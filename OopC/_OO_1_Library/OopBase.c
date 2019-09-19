
#define OOPLIB_API __declspec(dllexport)
#include "OopBase.h"

#include <string.h>
#include <malloc.h>
#include <stdio.h>

////OopBase//////////////////////////////////////////////////////////////////////////////
//

struct ExtraMemRef
{
	ExtraMemClear fnExec;
	void* pToClear;
};

ExtraMemRef* GenerateExtraMemRef(ExtraMemClear fnExec, void* pToClear)
{
    if (!fnExec || !pToClear) { return NULL; }

	ExtraMemRef* pRet = malloc(sizeof(ExtraMemRef));
	if (!pRet) { return NULL; }

	pRet->fnExec = fnExec;
	pRet->pToClear = pToClear;

	return pRet;
}

///////////////////////////////////////////////////////////////////////////////////
//

struct Method
{
	Method* pPrev;
	Method* pNext;

	Transit fnExec;
	char* pName;
};

struct MethodRing
{
	Method* pHead;
	Method* pTail;
};

Method* GenerateMethod(Transit fnExec, char* pName)
{
    //if (!pAddr || !pName || !*pName) { return NULL; }
	if (!pName || !*pName) { return NULL; }

	void* pMem = malloc(strlen(pName) + 1);
	Method* pRet = malloc(sizeof(Method));

	if (!pMem || !pRet)
	{
		free(pRet);
		free(pMem);

		return NULL;
	}

	pRet->pPrev = NULL;
	pRet->pNext = NULL;
	pRet->fnExec = fnExec; //可能为null
	pRet->pName = strcpy(pMem, pName);

	return pRet;
}

MethodRing* GenerateMethodRing()
{
	MethodRing* pRet = malloc(sizeof(MethodRing));

    if (!pRet) { return NULL; }

	pRet->pHead = NULL;
	pRet->pTail = NULL;

	return pRet;
}

MethodRing * InsertMethod(MethodRing * pMethods, int nMethodNum, ...)
{
    if (!pMethods) { return NULL; }
    if (nMethodNum <= 0) { return pMethods; }

    va_list methods;
    va_start(methods, nMethodNum);

    //pMethods->pHead && !pMethods->pTail || !pMethods->pHead && pMethods->pTail 属于异常情况

    if (!pMethods->pHead && !pMethods->pTail)
    {
        Method *pMethod = va_arg(methods, Method *);
        pMethod->pNext = pMethod;
        pMethod->pPrev = pMethod;

        pMethods->pHead = pMethod;
        pMethods->pTail = pMethod;

        nMethodNum--;
    }

    for (int i = 0; i < nMethodNum; i++)
    {
        Method *pMethod = va_arg(methods, Method *);

        pMethod->pPrev = pMethods->pTail;
        pMethod->pNext = pMethods->pHead;

        pMethods->pHead->pPrev = pMethod;
        pMethods->pTail->pNext = pMethod;

        pMethods->pTail = pMethod;
    }

    va_end(methods);

    return pMethods;
}

//////////////////////////////////////////////////////////////////////////////////
//

struct Instance
{
	Instance* pPrev;
	Instance* pNext;

	void* pFields;
	char* pName;
	ExtraMemRef* pExtRef;
	MethodRing* pMethods;
};

struct InstanceChain
{
	Instance* pHead;
	Instance* pTail;
};

Instance* GenerateInstance(void* pFields, char* pName, ExtraMemRef *pExtRef, MethodRing* pMethods)
{
    if (!pFields || !pName || !*pName || !pMethods) { return NULL; }

	void* pMem = malloc(strlen(pName) + 1);
	Instance* pRet = malloc(sizeof(Instance));

	if (!pRet || !pMem)
	{
		free(pRet);
		free(pMem);

		return NULL;
	}

	pRet->pPrev = NULL;
	pRet->pNext = NULL;
	pRet->pFields = pFields;
	pRet->pName = strcpy(pMem, pName);
	pRet->pExtRef = pExtRef;
	pRet->pMethods = pMethods;

	return pRet;
}

InstanceChain* GenerateInstanceChain()
{
	InstanceChain* pRet = malloc(sizeof(InstanceChain));

    if (!pRet) { return NULL; }

	pRet->pHead = NULL;
	pRet->pTail = NULL;

	return pRet;
}

