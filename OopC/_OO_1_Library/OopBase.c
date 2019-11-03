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

////OopBase//////////////////////////////////////////////////////////////////////////////
//

//---������Ϣ-----------------------------------------------------------------------------------//

char *pErrorBuffer = NULL;

char * GetErrorInfo(char * pMemIn)
{
    if (!pErrorBuffer) { return pMemIn; }

    int nLen = strlen(pErrorBuffer) + 1;
    return memcpy(realloc(pMemIn, nLen), pErrorBuffer, nLen);
}

void SetErrorInfo(char *pErrorInfo)
{
    if (!pErrorInfo || !*pErrorInfo) { return; }
    
    int nLen = strlen(pErrorInfo) + 1;
    pErrorBuffer = memcpy(realloc(pErrorBuffer, nLen), pErrorInfo, nLen);
}

///////////////////////////////////////////////////////////////////////////////////
//

//---�ڴ��ͷ�-----------------------------------------------------------------------------------//

typedef void(* Releaser)(void*);
typedef struct ReleaserRef ReleaserRef;
typedef struct ReleaserRefList ReleaserRefList;

struct ReleaserRef
{
    ReleaserRef *pPrev;
    ReleaserRef *pNext;

	void* pToClear;
    Releaser fnRelease;
};

struct ReleaserRefList
{
    ReleaserRef *pHead;
    ReleaserRef *pTail;
};

void* GenerateReleaserRef(void* pfnRelease, void* pToClear)
{
    Releaser fnRelease = pfnRelease;

    if (!fnRelease || !pToClear) { return NULL; }

    ReleaserRef* pRet = malloc(sizeof(ReleaserRef));
	if (!pRet) { return NULL; }

    pRet->pPrev = NULL;
    pRet->pNext = NULL;
	pRet->fnRelease = fnRelease;
	pRet->pToClear = pToClear;

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

void* InsertReleaserRef(void *pVdList, void *pVdRlsRef)
{
    ReleaserRefList *pList = pVdList;
    ReleaserRef *pRlsRef = pVdRlsRef;

    if (!pList || !pRlsRef || !pRlsRef->fnRelease) { return pList; }

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

void CallReleaser(void *pVdList)
{
    ReleaserRefList *pList = pVdList;

    if (!pList) { return; }

    for (ReleaserRef *pIterator = pList->pHead; pIterator; pIterator = pIterator->pNext)
    {
        if (pIterator->fnRelease)
        {
            (pIterator->fnRelease)(pIterator->pToClear);
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

///////////////////////////////////////////////////////////////////////////////////
//

//---ʵ����������-----------------------------------------------------------------------------------//

//��Ա������׼����
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

void* GenerateMethod(Transit fnExec, char* pName)
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

void* GenerateMethodRing()
{
	MethodRing* pRet = malloc(sizeof(MethodRing));

    if (!pRet) { return NULL; }

	pRet->pHead = NULL; //�²����� �������ṹ�� ���뽫���ֶ���Ϊnull���ж���Ҫ�õ�
	pRet->pTail = NULL; //�²����� �������ṹ�� ���뽫���ֶ���Ϊnull���ж���Ҫ�õ�

	return pRet;
}

void * InsertMethod(void * pVdMethods, int nMethodNum, ...)
{
    MethodRing *pMethods = pVdMethods;

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

//---ʵ������ʵ��-----------------------------------------------------------------------------------//

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
	pRet->pRlsRef = pRlsRef;
	pRet->pMethods = pMethods;

	return pRet;
}

void* GenerateInstanceChain()
{
	InstanceChain* pRet = malloc(sizeof(InstanceChain));

    if (!pRet) { return NULL; }

	pRet->pHead = NULL; //�²����� ʵ�����ṹ�� ���뽫���ֶ���Ϊnull���ж���Ҫ�õ�
	pRet->pTail = NULL; //�²����� ʵ�����ṹ�� ���뽫���ֶ���Ϊnull���ж���Ҫ�õ�

	return pRet;
}

void* InsertInstance(void* pVdChain, void* pVdInstance)
{
    InstanceChain *pChain = pVdChain;
    Instance *pInstance = pVdInstance;

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

//---ʵ��������󣬸�������-----------------------------------------------------------------------------------//

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
        //�����ҵ��Ŀ�����һ�����󷽷���
        //Ҳ���ǣ�������pRing�д��ڸ÷��������Ƿ�����ָ��Ϊnull��
        //��Ҳ������ContainMethod��FindMethod�����������ܺϲ�Ϊһ������
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

//---ʵ���������-----------------------------------------------------------------------------------//

bool Invoke(void* pVdChain, void* pInst, char* pFuncName, void* pParams)
{
    InstanceChain *pChain = pVdChain;

    if (!pChain || !pChain->pHead || !pChain->pTail || !pInst || !pFuncName || !*pFuncName)
    {
        SetErrorInfo("Null pChain or pInst or pFuncName.");
        return false;
    }

	Transit toExecute = NULL;

	Instance* pFindInst = FindInstance(pChain, pInst);
    if (!pFindInst) //û���ҵ���˵��������ʵ��pInst������Ӧ�����ʵ��
    {
        SetErrorInfo("Given object is not an instance of given type.");
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
        //ͨ������ָ��������෽��ʱ����Ҫ��֤���㸸���д��ڸ÷���������
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
                SetErrorInfo("Invalid call because the declaration type of instance has no given method.");
                return false;
            }
        }
    }
    else
    {
        SetErrorInfo("Given instance has not given func.");
        return false;
    }
}

bool InvokeSuper(void* pVdChain, void* pInst, char* pFuncName, void* pParams)
{
    InstanceChain *pChain = pVdChain;

	if (!pChain || !pChain->pHead || !pChain->pTail || !pInst || !pFuncName || !*pFuncName)
    {
        SetErrorInfo("Null pChain or pInst or pFuncName.");
        return false;
    }

	Transit toExecute = NULL;

	Instance* pFindInst = FindInstance(pChain, pInst);
	if (!pFindInst)
    {
        SetErrorInfo("Given object is not an instance of given type.");
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
        SetErrorInfo("Given instance has not given func.");
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
        if (pItrInst->pRlsRef && pItrInst->pRlsRef->fnRelease)
        {
            pItrInst->pRlsRef->fnRelease(pItrInst->pRlsRef->pToClear);
            free(pItrInst->pRlsRef);
        }
		//�ͷ�ʵ��������
		free(pItrInst->pFields);
		//�ͷ�����
		free(pItrInst->pName);
		//�ͷŷ��������ͷŷ�����
        if (pItrInst->pMethods->pHead && pItrInst->pMethods->pTail)
        {
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
        }
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

//---�������Object����-----------------------------------------------------------------------------------//

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

bool INVOKE(Object)(Object* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(Object)(Object* pInst)
{
    DOEXTEND(pInst);
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
	pCreate->pChain = InsertInstance(GenerateInstanceChain(), GenerateInstance(pCreate, "Object", NULL, pMethods));

	return pCreate;
}
