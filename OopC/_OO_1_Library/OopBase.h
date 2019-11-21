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

#ifdef OOPBASE_API
#else
#define OOPBASE_API __declspec(dllimport)
#endif // OOPBASE_API


#include <stdbool.h>
#include <stdarg.h>
#include <malloc.h>


/******************************************************/
/******** API for Object-Oriented Programming *********/
/******************************************************/
#define      ABSTRACT                                                                              \

#define      OVERRIDE                                                                              \

#define METHODDECLARE(declaration)                                                                 \

#define         CLASS(theclass, superclass)                                                        \
					 typedef struct theclass ## _Fld theclass ## _Fld;                             \
					 typedef struct theclass theclass;                                             \
					 struct theclass                                                               \
					 {                                                                             \
						 theclass ## _Fld *pFld;                                                   \
						 void *(* Extend)(theclass *pSelf);                                        \
						 bool  (* Call  )(theclass *pSelf, const char *pMethodName, ...);          \
					 };                                                                            \
					 theclass *New_ ## theclass();                                                 \
					 void      Del_ ## theclass(theclass *pSelf)                                   \

#define      CLASSEXP(exportflag, theclass, superclass)                                            \
					 typedef struct theclass ## _Fld theclass ## _Fld;                             \
					 typedef struct theclass theclass;                                             \
					 struct theclass                                                               \
					 {                                                                             \
						 theclass ## _Fld *pFld;                                                   \
						 void *(* Extend)(theclass *pSelf);                                        \
						 bool  (* Call  )(theclass *pSelf, const char *pMethodName, ...);          \
					 };                                                                            \
					 exportflag theclass *New_ ## theclass();                                      \
					 exportflag void      Del_ ## theclass(theclass *pSelf)                        \

#define           NEW(theclass)                                                                    \
					 New_ ## theclass()                                                            \

#define           DEL(theclass)                                                                    \
					 Del_ ## theclass                                                              \

#define         SUPER(pthis, methodname, ...)                                                      \
                     RedirectCallSuper(pthis->pFld->__pChain, pthis, methodname, __VA_ARGS__)      \

