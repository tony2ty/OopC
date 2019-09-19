
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
    //fnExec����Ϊnull�������ֳ����¿��ܻ����
    //һ�����������ΪpName�ķ�����
    //����û�и�������ʵ�֣�
    //����������ʵ�֣�
    //�൱����ΪpName�ķ���Ϊ���󷽷�

	if (!pName || !*pName) { return NULL; }

	void* pMem = malloc(strlen(pName) + 1);
	Method* pRet = malloc(sizeof(Method));

	if (!pMem || !pRet)
	{
		free(pRet);
		free(pMem);

		return NULL;
	}

	pRet->pPrev = NULL; //�²����� �����ṹ�� ���뽫���ֶ���Ϊnull���ж���Ҫ�õ�
	pRet->pNext = NULL; //�²����� �����ṹ�� ���뽫���ֶ���Ϊnull���ж���Ҫ�õ�
	pRet->fnExec = fnExec;
	pRet->pName = strcpy(pMem, pName);

	return pRet;
}

MethodRing* GenerateMethodRing()
{
	MethodRing* pRet = malloc(sizeof(MethodRing));

    if (!pRet) { return NULL; }

	pRet->pHead = NULL; //�²����� �������ṹ�� ���뽫���ֶ���Ϊnull���ж���Ҫ�õ�
	pRet->pTail = NULL; //�²����� �������ṹ�� ���뽫���ֶ���Ϊnull���ж���Ҫ�õ�

	return pRet;
}

MethodRing * InsertMethod(MethodRing * pMethods, int nMethodNum, ...)
{
    if (!pMethods) { return NULL; }
    if (nMethodNum <= 0) { return pMethods; }

    va_list methods;
    va_start(methods, nMethodNum);

    //pMethods->pHead && !pMethods->pTail || !pMethods->pHead && pMethods->pTail == true �����쳣���

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
    //��ʹ��û�г�Ա������
    //������Ҳֻ��˵��0Ԫ�أ�
    //������Ϊnull��
    //Ҳ����pMethods����Ϊnull

    if (!pFields || !pName || !*pName || !pMethods) { return NULL; }

	void* pMem = malloc(strlen(pName) + 1);
	Instance* pRet = malloc(sizeof(Instance));

	if (!pRet || !pMem)
	{
		free(pRet);
		free(pMem);

		return NULL;
	}

	pRet->pPrev = NULL; //�²����� ʵ���ṹ�� ���뽫���ֶ���Ϊnull���ж���Ҫ�õ�
	pRet->pNext = NULL; //�²����� ʵ���ṹ�� ���뽫���ֶ���Ϊnull���ж���Ҫ�õ�
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

	pRet->pHead = NULL; //�²����� ʵ�����ṹ�� ���뽫���ֶ���Ϊnull���ж���Ҫ�õ�
	pRet->pTail = NULL; //�²����� ʵ�����ṹ�� ���뽫���ֶ���Ϊnull���ж���Ҫ�õ�

	return pRet;
}

InstanceChain* InsertInstance(InstanceChain* pChain, Instance* pInstance)
{
    if (pChain && !pInstance) { return pChain; }
    if (!pChain) { return NULL; }

    //pChain->pHead && !pChain->pTail || !pChain->pHead && pChain->pTail == true �����쳣���

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
    if (!pFindInst) { return; } //û���ҵ���˵��������ʵ��pInst������Ӧ�����ʵ��

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
	//�����ͷ�ÿ��ʵ��
	Instance* pItrInst = pChain->pHead;
	do
	{
		//�ͷ���ʵ���ĸ��Ӵ洢
        if (pItrInst->pExtRef && pItrInst->pExtRef->fnExec)
        {
            pItrInst->pExtRef->fnExec(pItrInst->pExtRef->pToClear);
            free(pItrInst->pExtRef);
        }
		//�ͷ�ʵ��������
		free(pItrInst->pFields);
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
