
#ifndef BASE_H__
#define BASE_H__

#ifdef OOPLIB_API
	#define OOPLIB_API __declspec(dllexport)
#else
	#define OOPLIB_API __declspec(dllimport)
#endif // !OOPLIB_API


#include <stdbool.h>

//////////////////////////////////////////////////////////////////////////////////
//

#define ___DEBUG

#define   TYPE(type) #type			 //获取类型名称字符串

#define   MAKE(type)   Make_ ## type //构造函数实用宏
#define INVOKE(type) Invoke_ ## type //实例方法调用实用宏
#define EXTEND(type) Extend_ ## type //继承实用宏
#define DELETE(type) Delete_ ## type //析构实用宏
#define SWITCH(pInst, subclass, superclass) AsBase(EXTEND(subclass)(pInst), pInst, TYPE(superclass))
									 //类型转换实用宏

typedef void (*Transit)(void*);

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
OOPLIB_API void  Delete(InstanceChain* pChain);

#endif // !BASE_H__


