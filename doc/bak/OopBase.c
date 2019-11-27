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


#define OOPBASE_API __declspec(dllexport)
#include "OopBase.h"

#include <string.h>
#include <stdio.h>


/**********************************************************/
/*********** Simple api for memory releasing **************/
/**********************************************************/
void* MallocMarked(size_t szLen, void* pList)
{
	void* pBlk = malloc(szLen);
	if (pBlk)
	{
		InsertReleaserRef(pList, GenerateReleaserRef(free, pBlk, false));
	}
	return pBlk;
}

void* CallocMarked(size_t szItemCount, size_t szItemLen, void *pList)
{
	void* pBlk = calloc(szItemCount, szItemLen);
	if (pBlk)
	{
		InsertReleaserRef(pList, GenerateReleaserRef(free, pBlk, false));
	}
	return pBlk;
}

typedef void(*Releaser)(void*);

typedef struct ReleaserRef ReleaserRef;
struct ReleaserRef { ReleaserRef *pPrev; ReleaserRef *pNext; bool bMutable; void* pToRelease; Releaser fnRelease; };

typedef struct ReleaserRefList ReleaserRefList;
struct ReleaserRefList { ReleaserRef *pHead; ReleaserRef *pTail; };

void* GenerateReleaserRef(void(*pfnRelease)(void *), void* pToRelease, bool bMutable)
{
    Releaser fnRelease = pfnRelease;

    if (!fnRelease || !pToRelease) { return NULL; }

    ReleaserRef* pRet = malloc(sizeof(ReleaserRef));
    if (!pRet) { return NULL; }

    pRet->pPrev = NULL;
    pRet->pNext = NULL;
    pRet->fnRelease = fnRelease;
    pRet->pToRelease = pToRelease;
    pRet->bMutable = bMutable;

    return pRet;
}

void* GenerateReleaserRefList()
{
    ReleaserRefList *pRet = malloc(sizeof(ReleaserRefList));

    if (!pRet) { return NULL; }

    pRet->pHead = NULL;
    pRet->pTail = NULL;

    return pRet;
}

void   DestroyReleaserRefList(void *_pList)
{
    ReleaserRefList *pList = _pList;

    if (!pList) { return; }

    while (pList->pHead)
    {
        ReleaserRef *pTmp = pList->pHead->pNext;

        if (pList->pHead->fnRelease)
        {
            if (pList->pHead->bMutable)
            {
                pList->pHead->fnRelease(*(void **)(pList->pHead->pToRelease));
            }
            else
            {
                pList->pHead->fnRelease(pList->pHead->pToRelease);
            }
        }
        free(pList->pHead);

        pList->pHead = pTmp;
    }

    free(pList);
}

void*   InsertReleaserRef(void *_pList, void *_pReleaserRef)
{
    ReleaserRefList *pList = _pList;
    ReleaserRef *pReleaserRef = _pReleaserRef;

    if (pList->pHead && pList->pTail)
    {
        pList->pTail->pNext = pReleaserRef;
        pReleaserRef->pPrev = pList->pTail;
        pReleaserRef->pNext = NULL;
        pList->pTail = pReleaserRef;

        return pList;
    }

    if (!pList->pHead && !pList->pTail)
    {
        pReleaserRef->pPrev = NULL;
        pReleaserRef->pNext = NULL;
        pList->pHead = pReleaserRef;
        pList->pTail = pReleaserRef;

        return pList;
    }

    return NULL;
}


/**********************************************************/
/***************** Implementation of OOP ******************/
/**********************************************************/
/* 
 * 1.datastructure and some related api */
typedef void(*MthdRef)(void *_pThis, va_list vlArgs);

typedef struct Method Method;
struct Method { Method* pPrev; Method* pNext; char* pMethodName; MthdRef fnExec; };

typedef struct MethodRing MethodRing;
struct MethodRing { Method* pHead; Method* pTail; };

void* GenerateMethod(void(*pfnMethod)(void* _pThis, va_list vlArgs), const char* pMethodName)
{
    MthdRef fnExec = pfnMethod;

    void* pMem = malloc(strlen(pMethodName) + 1);
    Method* pRet = malloc(sizeof(Method));

    if (!pMem || !pRet)
    {
        free(pRet);
        free(pMem);

        return NULL;
    }

    //field pPrev and pNext of pointer pRet malloced just now must be set to NULL for later judgement.
    pRet->pPrev = NULL;
    pRet->pNext = NULL;
    pRet->fnExec = fnExec;
    pRet->pMethodName = strcpy(pMem, pMethodName);

    return pRet;
}

