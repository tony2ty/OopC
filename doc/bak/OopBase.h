//MIT License
//
//Copyright(c) 2019 Goodman Tao
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.


#ifndef OOPBASE_H__
#define OOPBASE_H__

#ifdef OOPLIB_API
#else
	#define OOPLIB_API __declspec(dllimport)
#endif // !OOPLIB_API


#include <stdbool.h>
#include <stdarg.h>
#include <malloc.h>

////OopBase//////////////////////////////////////////////////////////////////////////////
//

//------面向对象功能API-------------------------------------------------------------------------------------------------------------//

#define CREATE(type) Create_ ## type

#define INVOKE(type) Invoke_ ## type

#define EXTEND(type) Extend_ ## type

#define DELETE(type) Delete_ ## type

#define DOINVOKE(pInst, pFuncName, pParams)/*调用pInst的名为pFuncName的方法，参数为pParams。不要复合调用，DOINVOKE((...some expr...), ..., ...)*/ \
                return Invoke(pInst->pChain, pInst, pFuncName, &(ParamIn){ ConvertByFunc(pInst->pChain, pInst, pFuncName), pParams })

#define DOEXTEND(pInst) \
                return pInst->pChain

#define DODELETE(pInst, theclass, superclass) \
                superclass *pSuper = SWITCH(pInst, theclass, superclass); DELETE(superclass)(pSuper)

#define DOCREATE(pInst, theclass, superclass, pRlsRef, ...)/*创建实例，但并不初始化实例的数据域*/ \
                theclass *pInst = malloc(sizeof(theclass));                 \
                if (!pInst) { return NULL; }                                \
                void *pMethods = GenerateMethodRing();                      \
                if (!pMethods) { return NULL; };                            \
                __VA_ARGS__                                                 \
                pInst->pChain = InsertInstance(                             \
                    EXTEND(superclass)(CREATE(superclass)()),               \
                    GenerateInstance(pInst, #theclass, pRlsRef, pMethods))  \

#define CLASSDEF(theclass, superclass, ...)/*类定义宏，定义时，给定构造参数，则类没有默认无参构造函数声明，反之，则有*/ \
	            typedef struct theclass theclass;                                            \
	            theclass* CREATE(theclass)(__VA_ARGS__);                                     \
	            bool      INVOKE(theclass)(theclass* pInst, char* pFuncName, void* pParams); \
	            void*     EXTEND(theclass)(theclass* pInst);                                 \
	            void      DELETE(theclass)(theclass* pInst)                                  \

//-----实现面向对象的一些必要的宏定义--------------------------------------------------------------------------------------------------------------//

#define      ABSTRACT/*抽象方法注释符号*/

#define      CHAINDEF/*标准实例链定义*/ \
                     void *pChain

#define        METHOD(name)/*添加方法*/ \
                     InsertMethod(pMethods, 1, GenerateMethod(name, #name));

#define       AMETHOD(name)/*添加抽象方法，A前缀表示Abstract*/ \
                     InsertMethod(pMethods, 1, GenerateMethod(NULL, #name));

#define        SWITCH(pInst, theclass, superclass)/*将实例转换至指定父类型。不要复合调用，SWITCH((...some expr...), ..., ...)*/ \
                     ConvertByType(EXTEND(theclass)(pInst), pInst, #superclass)

#define DOINVOKESUPER(pInst, pFuncName, ...)/*调用pInst的父类pFuncName方法。不要复合调用，DOINVOKESUPER((...some expr...), ..., ...)*/ \
                     InvokeSuper(pInst->pChain, pInst, pFuncName, &(ParamIn){ ConvertByFuncInherited(pInst->pChain, pInst, pFuncName), __VA_ARGS__ })

//成员方法的空参数结构体
typedef struct { void* pNull; } ParamNull;
//成员方法的入参
typedef struct { void* pInst; void* pIn; } ParamIn;

//-----错误信息--------------------------------------------------------------------------------------------------------------//

//调用函数执行失败时，获取失败的信息
OOPLIB_API char *GetErrorInfo(char* pMemIn);

//-----内存释放--------------------------------------------------------------------------------------------------------------//

#define RLSLOCALMEMBRA()/*局部动态内存释放环境，开始宏。Release local memory bra*/ \
                      void *pLocalMemRefList = GenerateReleaserRefList()

#define RLSLOCALMEMKET()/*局部动态内存释放环境，结束宏。Release local memory ket*/ \
                      CallReleaser(pLocalMemRefList)

#define          TORLS(fnRelease, pToClear)/*局部动态内存释放标记宏。To Release*/ \
                      InsertReleaserRef(pLocalMemRefList, GenerateReleaserRef(fnRelease, pToClear))

OOPLIB_API void* GenerateReleaserRef(void* pfnRelease, void* pToClear);
OOPLIB_API void* GenerateReleaserRefList();
OOPLIB_API void*   InsertReleaserRef(void *pVdList, void *pVdRlsRef);
OOPLIB_API void      CallReleaser(void *pVdList);


//-----实例链，方法--------------------------------------------------------------------------------------------------------------//

OOPLIB_API void* GenerateMethod(void(*pAddr)(void *), char* pName);
OOPLIB_API void* GenerateMethodRing();
OOPLIB_API void*   InsertMethod(void *pVdMethods, int nMethodNum, ...);

//-----实例链，实例--------------------------------------------------------------------------------------------------------------//

OOPLIB_API void* GenerateInstance(void* pFields, char* pName, void *pRlsRef, void* pVdMethods);
OOPLIB_API void* GenerateInstanceChain();
OOPLIB_API void*   InsertInstance(void* pVdChain, void* pVdInstance);

//-----支持面向对象的功能--------------------------------------------------------------------------------------------------------------//

//该函数的目的在于通过实例指针pInst调用名为pFuncName的函数，参数为pParams。
//而指定名称的函数可能是pInst实例从父类中继承得到的，
//因此需要实例链，用以查找函数，
//在实例链中查找的时候，优先向下查找，然后向上查找
OOPLIB_API bool  Invoke                (void* pVdChain, void* pInst, char* pFuncName, void* pParams);

//该函数的目的在于通过实例指针pInst调用名为pFuncName的函数，参数为pParams。
//实例链pChain用于查找函数，
//查找时，只会向上查找
OOPLIB_API bool  InvokeSuper           (void* pVdChain, void* pInst, char* pFuncName, void* pParams);

//该函数从实例链pChain中查找给定的实例指针pInst，然后向上查找，直到找到给定类型的实例为止
OOPLIB_API void* ConvertByType         (void* pVdChain, void* pInst, char* pBaseType);

//根据函数名称，确定实例链中哪个实例将会被调用，优先向下查找，然后向上查找
OOPLIB_API void* ConvertByFunc         (void* pVdChain, void* pInst, char* pFuncName);

//根据函数名称，确定实例链中哪个实例将会被调用，仅向上查找
OOPLIB_API void* ConvertByFuncInherited(void* pVdChain, void* pInst, char* pFuncName);

////Object//////////////////////////////////////////////////////////////////////////////
//

typedef struct Object Object;

OOPLIB_API Object* CREATE(Object)();
OOPLIB_API bool    INVOKE(Object)(Object* pInst, char* pFuncName, void* pParams);
OOPLIB_API void*   EXTEND(Object)(Object* pInst);
OOPLIB_API void    DELETE(Object)(Object* pInst);

typedef struct { bool* pRet; void* pToCmpr; } Object_Equal;
typedef ParamNull Object_ToString;

#endif // !OOPBASE_H__


