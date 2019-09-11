
#define OOPLIB_API __declspec(dllexport)
#include "OopBase.h"

#include <string.h>
#include <malloc.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////////
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
	if (!pAddr || !pName || !*pName)
	{
#ifdef ___DEBUG
		printf("Null input IN GenerateMethod().\n");
#endif // ___DEBUG

		return NULL;
	}

	void* pMem = malloc(strlen(pName) + 1);
	Method* pRet = malloc(sizeof(Method));

	if (!pMem || !pRet)
	{
#ifdef ___DEBUG
		printf("Failed to allocate memory IN GenerateMethod().\n");
#endif // ___DEBUG

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

	if (!pRet)
	{
#ifdef ___DEBUG
		printf("Failed to allocate memory IN GenerateMethodRing().\n");
#endif // ___DEBUG

		return NULL;
	}

	pRet->pHead = NULL;
	pRet->pTail = NULL;

	return pRet;
}

MethodUtil* InsertMethod(MethodUtil* pUtil, Method* pMethod)
{
	if (pUtil && pUtil->InsertMethod && pUtil->pRing && !pMethod)
	{
#ifdef ___DEBUG
		printf("No method inserted.\n");
#endif // ___DEBUG

		return pUtil;
	}

	if (!pUtil || !pUtil->InsertMethod || !pUtil->pRing)
	{
#ifdef ___DEBUG
		printf("Null Input IN InsertMethod().\n");
#endif // ___DEBUG

		return NULL;
	}

	//����Ϊnull����ζ���Ѿ�������һ��Ԫ��
	if (pUtil->pRing->pHead && pUtil->pRing->pTail)
	{
		pMethod->pPrev = pUtil->pRing->pTail;
		pMethod->pNext = pUtil->pRing->pHead;

		pUtil->pRing->pHead->pPrev = pMethod;
		pUtil->pRing->pTail->pNext = pMethod;

		pUtil->pRing->pTail = pMethod;

		return pUtil;
	}

	//��Ϊnull����ζ�Ų����һ��Ԫ��
	if (!pUtil->pRing->pHead && !pUtil->pRing->pTail)
	{
		pMethod->pNext = pMethod;
		pMethod->pPrev = pMethod;

		pUtil->pRing->pHead = pMethod;
		pUtil->pRing->pTail = pMethod;

		return pUtil;
	}

	//pHead��pTail��һ��Ϊnull��Ϊ�쳣���
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
	if (!pFields || !pName || !*pName || !pMethods)
	{
#ifdef ___DEBUG
		printf("Null input IN GenerateInstance().\n");
#endif // ___DEBUG

		return NULL;
	}

	void* pMem = malloc(strlen(pName) + 1);
	Instance* pRet = malloc(sizeof(Instance));

	if (!pRet || !pMem)
	{
#ifdef ___DEBUG
		printf("Failed to allocate memory IN GenerateInstance().\n");
#endif // ___DEBUG

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

	if (!pRet)
	{
#ifdef ___DEBUG
		printf("Failed to allocate memory IN GenerateInstanceChain().\n");
#endif // ___DEBUG

		return NULL;
	}

	pRet->pHead = NULL;
	pRet->pTail = NULL;

	return pRet;
}

InstanceChain* InsertInstance(InstanceChain* pChain, Instance* pInstance)
{
	if (pChain && !pInstance)
	{
#ifdef ___DEBUG
		printf("No instance inserted.\n");
#endif // ___DEBUG

		return pChain;
	}

	if (!pChain)
	{
#ifdef ___DEBUG
		printf("Null input IN InsertInstance().\n");
#endif // ___DEBUG

		return NULL;
	}

	//1.����������һ��Ԫ��
	if (pChain->pHead && pChain->pTail)
	{
		pInstance->pPrev = pChain->pTail;
		pInstance->pNext = NULL;

		pChain->pTail->pNext = pInstance;

		pChain->pTail = pInstance;

		return pChain;
	}

	//2.����û��Ԫ�أ�����һ��Ԫ��
	if (!pChain->pHead && !pChain->pTail)
	{
		pInstance->pPrev = NULL;
		pInstance->pNext = NULL;

		pChain->pHead = pInstance;
		pChain->pTail = pInstance;

		return pChain;
	}

	//3.pHead��pTail��һ��Ϊnull��Ϊ�쳣���
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////
//

Method* FindMethod(MethodRing* pRing, char* pName)
{
	if (!pRing || !pRing->pHead || !pRing->pTail || !pName || !*pName)
	{
#ifdef ___DEBUG
		printf("Null input IN FindMethod().\n");
#endif // ___DEBUG

		return NULL;
	}

	Method* pIterator = pRing->pHead;
	do
	{
		if (!strcmp(pName, pIterator->pName))
		{
			return pIterator;
		}
		pIterator = pIterator->pNext;

	} while (pIterator != pRing->pHead);

	return NULL;
}

Instance* FindInstance(InstanceChain* pChain, void* pInst)
{
	if (!pChain || !pInst)
	{
#ifdef ___DEBUG
		printf("Null input IN FindInstance().\n");
#endif // ___DEBUG

		return NULL;
	}

	Instance* pIterator = pChain->pHead;
	do
	{
		if (pIterator->pFileds == pInst)
		{
			return pIterator;
		}
		pIterator = pIterator->pNext;

	} while (pIterator != NULL);

	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////
//

void Invoke(InstanceChain* pChain, void* pInst, char* pFuncName, void* pParams)
{
	if (!pChain || !pInst || !pFuncName || !*pFuncName)
	{
#ifdef ___DEBUG
		printf("Null input IN Invoke().\n");
#endif // ___DEBUG

		return;
	}

	Transit toExecute = NULL;
	Instance* pFindInst = FindInstance(pChain, pInst);

	if (!pFindInst)
	{
#ifdef ___DEBUG
		printf("No instance found IN Invoke().\n");
#endif // ___DEBUG

		return;
	}

	Method* pFindMthd = NULL;
	//1.���ڵ�ǰ���в���ָ���ķ���
	pFindMthd = FindMethod(pFindInst->pMethods, pFuncName);
	if (pFindMthd)
	{
		toExecute = pFindMthd->pAddr;
	}

	//2.���������в��ҷ���
	for (Instance* pIterator = pFindInst->pNext; pIterator; pIterator = pIterator->pNext)
	{
		pFindMthd = FindMethod(pIterator->pMethods, pFuncName);
		if (pFindMthd)
		{
			toExecute = pFindMthd->pAddr;
		}
	}

	//3.�������������ָ���ķ�������ִ�и÷�����
	//  ���������û�У�����Ҹ����Ƿ��м̳еķ���
	if (!toExecute)
	{
		for (Instance* pIterator = pFindInst->pPrev; pIterator; pIterator->pPrev)
		{
			pFindMthd = FindMethod(pIterator->pMethods, pFuncName);
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
	else
	{
#ifdef ___DEBUG
		printf("The specified method not found IN Invoke().\n");
#endif // ___DEBUG
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

void Delete(InstanceChain* pChain)
{
	//�����ͷ�ÿ��ʵ��
	Instance* pItrInst = pChain->pHead;
	do
	{
		//�ͷ�ʵ��������
		free(pItrInst->pFileds);
		//�ͷ�����
		free(pItrInst->pName);
		//�ͷŷ��������ͷŷ�����
		Method* pItrMthd = pItrInst->pMethods->pHead;
		do
		{
			free(pItrMthd->pName);
			pItrMthd = pItrMthd->pNext;

		} while (pItrMthd != pItrInst->pMethods->pHead);
		//�ͷŷ��������ͷŷ����ṹ��
		pItrMthd = pItrInst->pMethods->pHead;
		do
		{
			void* pVd = pItrMthd->pNext;
			free(pItrMthd);
			pItrMthd = pVd;

		} while (pItrMthd != pItrInst->pMethods->pHead);
		//�ͷŷ��������ͷŻ�ͷ
		free(pItrInst->pMethods);

		pItrInst = pItrInst->pNext;

	} while (pItrInst != NULL);

	//�ͷ���
	pItrInst = pChain->pHead;
	do
	{
		void* pVd = pItrInst->pNext;
		free(pItrInst);
		pItrInst = pVd;

	} while (pItrInst != NULL);

	free(pChain);
}


