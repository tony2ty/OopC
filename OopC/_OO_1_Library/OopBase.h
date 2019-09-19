
#ifndef OOPBASE_H__
#define OOPBASE_H__

#ifdef OOPLIB_API
#else
	#define OOPLIB_API __declspec(dllimport)
#endif // !OOPLIB_API


#include <stdbool.h>
#include <stdarg.h>

////OopBase//////////////////////////////////////////////////////////////////////////////
//

//获取类型名称字符串
#define   TYPE(type) #type

//构造函数帮助宏
#define CREATE(type) Create_ ## type   
//实例方法调用帮助宏
#define INVOKE(type) Invoke_ ## type   
//继承帮助宏
#define EXTEND(type) Extend_ ## type   
//析构帮助宏
#define DELETE(type) Delete_ ## type   

//类型转换帮助宏，该宏将实例从当前类类型转换至指定父类型
//最好不要复合调用，SWITCH((...some expr...), ..., ...)
#define SWITCH(pInst, theclass, superclass) AsBaseByType(EXTEND(theclass)(pInst), pInst, TYPE(superclass))

//调用该宏实现这样的功能，给定函数参数pParams，通过实例pInst调用名为pFuncName的方法
//最好不要复合调用，DOINVOKE((...some expr...), ..., ...)
#define DOINVOKE(pInst, pFuncName, pParams) Invoke(pInst->pChain, pInst, pFuncName, &(ParamIn){ AsBaseByFunc(pInst->pChain, pInst, pFuncName), pParams })

//调用该宏实现这样的功能，给定函数参数pParams(...)，通过实例pInst调用名为pFuncName的方法，调用的时候，只会查找实例链上部，也就是只会调用继承得到的方法
//最好不要复合调用，DOINVOKESUPER((...some expr...), ..., ...)
#define DOINVOKESUPER(pInst, pFuncName, ...) InvokeSuper(pInst->pChain, pInst, pFuncName, &(ParamIn){ AsBaseByFuncUpward(pInst->pChain, pInst, pFuncName), __VA_ARGS__ })

//类定义帮助宏，
//定义时，给定构造参数，则类没有默认无参构造函数声明
//反之，没有给定构造参数，则类有默认构造函数声明
#define CLASSDEF(theclass, ...)                                                    \
	typedef struct theclass theclass;                                              \
	theclass* CREATE(theclass)(__VA_ARGS__);                                       \
	void      INVOKE(theclass)(theclass*   pInst, char* pFuncName, void* pParams); \
	void*     EXTEND(theclass)(theclass*   pInst);                                 \
	void      DELETE(theclass)(theclass** ppInst);                                 \

//标准实例链定义
#define CHAINDEF InstanceChain *pChain 

//成员方法标准类型
typedef void (*Transit)(void*);
//成员方法的入参结构体，
//用于转发调用，
typedef struct { void* pInst; void* pIn; } ParamIn;
//成员方法的空参数结构体，
//用于外部调用
typedef struct { void* pVd; } ParamNull;

//////////////////////////////////////////////////////////////////////////////////
//

typedef void (*ExtraMemClear)(void*);
typedef struct ExtraMemRef ExtraMemRef;

OOPLIB_API ExtraMemRef* GenerateExtraMemRef(ExtraMemClear fnExec, void* pToClear);

//////////////////////////////////////////////////////////////////////////////////
//

typedef struct Method Method;
typedef struct MethodRing MethodRing;

OOPLIB_API Method*     GenerateMethod(Transit pAddr, char* pName);
OOPLIB_API MethodRing* GenerateMethodRing();
OOPLIB_API MethodRing*   InsertMethod(MethodRing *pMethods, int nMethodNum, ...);

//////////////////////////////////////////////////////////////////////////////////
//

typedef struct Instance Instance;
typedef struct InstanceChain InstanceChain;

OOPLIB_API Instance*      GenerateInstance(void* pFields, char* pName, ExtraMemRef *pExtRef, MethodRing* pMethods);
OOPLIB_API InstanceChain* GenerateInstanceChain();
OOPLIB_API InstanceChain*   InsertInstance(InstanceChain* pChain, Instance* pInstance);

//////////////////////////////////////////////////////////////////////////////////
//

//该函数的目的在于通过实例指针pInst调用名为pFuncName的函数，参数为pParams。
//而指定名称的函数可能是pInst实例从父类中继承得到的，
//因此需要实例链，用以查找函数，
//在实例链中查找的时候，优先向下查找，然后向上查找
OOPLIB_API void  Invoke(InstanceChain* pChain, void* pInst, char* pFuncName, void* pParams);

//该函数的目的在于通过实例指针pInst调用名为pFuncName的函数，参数为pParams。
//实例链pChain用于查找函数，
//查找时，只会向上查找
OOPLIB_API void  InvokeSuper(InstanceChain* pChain, void* pInst, char* pFuncName, void* pParams);

//该函数从实例链pChain中查找给定的实例指针pInst，然后向上查找，直到找到给定类型的实例为止
OOPLIB_API void* AsBaseByType(InstanceChain* pChain, void* pInst, char* pBaseType);

//根据函数名称，确定实例链中哪个实例将会被调用，优先向下查找，然后向上查找
OOPLIB_API void* AsBaseByFunc(InstanceChain* pChain, void* pInst, char* pFuncName);

//根据函数名称，确定实例链中哪个实例将会被调用，仅向上查找
OOPLIB_API void* AsBaseByFuncUpward(InstanceChain* pChain, void* pInst, char* pFuncName);

//获取给定实例的实际类型指针
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

#endif // !OOPBASE_H__


