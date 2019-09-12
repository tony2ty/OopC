
#ifndef BASE_H__
#define BASE_H__

#ifdef OOPLIB_API
#else
	#define OOPLIB_API __declspec(dllimport)
#endif // !OOPLIB_API


#include <stdbool.h>

////OopBase//////////////////////////////////////////////////////////////////////////////
//

#define   TYPE(type) #type			 //获取类型名称字符串

#define CREATE(type) Create_ ## type //构造函数实用宏
#define INVOKE(type) Invoke_ ## type //实例方法调用实用宏
#define EXTEND(type) Extend_ ## type //继承实用宏
#define DELETE(type) Delete_ ## type //析构实用宏
#define SWITCH(pInst, theclass, superclass) AsBase(EXTEND(theclass)(pInst), pInst, TYPE(superclass))
									 //类型转换实用宏
#define DOINVOKE(pInst, pFuncName, pParams) Invoke(pInst->pChain, pInst, pFuncName, &(ParamIn){ AsBaseByFunc(pInst->pChain, pInst, pFuncName), pParams })
									 //方法调用转发
#define CLASSDEF(theclass, ...)                                                    \
	typedef struct theclass theclass;                                              \
	theclass* CREATE(theclass)(__VA_ARGS__);                                       \
	void      INVOKE(theclass)(theclass*   pInst, char* pFuncName, void* pParams); \
	void*     EXTEND(theclass)(theclass*   pInst);                                 \
	void      DELETE(theclass)(theclass** ppInst);                                 \
									 //类定义

typedef void (*Transit)(void*);
typedef struct { void* pInst; void* pIn; } ParamIn;
typedef struct { void* pVd; } ParamNull;

//////////////////////////////////////////////////////////////////////////////////
//

typedef struct Method Method;
typedef struct MethodRing MethodRing;
typedef struct MethodUtil
{
	MethodRing* pRing;
	struct MethodUtil* (*InsertMethod)(struct MethodUtil*, Method*);
} MethodUtil;

OOPLIB_API Method*     GenerateMethod(Transit pAddr, char* pName);
OOPLIB_API MethodRing* GenerateMethodRing();
OOPLIB_API MethodUtil*   InsertMethod(MethodUtil* pUtil, Method* pMethod);

//////////////////////////////////////////////////////////////////////////////////
//

typedef struct Instance Instance;
typedef struct InstanceChain InstanceChain;

OOPLIB_API Instance*      GenerateInstance(void* pFields, char* pName, MethodRing* pMethods);
OOPLIB_API InstanceChain* GenerateInstanceChain();
OOPLIB_API InstanceChain*   InsertInstance(InstanceChain* pChain, Instance* pInstance);

//////////////////////////////////////////////////////////////////////////////////
//

OOPLIB_API void  Invoke(InstanceChain* pChain, void* pInst, char* pFuncName, void* pParams);
OOPLIB_API void* AsBase(InstanceChain* pChain, void* pInst, char* pBaseType);
OOPLIB_API void* AsBaseByFunc(InstanceChain* pChain, void* pInst, char* pFuncName);
OOPLIB_API void* AsExactType(InstanceChain* pChain, void* pInst);
OOPLIB_API void  Delete(InstanceChain* pChain);

////Object//////////////////////////////////////////////////////////////////////////////
//

typedef struct Object Object;

OOPLIB_API Object* CREATE(Object)();
OOPLIB_API void    INVOKE(Object)(Object*   pInst, char* pFuncName, void* pParams);
OOPLIB_API void*   EXTEND(Object)(Object*   pInst);
OOPLIB_API void    DELETE(Object)(Object** ppInst);

typedef struct { bool* pRet; void* pToCmpr; } Object_Equal;
typedef ParamNull Object_ToString;

#endif // !BASE_H__