void* GenerateMethodRing()
{
    MethodRing* pRet = malloc(sizeof(MethodRing));

    if (!pRet) { return NULL; }

    //field pHead and pTail of pointer pRet malloced just now must be set to NULL for later judgement.
    pRet->pHead = NULL;
    pRet->pTail = NULL;

    return pRet;
}

void   DestroyMethodRing(void* _pMethodRing)
{
    MethodRing* pMethodRing = _pMethodRing;

    if (pMethodRing->pHead && pMethodRing->pTail)
    {
        pMethodRing->pTail->pNext = NULL;
        while (pMethodRing->pHead)
        {
            Method *pTmp = pMethodRing->pHead->pNext;

            free(pMethodRing->pHead->pMethodName);
            free(pMethodRing->pHead);

            pMethodRing->pHead = pTmp;
        }
    }

    free(pMethodRing);
}

void*   InsertMethod(void* _pMethodRing, void* _pMethod)
{
    MethodRing* pMethodRing = _pMethodRing;
    Method* pMethod = _pMethod;

    if (pMethod == NULL)
    {
        DestroyMethodRing(pMethodRing);
        return NULL;
    }

    if (pMethodRing->pHead && pMethodRing->pTail)
    {
        pMethod->pPrev = pMethodRing->pTail;
        pMethod->pNext = pMethodRing->pHead;

        pMethodRing->pHead->pPrev = pMethod;
        pMethodRing->pTail->pNext = pMethod;

        pMethodRing->pTail = pMethod;

        return pMethodRing;
    }

    if (!pMethodRing->pHead && !pMethodRing->pTail)
    {
        pMethod->pNext = pMethod;
        pMethod->pPrev = pMethod;

        pMethodRing->pHead = pMethod;
        pMethodRing->pTail = pMethod;

        return pMethodRing;
    }

    return NULL;
}


typedef struct Instance Instance;
struct Instance { Instance* pPrev; Instance* pNext; char* pClassName; void *pObj; void* pFld; ReleaserRef* pReleaserRef; MethodRing* pMethodRing; };

typedef struct InstanceChain InstanceChain;
struct InstanceChain { Instance* pHead; Instance* pTail; };

void* GenerateInstance(void *pObj, void* pFld, const char* pClassName, void *_pReleaserRef, void* _pMethodRing)
{
    MethodRing *pMethodRing = _pMethodRing;
    ReleaserRef *pReleaserRef = _pReleaserRef;

    void* pMem = malloc(strlen(pClassName) + 1);
    Instance* pRet = malloc(sizeof(Instance));

    if (!pRet || !pMem)
    {
        free(pRet);
        free(pMem);

        return NULL;
    }

    //field pPrev and pNext of pointer pRet malloced just now must be set to NULL for later judgement.
    pRet->pPrev = NULL;
    pRet->pNext = NULL;
    pRet->pObj = pObj;
    pRet->pFld = pFld;
    pRet->pClassName = strcpy(pMem, pClassName);
    pRet->pReleaserRef = pReleaserRef;
    pRet->pMethodRing = pMethodRing;

    return pRet;
}

void* GenerateInstanceChain()
{
    InstanceChain* pRet = malloc(sizeof(InstanceChain));

    if (!pRet) { return NULL; }

    //field pHead and pTail of pointer pRet malloced just now must be set to NULL for later judgement.
    pRet->pHead = NULL;
    pRet->pTail = NULL;

    return pRet;
}

void   DestroyInstanceChain(void* _pChain)
{
    InstanceChain *pChain = _pChain;

    while (pChain->pHead)
    {
        Instance *pTmp = pChain->pHead->pNext;

        if (pChain->pHead->pReleaserRef && pChain->pHead->pReleaserRef->fnRelease)
        {
            if (pChain->pHead->pReleaserRef->bMutable)
            {
                pChain->pHead->pReleaserRef->fnRelease(*(void **)(pChain->pHead->pReleaserRef->pToRelease));
            }
            else
            {
                pChain->pHead->pReleaserRef->fnRelease(pChain->pHead->pReleaserRef->pToRelease);
            }

            free(pChain->pHead->pReleaserRef);
        }

        free(pChain->pHead->pClassName);

        free(pChain->pHead->pFld);

        free(pChain->pHead->pObj);

        DestroyMethodRing(pChain->pHead->pMethodRing);

        free(pChain->pHead);

        pChain->pHead = pTmp;
    }

    free(pChain);
}

