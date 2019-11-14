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


#define OOPLIB_API __declspec(dllexport)
#include "OopBase.h"

#include <string.h>
#include <stdio.h>

/**********************************************************/
/*********** Simple api for memory releasing **************/
/**********************************************************/
typedef void(* Releaser)(void*);
typedef struct ReleaserRef ReleaserRef;
typedef struct ReleaserRefList ReleaserRefList;
struct ReleaserRef
{
    ReleaserRef *pPrev;
    ReleaserRef *pNext;

    bool bMutable;
	void* pToClear;
    Releaser fnRelease;
};
struct ReleaserRefList
{
    ReleaserRef *pHead;
    ReleaserRef *pTail;
};
void* GenerateReleaserRef(void(*pfnRelease)(void *), void* pToClear, bool bMutable)
{
    Releaser fnRelease = pfnRelease;

    if (!fnRelease || !pToClear) { return NULL; }

    ReleaserRef* pRet = malloc(sizeof(ReleaserRef));
	if (!pRet) { return NULL; }

    pRet->pPrev = NULL;
    pRet->pNext = NULL;
	pRet->fnRelease = fnRelease;
	pRet->pToClear = pToClear;
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
void   DestroyReleaserRefList(void *pVdList)
{
    ReleaserRefList *pList = pVdList;

    if (!pList) { return; }

    for (ReleaserRef *pIterator = pList->pHead; pIterator; pIterator = pIterator->pNext)
    {
        if (pIterator->fnRelease)
        {
            if (pIterator->bMutable)
            {
                pIterator->fnRelease(*(void **)(pIterator->pToClear));
            }
            else
            {
                pIterator->fnRelease(pIterator->pToClear);
            }
        }
    }

    while (pList->pHead)
    {
        ReleaserRef *pTmp = pList->pHead;
        pList->pHead = pList->pHead->pNext;
        free(pTmp);
    }

    free(pList);
}
void*   InsertReleaserRef(void *pVdList, void *pVdRlsRef)
{
    ReleaserRefList *pList = pVdList;
    ReleaserRef *pRlsRef = pVdRlsRef;

    //no need to set if-clause here.
    //if (!pList || !pRlsRef || !pRlsRef->fnRelease) { return pList; }

    if (pList->pHead && pList->pTail)
    {
        pList->pTail->pNext = pRlsRef;
        pRlsRef->pPrev = pList->pTail;
        pRlsRef->pNext = NULL;
        pList->pTail = pRlsRef;

        return pList;
    }

    if (!pList->pHead && !pList->pTail)
    {
        pRlsRef->pPrev = NULL;
        pRlsRef->pNext = NULL;
        pList->pHead = pRlsRef;
        pList->pTail = pRlsRef;

        return pList;
    }

    return NULL;
}


/**********************************************************/
/********* Implements of functions of OOP *****************/
/**********************************************************/

//1.datastructure and api
typedef void(*Transit)(void*);
typedef struct Method Method;
typedef struct MethodRing MethodRing;
struct Method
{
	Method* pPrev;
	Method* pNext;

	char* pName;
	Transit fnExec;
};
struct MethodRing
{
	Method* pHead;
	Method* pTail;
};
void* GenerateMethod(void(*pfnAddr)(void *), char* pName)
{
    Transit fnExec = pfnAddr;

    //fnExec can be NULL when generating abstract method.
    //pName CAN'T be NULL, so there's no need to judge with if clause;
	//if (!pName || !*pName) { return NULL; }

	void* pMem = malloc(strlen(pName) + 1);
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
	pRet->pName = strcpy(pMem, pName);

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
void   DestroyMethodRing(void* pVdMethods)
{
    MethodRing* pMethods = pVdMethods;

    //pMethods cannot be null if this func called.

    if (pMethods->pHead != NULL && pMethods->pTail != NULL)
    {
        pMethods->pHead->pPrev = NULL;
        pMethods->pTail->pNext = NULL;

        for (Method *pIt = pMethods->pHead; pIt;)
        {
            Method* pTmp = pIt->pNext;
            free(pIt->pName);
            free(pIt);
            pIt = pTmp;
        }

        free(pMethods);
        return;
    }

    if (pMethods->pHead == NULL && pMethods->pTail == NULL)
    {
        free(pMethods);
    }
}
void*   InsertMethod(void* pVdMethods, void* pVdMethod)
{
	MethodRing* pMethods = pVdMethods;
	Method* pMethod = pVdMethod;

    //pMethods can't be null, 
    //because pre-judgement has been made when calling this func.
	if (pMethod == NULL)
	{
        DestroyMethodRing(pMethods);
		return NULL;
	}

    //no need to consider this kind of situation:
	//pMethods->pHead && !pMethods->pTail || !pMethods->pHead && pMethods->pTail == true

	if (pMethods->pHead && pMethods->pTail)
	{
		pMethod->pPrev = pMethods->pTail;
		pMethod->pNext = pMethods->pHead;

		pMethods->pHead->pPrev = pMethod;
		pMethods->pTail->pNext = pMethod;

		pMethods->pTail = pMethod;

		return pMethods;
	}

	if (!pMethods->pHead && !pMethods->pTail)
	{
		pMethod->pNext = pMethod;
		pMethod->pPrev = pMethod;

		pMethods->pHead = pMethod;
		pMethods->pTail = pMethod;

		return pMethods;
	}

	return NULL;
}

typedef struct Instance Instance;
typedef struct InstanceChain InstanceChain;
struct Instance
{
	Instance* pPrev;
	Instance* pNext;

	char* pName;
	void* pFields;
    ReleaserRef* pRlsRef;
	MethodRing* pMethods;
};
struct InstanceChain
{
	Instance* pHead;
	Instance* pTail;
};
void* GenerateInstance(void* pFields, char* pName, void *pVdRlsRef, void* pVdMethods)
{
    MethodRing *pMethods = pVdMethods;
    ReleaserRef *pRlsRef = pVdRlsRef;

    //these params can't be null
    //if (!pFields || !pName || !*pName || !pMethods) { return NULL; }

	void* pMem = malloc(strlen(pName) + 1);
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
	pRet->pFields = pFields;
	pRet->pName = strcpy(pMem, pName);
	pRet->pRlsRef = pRlsRef;
	pRet->pMethods = pMethods;

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
void   DestroyInstanceChain(void* pVdChain)
{
    InstanceChain *pChain = pVdChain;

    //迭代释放每个实例
    Instance* pItrInst = pChain->pHead;
    do
    {
        //释放类实例的附加存储
        if (pItrInst->pRlsRef && pItrInst->pRlsRef->fnRelease)
        {
            if (pItrInst->pRlsRef->bMutable)
            {
                pItrInst->pRlsRef->fnRelease(*(void **)(pItrInst->pRlsRef->pToClear));
            }
            else
            {
                pItrInst->pRlsRef->fnRelease(pItrInst->pRlsRef->pToClear);
            }
            free(pItrInst->pRlsRef);
        }
        //释放实例数据域
        free(pItrInst->pFields);
        //释放类名
        free(pItrInst->pName);
        //释放方法环：释放方法名
        if (pItrInst->pMethods->pHead && pItrInst->pMethods->pTail)
        {
            Method* pItrMthd = pItrInst->pMethods->pHead;
            do
            {
                free(pItrMthd->pName);
                pItrMthd = pItrMthd->pNext;

            } while (pItrMthd != pItrInst->pMethods->pHead);
            //释放方法环：释放方法结构体
            pItrMthd = pItrInst->pMethods->pHead;
            do
            {
                void* pVd = pItrMthd->pNext;
                free(pItrMthd);
                pItrMthd = pVd;

            } while (pItrMthd != pItrInst->pMethods->pHead);
        }
        //释放方法环：释放环头
        free(pItrInst->pMethods);

        pItrInst = pItrInst->pNext;

    } while (pItrInst != NULL);

    //释放链
    pItrInst = pChain->pHead;
    do
    {
        void* pVd = pItrInst->pNext;
        free(pItrInst);
        pItrInst = pVd;

    } while (pItrInst != NULL);

    free(pChain);
}
void*   InsertInstance(void* pVdChain, void* pVdInstance)
{
    InstanceChain *pChain = pVdChain;
    Instance *pInstance = pVdInstance;

	if (pChain == NULL)
	{
		if (pInstance != NULL)
		{
			if (pInstance->pRlsRef != NULL && pInstance->pRlsRef->fnRelease != NULL)
			{
				pInstance->pRlsRef->fnRelease(pInstance->pRlsRef->pToClear);

				free(pInstance->pRlsRef);
			}

			pInstance->pMethods->pTail->pNext = NULL;
			while (pInstance->pMethods->pHead)
			{
				Method* pTmp = pInstance->pMethods->pHead;
				pInstance->pMethods->pHead = pInstance->pMethods->pHead->pNext;

				free(pTmp->pName);
				free(pTmp);
			}
			free(pInstance->pMethods);
			
			free(pInstance->pFields);
			free(pInstance->pName);
			free(pInstance);
		}
		return NULL;
	}
	if (pInstance == NULL)
	{
		if (pChain->pHead == NULL)
		{
			free(pChain);
		}
		else
		{
			DestroyInstanceChain(pChain);
		}
		return NULL;
	}

    //this kind of situation can't occur:
    //pChain->pHead && !pChain->pTail || !pChain->pHead && pChain->pTail == true

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

//2.oop rules and some operations like simple error handling
int  nInvokeErrorCode = INVKSUCCESS;
int  GetInvokeRetCode()
{
	return nInvokeErrorCode;
}
void ResetInvokeRetCode()
{
	nInvokeErrorCode = INVKSUCCESS;
}

bool ContainMethod(MethodRing *pRing, char *pName)
{
    if (!pRing || !pRing->pHead || !pRing->pTail || !pName || !*pName) { return false; }

    Method *pIterator = pRing->pHead;
    do
    {
        if (!strcmp(pName, pIterator->pName)) { return true; }
        pIterator = pIterator->pNext;

    } while (pIterator != pRing->pHead);

    return false;
}
Method* FindMethod(MethodRing* pRing, char* pName)
{
    if (!pRing || !pRing->pHead || !pRing->pTail || !pName || !*pName) { return NULL; }

	Method* pIterator = pRing->pHead;
	do
	{
        //这里找到的可能是一个抽象方法，
        //也就是，方法换pRing中存在该方法，但是方法的指针为null，
        //这也导致了ContainMethod和FindMethod两个函数不能合并为一个函数
        if (!strcmp(pName, pIterator->pName)) { return pIterator; }
		pIterator = pIterator->pNext;

	} while (pIterator != pRing->pHead);

	return NULL;
}
Instance* FindInstance(InstanceChain* pChain, void* pInst)
{
    if (!pChain || !pChain->pHead || !pChain->pTail || !pInst) { return NULL; }

	Instance* pIterator = pChain->pHead;
	do
	{
        if (pIterator->pFields == pInst) { return pIterator; }
		pIterator = pIterator->pNext;

	} while (pIterator != NULL);

	return NULL;
}

bool Invoke(void* pVdChain, void* pInst, char* pFuncName, void* pParams)
{
    InstanceChain *pChain = pVdChain;

    if (!pChain || !pChain->pHead || !pChain->pTail || !pInst || !pFuncName || !*pFuncName)
    {
		nInvokeErrorCode = INVKNULLPARAM;
        return false;
    }

	Transit toExecute = NULL;

	Instance* pFindInst = FindInstance(pChain, pInst);
    if (!pFindInst) //没有找到，说明给定的实例pInst不是相应的类的实例
    {
		nInvokeErrorCode = INVKINSTNOTFOUND;
        return false;
    }

	for (Instance* pIterator = pFindInst; pIterator; pIterator = pIterator->pNext)
	{
        Method* pFindMthd = FindMethod(pIterator->pMethods, pFuncName);
        toExecute = pFindMthd ? pFindMthd->fnExec : toExecute;
	}

	if (!toExecute)
	{
		for (Instance* pIterator = pFindInst->pPrev; pIterator; pIterator = pIterator->pPrev)
		{
            Method* pFindMthd = FindMethod(pIterator->pMethods, pFuncName);
			if (pFindMthd)
			{
				toExecute = pFindMthd->fnExec;
				break;
			}
		}
	}

    if (toExecute)
    {
        //通过父类指针调用子类方法时，需要保证各层父类中存在该方法的声明
        if (!pFindInst->pNext)
        {
            toExecute(pParams);

            return true;
        }
        else
        {
            bool bValidCall = false;
            for (Instance *pIterator = pFindInst; pIterator; pIterator = pIterator->pPrev)
            {
                if (ContainMethod(pIterator->pMethods, pFuncName))
                {
                    bValidCall = true;
                    break;
                }
            }

            if (bValidCall)
            {
                toExecute(pParams);

                return true;
            }
            else
            {
				nInvokeErrorCode = INVKNOSUCHMETHOD1;
                return false;
            }
        }
    }
    else
    {
		nInvokeErrorCode = INVKNOSUCHMETHOD2;
        return false;
    }
}
bool InvokeSuper(void* pVdChain, void* pInst, char* pFuncName, void* pParams)
{
    InstanceChain *pChain = pVdChain;

	if (!pChain || !pChain->pHead || !pChain->pTail || !pInst || !pFuncName || !*pFuncName)
    {
		nInvokeErrorCode = INVKNULLPARAM;
        return false;
    }

	Transit toExecute = NULL;

	Instance* pFindInst = FindInstance(pChain, pInst);
	if (!pFindInst)
    {
		nInvokeErrorCode = INVKINSTNOTFOUND;
        return false;
    }

	for (Instance *pIterator = pFindInst->pPrev; pIterator; pIterator = pIterator->pPrev)
	{
		Method* pFindMthd = FindMethod(pIterator->pMethods, pFuncName);
		if (pFindMthd)
		{
			toExecute = pFindMthd->fnExec;
			break;
		}
	}

	if (toExecute)
	{
		toExecute(pParams);

        return true;
    }
    else
    {
		nInvokeErrorCode = INVKNOSUCHMETHOD2;
        return false;
    }
}
void* ConvertByType(void* pVdChain, void* pInst, char* pBaseType)
{
    InstanceChain *pChain = pVdChain;

    if (!pChain || !pChain->pHead || !pChain->pTail || !pInst || !pBaseType || !*pBaseType) { return NULL; }

	for (Instance* pIterator = FindInstance(pChain, pInst); pIterator; pIterator = pIterator->pPrev)
	{
        if (!strcmp(pIterator->pName, pBaseType)) { return pIterator->pFields; }
	}

	return NULL;
}
void* ConvertByFunc(void* pVdChain, void* pInst, char* pFuncName)
{
    InstanceChain *pChain = pVdChain;

    if (!pChain || !pChain->pHead || !pChain->pTail || !pInst || !pFuncName || !*pFuncName) { return NULL; }

	Instance* pTmpInst = NULL;
	Instance* pFindInst = FindInstance(pChain, pInst);

    if (!pFindInst) { return NULL; }

	for (Instance* pIterator = pFindInst; pIterator; pIterator = pIterator->pNext)
	{
        pTmpInst = FindMethod(pIterator->pMethods, pFuncName) ? pIterator : pTmpInst;
	}

	if (!pTmpInst)
	{
		for (Instance* pIterator = pFindInst->pPrev; pIterator; pIterator = pIterator->pPrev)
		{
			if (FindMethod(pIterator->pMethods, pFuncName))
			{
                pTmpInst = pIterator;
				break;
			}
		}
	}

    return pTmpInst ? pTmpInst->pFields : NULL;
}
void* ConvertByFuncInherited(void* pVdChain, void* pInst, char* pFuncName)
{
    InstanceChain *pChain = pVdChain;

	if (!pChain || !pChain->pHead || !pChain->pTail || !pInst || !pFuncName || !*pFuncName) { return NULL; }

	Instance* pFindInst = FindInstance(pChain, pInst);
	if (!pFindInst) { return NULL; }

	for (Instance *pIterator = pFindInst->pPrev; pIterator; pIterator = pIterator->pPrev)
	{
		if (FindMethod(pIterator->pMethods, pFuncName))
		{
			return pIterator->pFields;
		}
	}

	return NULL;
}
void* ConvertToExactType(InstanceChain* pChain, void* pInst)
{
    if (!pChain || !pChain->pHead || !pChain->pTail || !pInst) { return NULL; }

    Instance *pTmpInst = NULL;
    for (Instance *pIterator = FindInstance(pChain, pInst); pIterator; pIterator = pIterator->pNext)
    {
        pTmpInst = pIterator;
    }

    return pTmpInst ? pTmpInst->pFields : NULL;
}


/***************************************************/
/*********** Super super class: Object *************/
/***************************************************/
struct Object
{
    CHAINDEF;
};
static void Equal(void* pParams)
{
	Object* pThis = ((ParamIn*)pParams)->pInst;
	Object_Equal* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pRet = ConvertToExactType(pThis->pChain, pThis) == pIn->pToCmpr;
}
static void ToString(void* pParams)
{
	Object* pThis = ((ParamIn*)pParams)->pInst;
	Object_ToString* pIn = ((ParamIn*)pParams)->pIn;

	printf("%p", ConvertToExactType(pThis->pChain, pThis));
}

bool INVOKE(Object)(Object* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}
void* EXTEND(Object)(Object* pInst)
{
    DOEXTEND(pInst);
}
void DELETE(Object)(Object* pInst)
{
	DestroyInstanceChain(pInst->pChain);
}
Object* CREATE(Object)()
{
	Object* pCreate = malloc(sizeof(Object));
    if (pCreate == NULL) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (pMethods == NULL)
	{
		free(pCreate);
		return NULL;
	}

	if (InsertMethod(pMethods, GenerateMethod(Equal, "Equal")) == NULL
	  ||InsertMethod(pMethods, GenerateMethod(ToString, "ToString")) == NULL)
	{
        free(pCreate);
		return NULL;
	}

	pCreate->pChain = InsertInstance(GenerateInstanceChain(), GenerateInstance(pCreate, "Object", NULL, pMethods));
	if (pCreate->pChain == NULL) { return NULL; }

	return pCreate;
}
