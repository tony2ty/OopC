
#define OOPLIB_API __declspec(dllexport)
#include "OopBase.h"

#include <string.h>
#include <malloc.h>
#include <stdio.h>

////OopBase//////////////////////////////////////////////////////////////////////////////
//

struct ExtraMemRef
{
	void* pToClear;
	ExtraMemClear fnExec;
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

	char* pName;
	Transit fnExec;
};

struct MethodRing
{
	Method* pHead;
	Method* pTail;
};

Method* GenerateMethod(Transit fnExec, char* pName)
{
    //fnExec可能为null，在这种场景下可能会出现
    //一个类添加了名为pName的方法，
    //但是没有给出具体实现，
    //而是让子类实现，
    //相当于名为pName的方法为抽象方法

	if (!pName || !*pName) { return NULL; }

	void* pMem = malloc(strlen(pName) + 1);
	Method* pRet = malloc(sizeof(Method));

	if (!pMem || !pRet)
	{
		free(pRet);
		free(pMem);

		return NULL;
	}

	pRet->pPrev = NULL; //新产生的 方法结构体 必须将该字段设为null，判断需要用到
	pRet->pNext = NULL; //新产生的 方法结构体 必须将该字段设为null，判断需要用到
	pRet->fnExec = fnExec;
	pRet->pName = strcpy(pMem, pName);

	return pRet;
}

MethodRing* GenerateMethodRing()
{
	MethodRing* pRet = malloc(sizeof(MethodRing));

    if (!pRet) { return NULL; }

	pRet->pHead = NULL; //新产生的 方法环结构体 必须将该字段设为null，判断需要用到
	pRet->pTail = NULL; //新产生的 方法环结构体 必须将该字段设为null，判断需要用到

	return pRet;
}

MethodRing * InsertMethod(MethodRing * pMethods, int nMethodNum, ...)
{
    if (!pMethods) { return NULL; }
    if (nMethodNum <= 0) { return pMethods; }

    va_list methods;
    va_start(methods, nMethodNum);

    //pMethods->pHead && !pMethods->pTail || !pMethods->pHead && pMethods->pTail == true 属于异常情况

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

	char* pName;
	void* pFields;
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
    //即使类没有成员方法，
    //方法环也只能说是0元素，
    //而不能为null，
    //也就是pMethods不能为null

    if (!pFields || !pName || !*pName || !pMethods) { return NULL; }

	void* pMem = malloc(strlen(pName) + 1);
	Instance* pRet = malloc(sizeof(Instance));

	if (!pRet || !pMem)
	{
		free(pRet);
		free(pMem);

		return NULL;
	}

	pRet->pPrev = NULL; //新产生的 实例结构体 必须将该字段设为null，判断需要用到
	pRet->pNext = NULL; //新产生的 实例结构体 必须将该字段设为null，判断需要用到
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

	pRet->pHead = NULL; //新产生的 实例链结构体 必须将该字段设为null，判断需要用到
	pRet->pTail = NULL; //新产生的 实例链结构体 必须将该字段设为null，判断需要用到

	return pRet;
}

InstanceChain* InsertInstance(InstanceChain* pChain, Instance* pInstance)
{
    if (pChain && !pInstance) { return pChain; }
    if (!pChain) { return NULL; }

    //pChain->pHead && !pChain->pTail || !pChain->pHead && pChain->pTail == true 属于异常情况

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
    if (!pFindInst) { return; } //没有找到，说明给定的实例pInst不是相应的类的实例

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
		//释放类实例的附加存储
        if (pItrInst->pExtRef && pItrInst->pExtRef->fnExec)
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
	Delete((*ppInst)->pChain);
    *ppInst = NULL;
}

Object* CREATE(Object)()
{
	Object* pCreate = malloc(sizeof(Object));
    if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
    if (!pMethods) { return NULL; }

    pMethods = InsertMethod(pMethods, 2,
        GenerateMethod(Equal, "Equal"),
        GenerateMethod(ToString, "ToString"));
	pCreate->pChain = InsertInstance(GenerateInstanceChain(), GenerateInstance(pCreate, TYPE(Object), NULL, pMethods));

	return pCreate;
}
