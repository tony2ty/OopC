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

/******************************************************/
/***** API for Object-Oriented Programming with C *****/
/******************************************************/
#define CREATE(type) Create_ ## type

#define INVOKE(type) Invoke_ ## type

#define EXTEND(type) Extend_ ## type

#define DELETE(type) Delete_ ## type

#define DOINVOKE(pInst, pFuncName, pParams)                                                                                           \
                return Invoke(pInst->pChain, pInst, pFuncName, &(ParamIn){ ConvertByFunc(pInst->pChain, pInst, pFuncName), pParams }) \

#define DOEXTEND(pInst)                                                                                                               \
				return pInst == NULL ? NULL : pInst->pChain																			  \

#define DODELETE(pInst, theclass, superclass)                                                                                         \
                superclass *pSuper = SWITCH(pInst, theclass, superclass); DELETE(superclass)(pSuper)                                  \

#define DOCREATE(pInst, theclass, superclass, pRlsRef, ...)                                             \
                theclass *pInst = malloc(sizeof(theclass));                                             \
                if (!pInst) { return NULL; }                                                            \
                void *pMethods = GenerateMethodRing();                                                  \
                if (!pMethods) { free(pInst); return NULL; }                                            \
                __VA_ARGS__                                                                             \
                pInst->pChain = InsertInstance(                                                         \
                    EXTEND(superclass)(CREATE(superclass)()),                                           \
                    GenerateInstance(pInst, #theclass, pRlsRef, pMethods));                             \
				if (pInst->pChain == NULL) return NULL                                                  \

#define CLASSDEF(theclass, superclass)                                                                  \
	            typedef struct theclass theclass;                                                       \
	            theclass* CREATE(theclass)();                                                           \
	            bool      INVOKE(theclass)(theclass* pInst, char* pFuncName, void* pParams);            \
	            void*     EXTEND(theclass)(theclass* pInst);                                            \
	            void      DELETE(theclass)(theclass* pInst)                                             \

#define CLASSDEFEXP(exportflag, theclass, superclass)                                                   \
	            typedef struct theclass theclass;                                                       \
	            exportflag theclass* CREATE(theclass)();                                                \
	            exportflag bool      INVOKE(theclass)(theclass* pInst, char* pFuncName, void* pParams); \
	            exportflag void*     EXTEND(theclass)(theclass* pInst);                                 \
	            exportflag void      DELETE(theclass)(theclass* pInst)                                  \

/******************************************************/
/******* Neccessary and required API for Coding *******/
/******************************************************/
//demonstrate a method has no implement
#define      ABSTRACT                                                                                                                                 \
//demonstrate an operation of implementing an abstract method of super or overriding an inherited method
#define      OVERRIDE                                                                                                                                 \

#define      CHAINDEF                                                                                                                                 \
                     void *pChain                                                                                                                     \

#define        METHOD(name)                                                                                                                           \
                     if (InsertMethod(pMethods, GenerateMethod(name, #name)) == NULL) {DestroyMethodRing(pMethods); return NULL;}                     \

#define       AMETHOD(name)                                                                                                                           \
                     if (InsertMethod(pMethods, GenerateMethod(NULL, #name)) == NULL) {DestroyMethodRing(pMethods); return NULL;}                     \

#define        SWITCH(pInst, theclass, superclass)                                                                                                    \
                     ConvertByType(EXTEND(theclass)(pInst), pInst, #superclass)                                                                       \

#define DOINVOKESUPER(pInst, pFuncName, ...)                                                                                                          \
                     InvokeSuper(pInst->pChain, pInst, pFuncName, &(ParamIn){ ConvertByFuncInherited(pInst->pChain, pInst, pFuncName), __VA_ARGS__ }) \


typedef struct { void* pNull; } ParamNull;
typedef struct { void* pInst; void* pIn; } ParamIn;

//only for calling INVOKE function
#define INVKSUCCESS       0//success
#define INVKNULLPARAM     1//Null chain or inst or funcName.
#define INVKINSTNOTFOUND  2//not an instance of given type, or say, inst not found in chain
#define INVKNOSUCHMETHOD1 3//The declared type has no such method.
#define INVKNOSUCHMETHOD2 4//no such method found.
OOPLIB_API int GetInvokeRetCode();
OOPLIB_API void ResetInvokeRetCode();

//for releasing local memory
#define RLSLOCALMEMBRA()                                                                            \
                      void *pLocalMemRefList = GenerateReleaserRefList()                            \

#define RLSLOCALMEMKET()                                                                            \
                      DestroyReleaserRefList(pLocalMemRefList)                                      \

#define          TORLS(fnRelease, pToClear)                                                         \
                      InsertReleaserRef(pLocalMemRefList, GenerateReleaserRef(fnRelease, pToClear)) \

/********************************************************/
/* APIs Supporting as infrastructure for OO programming */
/********************************************************/
OOPLIB_API void* GenerateReleaserRef(void(*pfnRelease)(void *), void* pToClear);
OOPLIB_API void* GenerateReleaserRefList();
OOPLIB_API void*   InsertReleaserRef(void *pVdList, void *pVdRlsRef);
OOPLIB_API void   DestroyReleaserRefList(void *pVdList);


OOPLIB_API void* GenerateMethod(void(*pfnAddr)(void *), char* pName);
OOPLIB_API void* GenerateMethodRing();
OOPLIB_API void*   InsertMethod(void *pVdMethods, void *pVdMethod);
OOPLIB_API void   DestroyMethodRing(void *pVdMethods);


OOPLIB_API void* GenerateInstance(void* pFields, char* pName, void *pRlsRef, void* pVdMethods);
OOPLIB_API void* GenerateInstanceChain();
OOPLIB_API void*   InsertInstance(void* pVdChain, void* pVdInstance);


OOPLIB_API bool  Invoke                (void* pVdChain, void* pInst, char* pFuncName, void* pParams);
OOPLIB_API bool  InvokeSuper           (void* pVdChain, void* pInst, char* pFuncName, void* pParams);
OOPLIB_API void* ConvertByType         (void* pVdChain, void* pInst, char* pBaseType);
OOPLIB_API void* ConvertByFunc         (void* pVdChain, void* pInst, char* pFuncName);
OOPLIB_API void* ConvertByFuncInherited(void* pVdChain, void* pInst, char* pFuncName);

/********************************************************/
/************** Super super class : Object **************/
/********************************************************/
CLASSDEFEXP(OOPLIB_API, Object, NULL);

typedef struct { bool* pRet; void* pToCmpr; } Object_Equal;
typedef ParamNull Object_ToString;

#endif // !OOPBASE_H__


