#include "hook.h"
#include "utils.h"


int writeCode(int address,void *data,int length){
	DWORD oldSetting;

	VirtualProtect((void *)address,length,PAGE_READWRITE,&oldSetting);
	memcpy((int *)address,data,length);
	VirtualProtect((void *)address,length,oldSetting,&oldSetting);

	return 1;
}

int writeCodeValue(int address,int value){
	DWORD oldSetting;

	VirtualProtect((void *)address,sizeof(value),PAGE_READWRITE,&oldSetting);
	memcpy((int *)address,&value,sizeof(value));
	VirtualProtect((void *)address,sizeof(value),oldSetting,&oldSetting);

	return 1;
}

int hookvf(int address,void *function,void *fallthrough){
	if(fallthrough) *(int *)fallthrough=*(int *)address;
	return writeCodeValue(address,(int)function);
}

int hook(int address,void *function,void *fallthrough){
	DWORD oldSetting;
	unsigned int offset,addressLocation=-1,addressData;
	int page=address&0xfffff000;
	int count=0;

	/* e8 is a call instruction, it is followed by a 4-byte value
	 * that will be added to instruction pointer (and 5 bytes that this
	 * instruction takes  will be added as well) */
	if(*(unsigned char *)address==0xe8){
		offset=address + *(unsigned int *)(address+1) + 5;
		addressLocation=address+1;
		addressData=(int)function - address - 5;
	
	/* ff 15, apparently call too; absolute and indirect */
	} else if(*(unsigned char *)address==0xff && *(unsigned char *)(address+1)==0x15){
		offset=**(unsigned int **)(address+2);
		addressLocation=*(unsigned int *)(address+2);
		addressData=(int)function;
	}

	if(addressLocation==-1) return 0;

	
	/* Program memory is usually read-only, so we need to unprotect it first.
	 * We are unprotecting two pages because call instruction might span
	 * two pages. After that we replace the address to be called with new
	 * one, supplied to this function as argument. */
	VirtualProtect((void *)page,0x2000,PAGE_READWRITE,&oldSetting);
	*(int *)addressLocation=addressData;
	VirtualProtect((void *)page,0x2000,oldSetting,&oldSetting);

	/* We store the address of original function so that our hook can call it. */
	if(fallthrough!=NULL)
		*(unsigned int *)fallthrough=offset;


	return 1;
}


#include <DbgHelp.h>
#pragma comment( lib, "dbghelp.lib" )

void getTextSegment(int &textSegmentStart, int &textSegmentEnd){
	HMODULE module = GetModuleHandle(NULL);

	IMAGE_NT_HEADERS *pNtHdr = ImageNtHeader(module);
	IMAGE_SECTION_HEADER *pSectionHdr = (IMAGE_SECTION_HEADER *) (pNtHdr + 1);

	const char* imageBase = (const char*) module;
	char scnName[sizeof(pSectionHdr->Name) + 1];
	scnName[sizeof(scnName) - 1] = '\0'; // enforce nul-termination for scn names that are the whole length of pSectionHdr->Name[]

	textSegmentStart = 0;
	textSegmentEnd = 0;

	for(int scn = 0; scn < pNtHdr->FileHeader.NumberOfSections; ++scn) {
		strncpy(scnName, (const char*) pSectionHdr->Name, sizeof(pSectionHdr->Name));

		int segStart = (int) (imageBase + pSectionHdr->VirtualAddress);
		int segEnd = (int) (imageBase + pSectionHdr->VirtualAddress + pSectionHdr->Misc.VirtualSize - 1);

		if(segStart < textSegmentStart || textSegmentStart == 0) textSegmentStart = segStart;
		if(segEnd > textSegmentEnd || textSegmentEnd == 0) textSegmentEnd = segEnd;

//		if(strcmp(scnName, ".text") == 0) {
//			textSegmentStart = segStart;
//			textSegmentEnd = segEnd;
//			return;
//		}
		++pSectionHdr;
	}
}


/* This scans text section and hooks into anything like a call to function
 * at address, making program call function instead. If fallthrough is
 * specified, writes address into it (it is convenient to pass a function
 * as fallthrough, so that you don't have to do insane casts to assign
 * address to it) */
int hookSweep(int address,void *function,void *fallthrough){
	unsigned char *p;

	if(fallthrough)
		*(int *)fallthrough=address;

	/* I also don't know how to get program segmentation info from a running
	 * executable, so for now these are values just pasted from IDA. */
	int textSegmentStart,textSegmentEnd;
	getTextSegment(textSegmentStart, textSegmentEnd);

	for(p=(unsigned char *)textSegmentStart;(int)p+6<textSegmentEnd;p++){
		if(*p==0xe8){
			int desiredValue=address-(int)p-5;
			if(desiredValue!=*(unsigned int *)(p+1)) continue;

			hook((int)p,function,fallthrough);
			p+=5;
		}

		if(*p==0xff && *(p+1)==0x15){
			if(address!=*(unsigned int *)(p+2)) continue;

			hook((int)p,function,fallthrough);
			p+=6;
		}

	}

	return 1;
}

static int log(char *fmt,...){
	va_list args;
	va_start(args,fmt);

	FILE *f=fopen("log.txt","a");
	vfprintf(f,fmt,args);
	fclose(f);

	va_end(args);
	return 0;
}

hook_helper_insrerter::hook_helper_insrerter(int address,int code,int *original){
	if(address==0) return;

	hookSweep(address,(void *)code,original);
}

hook_single_helper_inserter::hook_single_helper_inserter(int address,int code,int *original){
	if(address==0) return;
	
	hook(address,(void *)code,original);
}

hook_vf_helper_inserter::hook_vf_helper_inserter(int address,int code,int *original){
	if(address==0) return;
	
	hookvf(address,(void *)code,original);
}