InstanceChain* InsertInstance(InstanceChain* pChain, Instance* pInstance)
{
    if (pChain && !pInstance) { return pChain; }

    if (!pChain) { return NULL; }

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

//////////////////////////////////////////////////////////////////////////////////
//

Method* FindMethod(MethodRing* pRing, char* pName)
{
    if (!pRing || !pRing->pHead || !pRing->pTail || !pName || !*pName) { return NULL; }

	Method* pIterator = pRing->pHead;
	do
	{
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

//////////////////////////////////////////////////////////////////////////////////
//

void Invoke(InstanceChain* pChain, void* pInst, char* pFuncName, void* pParams)
{
    if (!pChain || !pChain->pHead || !pChain->pTail || !pInst || !pFuncName || !*pFuncName) { return; }

	Transit toExecute = NULL;

	Instance* pFindInst = FindInstance(pChain, pInst);
    if (!pFindInst) { return; }

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
        toExecute(pParams);
    }
}

void InvokeSuper(InstanceChain* pChain, void* pInst, char* pFuncName, void* pParams)
{
	if (!pChain || !pChain->pHead || !pChain->pTail || !pInst || !pFuncName || !*pFuncName) { return; }

	Transit toExecute = NULL;

	Instance* pFindInst = FindInstance(pChain, pInst);
	if (!pFindInst) { return; }

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
	}
}

void* AsBaseByType(InstanceChain* pChain, void* pInst, char* pBaseType)
{
    if (!pChain || !pChain->pHead || !pChain->pTail || !pInst || !pBaseType || !*pBaseType) { return NULL; }

	for (Instance* pIterator = FindInstance(pChain, pInst); pIterator; pIterator = pIterator->pPrev)
	{
        if (!strcmp(pIterator->pName, pBaseType)) { return pIterator->pFields; }
	}

	return NULL;
}

void* AsBaseByFunc(InstanceChain* pChain, void* pInst, char* pFuncName)
{
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

void* AsBaseByFuncUpward(InstanceChain* pChain, void* pInst, char* pFuncName)
{
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

void* AsExactType(InstanceChain* pChain, void* pInst)
{
    if (!pChain || !pChain->pHead || !pChain->pTail || !pInst) { return NULL; }

    Instance *pTmpInst = NULL;
    for (Instance *pIterator = FindInstance(pChain, pInst); pIterator; pIterator = pIterator->pNext)
    {
        pTmpInst = pIterator;
    }

    return pTmpInst ? pTmpInst->pFields : NULL;
}

void Delete(InstanceChain* pChain)
{
	//迭代释放每个实例
	Instance* pItrInst = pChain->pHead;
	do
	{
		//
        if (pItrInst->pExtRef)
        {
            pItrInst->pExtRef->fnExec(pItrInst->pExtRef->pToClear);
            free(pItrInst->pExtRef);
        }
		//释放实例数据域
		free(pItrInst->pFields);
		//释放类名
		free(pItrInst->pName);
		//释放方法环：释放方法名
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

/////Object/////////////////////////////////////////////////////////////////////////////////
//

struct Object
{
    CHAINDEF;
};

static void Equal(void* pParams)
{
	Object* pThis = ((ParamIn*)pParams)->pInst;
	Object_Equal* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pRet = AsExactType(pThis->pChain, pThis) == pIn->pToCmpr;
}

static void ToString(void* pParams)
{
	Object* pThis = ((ParamIn*)pParams)->pInst;
	Object_ToString* pIn = ((ParamIn*)pParams)->pIn;

	printf("%p", AsExactType(pThis->pChain, pThis));
}

//////////////////////////////////////////////////////////////////////////////////////
//

void INVOKE(Object)(Object* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(Object)(Object* pInst)
{
	return pInst->pChain;
}

void DELETE(Object)(Object** ppInst)
{
	//释放当前类数据域中动态分配的内存

	Delete((*ppInst)->pChain);
    *ppInst = NULL;
}

Object* CREATE(Object)()
{
	Object* pCreate = malloc(sizeof(Object));
    if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
    if (!pMethods) { return NULL; }

    pMethods =
        InsertMethod(pMethods, 2,
            GenerateMethod(Equal, "Equal"),
            GenerateMethod(ToString, "ToString"));
	pCreate->pChain = InsertInstance(GenerateInstanceChain(), GenerateInstance(pCreate, TYPE(Object), NULL, pMethods));

	return pCreate;
}