void*   InsertInstance(void* _pChain, void* _pInstance)
{
    InstanceChain *pChain = _pChain;
    Instance *pInstance = _pInstance;

    if (pChain->pHead && pChain->pTail)
    {
        pInstance->pPrev = pChain->pTail;
        pInstance->pNext = NULL;

        pChain->pTail->pNext = pInstance;

        pChain->pTail = pInstance;

        return pChain;
    }

    if (!pChain->pHead && !pChain->pTail)
    {
        pInstance->pPrev = NULL;
        pInstance->pNext = NULL;

        pChain->pHead = pInstance;
        pChain->pTail = pInstance;

        return pChain;
    }

    return NULL;
}


/*
 * 2.oop rules and some operations such as simple error handling */
int CallCode = CALLSUCCESS;

int GetCallCode()
{
    return CallCode;
}


bool ContainMethod(MethodRing *pMethodRing, const char *pMethodName)
{
    if (!pMethodRing->pHead || !pMethodRing->pTail) { return false; }

    Method *pIterator = pMethodRing->pHead;
    do
    {
        if (!strcmp(pMethodName, pIterator->pMethodName)) { return true; }
        pIterator = pIterator->pNext;

    } while (pIterator != pMethodRing->pHead);

    return false;
}

Method* FindMethod(MethodRing* pMethodRing, const char* pMethodName)
{
    if (!pMethodRing->pHead || !pMethodRing->pTail) { return NULL; }

    Method* pIterator = pMethodRing->pHead;
    do
    {
        //这里找到的可能是一个抽象方法，
        //也就是，方法换pRing中存在该方法，但是方法的指针为null，
        //这也导致了ContainMethod和FindMethod两个函数不能合并为一个函数
        if (!strcmp(pMethodName, pIterator->pMethodName)) { return pIterator; }
        pIterator = pIterator->pNext;

    } while (pIterator != pMethodRing->pHead);

    return NULL;
}

Instance* FindInstance(InstanceChain* pChain, void* pObj)
{
    Instance* pIterator = pChain->pHead;
    do
    {
        if (pIterator->pObj == pObj) { return pIterator; }
        pIterator = pIterator->pNext;

    } while (pIterator != NULL);

    return NULL;
}

bool RedirectCall(void* _pChain, void* pObj, const char* pMethodName, va_list vlArgs)
{
    InstanceChain *pChain = _pChain;

    MthdRef toExecute = NULL;
	void* pObjExact = NULL;

    Instance* pFindInst = FindInstance(pChain, pObj);
    if (!pFindInst)
    {
		CallCode = INSTANCENOTFOUND;
        return false;
    }

    for (Instance* pIterator = pFindInst; pIterator; pIterator = pIterator->pNext)
    {
        Method* pFindMthd = FindMethod(pIterator->pMethodRing, pMethodName);
        toExecute = pFindMthd ? pFindMthd->fnExec : toExecute;
        pObjExact = pFindMthd ? pIterator->pObj : pObjExact;
    }

    if (!toExecute)
    {
        for (Instance* pIterator = pFindInst->pPrev; pIterator; pIterator = pIterator->pPrev)
        {
            Method* pFindMthd = FindMethod(pIterator->pMethodRing, pMethodName);
            if (pFindMthd)
            {
                toExecute = pFindMthd->fnExec;
                pObjExact = pIterator->pObj;
                break;
            }
        }
    }

    if (toExecute)
    {
        //通过父类指针调用子类方法时，需要保证各层父类中存在该方法的声明
        if (!pFindInst->pNext)
        {
			toExecute(pObjExact, vlArgs);
            CallCode = CALLSUCCESS;
            return true;
        }
        else
        {
            bool bValidCall = false;
            for (Instance *pIterator = pFindInst; pIterator; pIterator = pIterator->pPrev)
            {
                if (ContainMethod(pIterator->pMethodRing, pMethodName))
                {
                    bValidCall = true;
                    break;
                }
            }

            if (bValidCall)
            {
				toExecute(pObjExact, vlArgs);
                CallCode = CALLSUCCESS;
                return true;
            }
            else
            {
				CallCode = METHODUNDECLARED;
                return false;
            }
        }
    }
    else
    {
		CallCode = METHODNOTFOUND;
        return false;
    }
}

