#ifndef __HOOK_H__
#define __HOOK_H__

int writeCode(int address,void *data,int length);
int writeCodeValue(int address,int value);

/* This inspects memory at address to check if there is an x86 call
 * instruction there, and if there is, changes it to call function.
 * address of function that was called by this instruction initially
 * is put into fallthrough. */
int hook(int address,void *function,void *fallthrough);

/* This scans text section and hooks into anything like a call to function
 * at address, making program call function instead. If fallthrough is
 * specified, writes address into it (it is convenient to pass a function
 * as fallthrough, so that you don't have to do insane casts to assign
 * address to it) */
/* I don't know a safe way to implement this, sorry. In rare cases it
 * might interpret data as instruction and fuck everything up big time. */
int hookSweep(int address,void *function,void *fallthrough);

/* When an instance of hook_helper_insrerter is created, function
 * hookSweep(address,code,original) is called. This is a shortcut to allow code
 * outside of function scope (called when program is loaded). */
struct hook_helper_insrerter{
	hook_helper_insrerter(int address,int code,int *original);
};

/* When an instance of hook_single_helper_insrerter is created, function
 * hook(address,code,original) is called. This is a shortcut to allow code
 * outside of function scope (called when program is loaded). */
struct hook_single_helper_inserter{
	hook_single_helper_inserter(int address,int code,int *original);
};

/* When an instance of hook_vf_helper_inserter is created, function
 * hookvf(address,code,original) is called. */
struct hook_vf_helper_inserter{
	hook_vf_helper_inserter(int address,int code,int *original);
};


struct hook_helper_empty_class{
};

/* This macro should be followed by a BLOCK ({...} <-- this). It creates an
 * instance of class sub_##name##_helper_class named sub_##name.
 * It has fields:
 *   function  - address of function that, when executed, will run code
 *               inside BLOCK.
 *   functionf - callable from C++ code function, placed in union with 'function'.
 *               It is a member of another automatically created class,
 *               sub_##name##_helper. You can call it as any pointer to C++
 *               class member function, or using HOOK_METHOD_CALL macro.
 *               sub_##name##_helper can be inherited from your own calls
 *               classname, or from default dummy class hook_helper_empty_class.
 *   original  - address of function that BLOCK is supposed to hook into. Callable
 *               with HOOK_METHOD_CHAIN macro.
 *   originalf - callable from C++ code function, placed in union with 'original'.
 *
 * It also creates an instance of hook_helper_class (see higher) with arguments
 * (addr, function, &original), automatically hooking into program code.
 *
 * Here is some sample use:
 *
	FULL_HOOK_METHOD(0x448ee0,Script,0x448ee0,int,(int slot,char *filename,int unk0)){
		int res;

		res=HOOK_METHOD_CHAIN(0x448ee0,(slot,"my-other-filename",unk0));

		return 1-res;
	}
 * 
 * This will, assuming there is some C++ class method at 0x448ee0, make
 * program call this code instead. It calls original method with
 * different second argument, and returns different value.
 */
#define FULL_HOOK_METHOD(name,classname,addr,type,args) \
 \
class sub_##name##_helper : public classname{ \
public: \
	type func args; \
}; \
 \
class sub_##name##_helper_class{ \
public: \
	union{ \
		int function; \
		type (__thiscall sub_##name##_helper::*functionf ) args; \
	}; \
	union{ \
		int original; \
		type (__thiscall sub_##name##_helper::*originalf ) args; \
	}; \
 \
	sub_##name##_helper_class(type (__thiscall sub_##name##_helper::*f ) args){ \
		functionf=f; \
		original=NULL; \
	} \
} sub_##name(&sub_##name##_helper::func); \
 \
static hook_helper_insrerter sub_##name##_hook_inserter(addr,sub_##name.function,&sub_##name.original); \
 \
type sub_##name##_helper::func args

/* Shortcut for FULL_HOOK_METHOD with unsensible name and dummy class */
#define HOOK_METHOD(addr,type,args) FULL_HOOK_METHOD(addr,hook_helper_empty_class,addr,type,args)

/* Shortcut for FULL_HOOK_METHOD with unsensible name */
#define HOOK_INHERITED_METHOD(addr,classname,type,args) FULL_HOOK_METHOD(addr,classname,addr,type,args)

/* Shortcut for FULL_HOOK_METHOD that doesn't hook function anywhere */
#define DECLARE_METHOD(name,type,args) FULL_HOOK_METHOD(name,hook_helper_empty_class,0,type,args)


/* Will hook a method previously declared with FULL_HOOK_METHOD.
 * addr is an address of processor instruction that makes the call.
 * That is, if you see this line in IDA (or your favorite disassembler):
 *      .text:0043ABBF                 call    sub_4491B0
 * then addr should be 0x43ABBF. */
#define HOOK_DECLARED_METHOD(name,addr) \
	static hook_single_helper_inserter sub_##name##_single_hook_inserter_at_##addr(addr,sub_##name.function,&sub_##name.original);

/* Will hook a method previously declared with FULL_HOOK_METHOD.
 * addr is an address of location in memory where address of the
 * function resides (i.e., a virtual function table entry) */
#define HOOK_DECLARED_VF_METHOD(name,addr) \
	static hook_vf_helper_inserter sub_##name##_vf_hook_inserter_at_##addr(addr,sub_##name.function,&sub_##name.original);

/* calls 'original' when inside BLOCK of FULL_HOOK_METHOD */
#define HOOK_METHOD_CHAIN(addr,args) \
	(((sub_##addr##_helper *)this)->*(sub_##addr##.originalf)) args

/* calls 'function' when inside BLOCK of FULL_HOOK_METHOD */
#define HOOK_METHOD_CALL(addr,args) \
	(((sub_##addr##_helper *)this)->*(sub_##addr##.functionf)) args

/* calls 'original' when inside BLOCK of FULL_HOOK_METHOD */
#define CALL_METHOD(addr,args,self) \
	(((sub_##addr##_helper *)(self))->*(sub_##addr##.originalf)) args


#endif