#define        SWITCH(pObj, superclass)                                                            \
					 ConvertByType(pObj->Extend(pObj), pObj, #superclass)                          \


/******************************************************/
/******* Neccessary and required API for Coding *******/
/******************************************************/
#define  CHAINDECLARE                                                                                                                                                 \
					 void *__pChain                                                                                                                                   \

#define         __NEW(theclass)                                                                                                                                       \
                     New_ ## theclass                                                                                                                                 \

#define         __DEL(theclass)                                                                                                                                       \
                     Del_ ## theclass                                                                                                                                 \

#define      __EXTEND(theclass)                                                                                                                                       \
                     __Extend                                                                                                                                         \

#define        __CALL(theclass)                                                                                                                                       \
                     __Call                                                                                                                                           \

#define       __CLEAR(theclass)                                                                                                                                       \
                     __Clear                                                                                                                                          \

#define        METHOD(name)                                                                                                                                           \
					 if (!InsertMethod(__Methods, GenerateMethod(name, #name))) { return NULL; }                                                                      \

#define       AMETHOD(name)                                                                                                                                           \
					 if (!InsertMethod(__Methods, GenerateMethod(NULL, #name))) { return NULL; }                                                                      \

#define        DOCALL(pSelf, pMethodName)                                                                                                                             \
					 va_list __vlArgs;                                                                                                                                \
					 va_start(__vlArgs, pMethodName);                                                                                                                 \
					 bool __Ret = RedirectCall(pSelf->pFld->__pChain, pSelf, pMethodName, __vlArgs);                                                                  \
					 va_end(__vlArgs);                                                                                                                                \
					 return __Ret                                                                                                                                     \

#define      DOEXTEND(pSelf)                                                                                                                                          \
					 return pSelf->pFld->__pChain                                                                                                                     \

#define         DODEL(pSelf, superclass)                                                                                                                              \
					 superclass *__Super = ConvertByType(pSelf->pFld->__pChain, pSelf, #superclass);                                                                  \
					 Del_ ## superclass(__Super)                                                                                                                      \

#define         DONEW(pNew, theclass, superclass, fnRelease, ...)                                                                                                     \
					 theclass* pNew = NULL;                                                                                                                           \
					 {                                                                                                                                                \
						 void* __Methods = NULL;                                                                                                                      \
						 {                                                                                                                                            \
							 __Methods = GenerateMethodRing();                                                                                                        \
							 if (!__Methods) { return NULL; }                                                                                                         \
					                                                                                                                                                  \
							 __VA_ARGS__                                                                                                                              \
						 }                                                                                                                                            \
					                                                                                                                                                  \
						 theclass ## _Fld* __Fld = NULL;                                                                                                              \
						 {                                                                                                                                            \
							 __Fld = malloc(sizeof(theclass ## _Fld));                                                                                                \
							 if (!__Fld) { DestroyMethodRing(__Methods); return NULL; }                                                                               \
						 }                                                                                                                                            \
					                                                                                                                                                  \
						 theclass* __New = NULL;                                                                                                                      \
						 {                                                                                                                                            \
							 __New = malloc(sizeof(theclass));                                                                                                        \
							 if (!__New) { DestroyMethodRing(__Methods); free(__Fld); return NULL; }                                                                  \
					                                                                                                                                                  \
							 __New->pFld = __Fld;                                                                                                                     \
							 __New->Extend = __EXTEND(theclass);                                                                                                      \
							 __New->Call = __CALL(theclass);                                                                                                          \
						 }                                                                                                                                            \
					                                                                                                                                                  \
						 superclass* __Super = NULL;                                                                                                                  \
						 {                                                                                                                                            \
							 __Super = NEW(superclass);                                                                                                               \
							 if (!__Super) { DestroyMethodRing(__Methods); free(__Fld); free(__New); return NULL; }                                                   \
					                                                                                                                                                  \
							 __Fld->__pChain = __Super->Extend(__Super);                                                                                              \
						 }                                                                                                                                            \
					                                                                                                                                                  \
                         void *__ReleaserRef = NULL;                                                                                                                  \
                         {                                                                                                                                            \
                             __ReleaserRef = GenerateReleaserRef(fnRelease, __New, false);                                                                            \
                             if (fnRelease && !__ReleaserRef) { DestroyMethodRing(__Methods); free(__New); free(__Fld); DEL(superclass)(__Super); return NULL; }      \
                         }                                                                                                                                            \
					                                                                                                                                                  \
						 void* __Instance = NULL;                                                                                                                     \
						 {                                                                                                                                            \
							 __Instance = GenerateInstance(__New, __Fld, #theclass, __ReleaserRef, __Methods);                                                        \
							 if (!__Instance) { DestroyMethodRing(__Methods); free(__New); free(__Fld); DEL(superclass)(__Super); free(__ReleaserRef); return NULL; } \
					                                                                                                                                                  \
							 InsertInstance(__Super->Extend(__Super), __Instance);                                                                                    \
 						 }                                                                                                                                            \
					                                                                                                                                                  \
						 pNew = __New;                                                                                                                                \
					 }                                                                                                                                                \
/*
 * Status Code: success */
#define      CALLSUCCESS  0
/*
 * Status Code: not an instance of given type, or say, inst not found in chain */
#define INSTANCENOTFOUND  1
/*
 * Status Code: The declared type has no such method. */
#define METHODUNDECLARED  2
/*
 * Status Code: no such method found. */
#define   METHODNOTFOUND  3

int GetCallCode();


/********************************************************/
/******************** Memory Util ***********************/
/********************************************************/
/*
 * for releasing local memory.
 * this macro always asserts that mem will be allocated successfully,
 * while in some extreme condition failure of mem allocation will cause error. */
#define   RLSLOCALMEMBRA()                                                                                      \
                        void *__LocalMemRefList = GenerateReleaserRefList()                                     \

#define   RLSLOCALMEMKET()                                                                                      \
                        DestroyReleaserRefList(__LocalMemRefList)                                               \
/*
 * used to mark mem dynamically allocated which is intended to free at the end of current code block.
 * this macro always asserts that mem will be allocated successfully when calling GenerateReleaserRef(),
 * while in some extreme condition failure of mem allocation will cause error. */
#define            TORLS(fnRelease, pToRelease)                                                                 \
                        InsertReleaserRef(__LocalMemRefList, GenerateReleaserRef(fnRelease, pToRelease, false)) \

#define     TORLSMUTABLE(fnRelease, pToRelease)                                                                 \
                        InsertReleaserRef(__LocalMemRefList, GenerateReleaserRef(fnRelease, &pToRelease, true)) \


/********************************************************/
/* APIs Supporting as infrastructure for OO programming */
/********************************************************/
typedef struct { void* pThis; va_list vlArgs; } ParamIn;

OOPBASE_API void* GenerateReleaserRef(void(*pfnRelease)(void *), void* pToRelease, bool bMutable);
OOPBASE_API void* GenerateReleaserRefList();
OOPBASE_API void   DestroyReleaserRefList(void *pList);
OOPBASE_API void*   InsertReleaserRef(void *pList, void *pReleaserRef);

OOPBASE_API void* GenerateMethod(void(*pfnMethod)(ParamIn *), const char* pMethodName);
OOPBASE_API void* GenerateMethodRing();
OOPBASE_API void   DestroyMethodRing(void *pMethodRing);
OOPBASE_API void*   InsertMethod(void *pMethodRing, void *pMethod);

OOPBASE_API void* GenerateInstance(void *pObj, void* pFld, const char* pClassName, void *pReleaserRef, void* pMethodRing);
OOPBASE_API void* GenerateInstanceChain();
OOPBASE_API void*   InsertInstance(void* pChain, void* pInstance);

OOPBASE_API bool  RedirectCall(void* pChain, void* pObj, const char* pMethodName, va_list vlArgs);
OOPBASE_API bool  RedirectCallSuper(void* pChain, void* pObj, const char* pMethodName, ...);
OOPBASE_API void* ConvertByType(void* pChain, void* pObj, const char* pBaseName);


/********************************************************/
/************** Super super class : Object **************/
/********************************************************/
CLASSEXP(OOPBASE_API, Object, NULL);
METHODDECLARE(
	Equal:    bool* pRet; void* pToCompare;
	ToString: -;)

#endif // !OOPBASE_H__