bool RedirectCallSuper(void* _pChain, void* pObj, const char* pMethodName, ...)
{
    InstanceChain *pChain = _pChain;

    MthdRef toExecute = NULL;
    void *pObjExact = NULL;

    Instance* pFindInst = FindInstance(pChain, pObj);
    if (!pFindInst)
    {
        CallCode = INSTANCENOTFOUND;
        return false;
    }

    for (Instance *pIterator = pFindInst->pPrev; pIterator; pIterator = pIterator->pPrev)
    {
        Method* pFindMthd = FindMethod(pIterator->pMethodRing, pMethodName);
        if (pFindMthd)
        {
            toExecute = pFindMthd->fnExec;
            pObjExact = pIterator->pObj;
            break;
        }
    }

    if (toExecute)
    {
        va_list vlArgs;
        va_start(vlArgs, pMethodName);
        toExecute(pObjExact, vlArgs);
        va_end(vlArgs);

        CallCode = CALLSUCCESS;
        return true;
    }
    else
    {
        CallCode = METHODNOTFOUND;
        return false;
    }
}

void* ConvertByType(void* _pChain, void* pObj, const char* pBaseName)
{
    InstanceChain *pChain = _pChain;

    for (Instance* pIterator = FindInstance(pChain, pObj); pIterator; pIterator = pIterator->pPrev)
    {
        if (!strcmp(pIterator->pClassName, pBaseName)) { return pIterator->pObj; }
    }

    return NULL;
}

void* ConvertToExactType(InstanceChain* pChain, void* pObj)
{
    Instance *pInstance = NULL;
    for (Instance *pIterator = FindInstance(pChain, pObj); pIterator; pIterator = pIterator->pNext)
    {
        pInstance = pIterator;
    }

    return pInstance ? pInstance->pObj : NULL;
}


/***************************************************/
/*********** Super super class: Object *************/
/***************************************************/
struct Object_Fld { CHAINDECLARE; };

static void Equal(void* _pThis, va_list vlArgs)
{
    Object* pThis = _pThis;

    bool *pRet = va_arg(vlArgs, bool *);
    void *pToCompare = va_arg(vlArgs, void *);

    *pRet = ConvertToExactType(pThis->pFld->__pChain, pThis) == pToCompare;
}

static void ToString(void* _pThis, va_list vlArgs)
{
    Object* pThis = _pThis;

    printf("%p", ConvertToExactType(pThis->pFld->__pChain, pThis));
}

static bool __CALL(Object)(Object *pSelf, const char *pMethodName, ...)
{
    DOCALL(pSelf, pMethodName);
}

static void *__EXTEND(Object)(Object *pSelf)
{
    DOEXTEND(pSelf);
}

void __DEL(Object)(Object *pInst)
{
    DestroyInstanceChain(pInst->pFld->__pChain);
}

Object* __NEW(Object)()
{
	Object* pNew = NULL;
	{
		void* __Methods = NULL;
		{
			__Methods = GenerateMethodRing();
			if (!__Methods) { return NULL; }

			if (!InsertMethod(__Methods, GenerateMethod(Equal, "Equal"))) { return NULL; }
			if (!InsertMethod(__Methods, GenerateMethod(ToString, "ToString"))) { return NULL; }
		}

		Object_Fld* __Fld = NULL;
		{
			__Fld = malloc(sizeof(Object_Fld));
			if (!__Fld) { DestroyMethodRing(__Methods); return NULL; }
		}

		Object* __New = NULL;
		{
			__New = malloc(sizeof(Object));
			if (!__New) { DestroyMethodRing(__Methods); free(__Fld); return NULL; }

			__New->pFld = __Fld;
			__New->Extend = __EXTEND(Object);
			__New->Call = __CALL(Object);
		}

		void* __Chain = NULL;
		{
			__Chain = GenerateInstanceChain();
			if (!__Chain) { DestroyMethodRing(__Methods); free(__Fld); free(__New); return NULL; }

			__Fld->__pChain = __Chain;
		}

		void* __Instance = NULL;
		{
			__Instance = GenerateInstance(__New, __Fld, "Object", NULL, __Methods);
			if (!__Instance) { DestroyMethodRing(__Methods); free(__New); free(__Fld); DestroyInstanceChain(__Chain); return NULL; }

			InsertInstance(__Chain, __Instance);
		}

		pNew = __New;
	}

	return pNew;
}
