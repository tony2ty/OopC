
#define OOPLIB_API __declspec(dllexport)
#include "OopBase.h"

#include <string.h>
#include <malloc.h>
#include <stdio.h>

////OopBase//////////////////////////////////////////////////////////////////////////////
//

struct Method
{
	Method* pPrev;
	Method* pNext;

	Transit pAddr;
	char* pName;
};

struct MethodRing
{
	Method* pHead;
	Method* pTail;
};

Method* GenerateMethod(Transit pAddr, char* pName)
{
    if (!pAddr || !pName || !*pName) { return NULL; }

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
	pRet->pAddr = pAddr;
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

MethodUtil* InsertMethod(MethodUtil* pUtil, Method* pMethod)
{
    if (pUtil && pUtil->InsertMethod && pUtil->pRing && !pMethod) { return pUtil; }

    if (!pUtil || !pUtil->InsertMethod || !pUtil->pRing) { return NULL; }

	if (pUtil->pRing->pHead && pUtil->pRing->pTail)
	{
		pMethod->pPrev = pUtil->pRing->pTail;
		pMethod->pNext = pUtil->pRing->pHead;

		pUtil->pRing->pHead->pPrev = pMethod;
		pUtil->pRing->pTail->pNext = pMethod;

		pUtil->pRing->pTail = pMethod;

		return pUtil;
	}

	if (!pUtil->pRing->pHead && !pUtil->pRing->pTail)
	{
		pMethod->pNext = pMethod;
		pMethod->pPrev = pMethod;

		pUtil->pRing->pHead = pMethod;
		pUtil->pRing->pTail = pMethod;

		return pUtil;
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////
//

struct Instance
{
	Instance* pPrev;
	Instance* pNext;

	void* pFileds;
	char* pName;
	MethodRing* pMethods;
};

struct InstanceChain
{
	Instance* pHead;
	Instance* pTail;
};

Instance* GenerateInstance(void* pFields, char* pName, MethodRing* pMethods)
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
	pRet->pFileds = pFields;
	pRet->pName = strcpy(pMem, pName);
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
        if (pIterator->pFileds == pInst) { return pIterator; }
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
        toExecute = pFindMthd ? pFindMthd->pAddr : toExecute;
	}

	if (!toExecute)
	{
		for (Instance* pIterator = pFindInst->pPrev; pIterator; pIterator->pPrev)
		{
            Method* pFindMthd = FindMethod(pIterator->pMethods, pFuncName);
			if (pFindMthd)
			{
				toExecute = pFindMthd->pAddr;
				break;
			}
		}
	}

    if (toExecute)
    {
        toExecute(pParams);
    }
}

void* AsBase(InstanceChain* pChain, void* pInst, char* pBaseType)
{
	if (!pChain || !pInst || !pBaseType || !*pBaseType)
	{
#ifdef ___DEBUG
		printf("Null input IN AsBase().\n");
#endif // ___DEBUG

		return NULL;
	}

	for (Instance* pIterator = FindInstance(pChain, pInst); pIterator; pIterator = pIterator->pPrev)
	{
		if (!strcmp(pIterator->pName, pBaseType))
		{
			return pIterator->pFileds;
		}
	}

	return NULL;
}

void* AsBaseByFunc(InstanceChain* pChain, void* pInst, char* pFuncName)
{
	if (!pChain || !pInst || !pFuncName || !*pFuncName)
	{
#ifdef ___DEBUG
		printf("Null input IN AsBaseByFunc().\n");
#endif // ___DEBUG

		return NULL;
	}

	Instance* pRet = NULL;
	Instance* pFindInst = FindInstance(pChain, pInst);

	if (!pFindInst)
	{
#ifdef ___DEBUG
		printf("No instance found IN AsBaseByFunc().\n");
#endif // ___DEBUG

		return NULL;
	}

	//1.先在当前类中查找，确定是否存在指定的方法
	pRet = FindMethod(pFindInst->pMethods, pFuncName) ? pFindInst : pRet;

	//2.再在子类中查找方法
	for (Instance* pIterator = pFindInst->pNext; pIterator; pIterator = pIterator->pNext)
	{
		pRet = FindMethod(pIterator->pMethods, pFuncName) ? pIterator : pRet;
	}

	//3.子类中如果包含指定的方法，则执行该方法，
	//  如果子类中没有，则查找父类是否有继承的方法
	if (!pRet)
	{
		for (Instance* pIterator = pFindInst->pPrev; pIterator; pIterator->pPrev)
		{
			if (FindMethod(pIterator->pMethods, pFuncName))
			{
				pRet = pIterator;
				break;
			}
		}
	}

	if (!pRet)
	{
#ifdef ___DEBUG
		printf("The no valid instance found IN AsBaseByFunc().\n");
#endif // ___DEBUG

		return NULL;
	}
	else
	{
		return pRet->pFileds;
	}
}

void* AsExactType(InstanceChain* pChain, void* pInst)
{
	if (!pChain || !pInst)
	{
#ifdef ___DEBUG
		printf("Null input IN AsExactType().\n");
#endif // ___DEBUG

		return NULL;
	}

	Instance* pItrInst = FindInstance(pChain, pInst);
	do
	{
		if (!pItrInst->pNext)
		{
			return pItrInst->pFileds;
		}

		pItrInst = pItrInst->pNext;

	} while (true);
}

void Delete(InstanceChain* pChain)
{
	//迭代释放每个实例
	Instance* pItrInst = pChain->pHead;
	do
	{
		//释放实例数据域
		free(pItrInst->pFileds);
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
	InstanceChain* pChain;
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

void    Invoke_Object(Object* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void*   Extend_Object(Object* pInst)
{
	return pInst->pChain;
}

void    Delete_Object(Object** ppInst)
{
	//释放当前类数据域中动态分配的内存

	Delete((*ppInst)->pChain);
}

Object* Create_Object()
{
	Object* pCreate = NULL;
	pCreate = malloc(sizeof(Object));

	if (!pCreate)
	{
		goto MemErr;
	}

	MethodRing* pMethods = NULL;
	pMethods = GenerateMethodRing();
	pMethods =
		InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Equal, "Equal"))
	  ->InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(ToString, "ToString"))
	  ->pRing;
	pCreate->pChain = InsertInstance(GenerateInstanceChain(), GenerateInstance(pCreate, "Object", pMethods));

	return pCreate;

MemErr:
#ifdef ___DEBUG
	printf("Failed to allocate memory IN Create_Object().\n");
#endif // ___DEBUG

	return NULL;
}
