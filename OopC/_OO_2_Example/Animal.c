
#include "Animal.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Animal
{
	InstanceChain* pChain;
	char* pName;
	int nID;
};

////////////////////////////////////////////////////////////////////////////////
//

static void Eat(void* pParams)
{
	Animal* pThis = ((ParamIn*)pParams)->pInst;
	Animal_Eat* pIn = ((ParamIn*)pParams)->pIn;

	printf("%s 正在吃.\n", pThis->pName);
}

static void Sleep(void* pParams)
{
	Animal* pThis = ((ParamIn*)pParams)->pInst;
	Animal_Sleep* pIn = ((ParamIn*)pParams)->pIn;

	printf("%s 正在睡.\n", pThis->pName);
}

static void Introduce(void* pParams)
{
	Animal* pThis = ((ParamIn*)pParams)->pInst;
	Animal_Introduce* pIn = ((ParamIn*)pParams)->pIn;

	printf("大家好， 我是 %d 号， %s.\n", pThis->nID, pThis->pName);
}

////////////////////////////////////////////////////////////////////////////////
//

void INVOKE(Animal)(Animal* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(Animal)(Animal* pInst)
{
	return pInst->pChain;
}

void DELETE(Animal)(Animal** ppInst)
{
	//释放当前类动态分配的内存
	free((*ppInst)->pName);

	Object* pSuper = AsBase((*ppInst)->pChain, *ppInst, TYPE(Object));
	DELETE(Object)(&pSuper);
}

Animal* CREATE(Animal)(const char* pName, int nID)
{
	Animal* pCreate = NULL;
	pCreate = malloc(sizeof(Animal));
	if (pCreate)
	{
		pCreate->nID = nID;
		pCreate->pName = malloc(strlen(pName) + 1);
		if (pCreate->pName)
		{
			pCreate->pName = strcpy(pCreate->pName, pName);
		}
		else
		{
			goto MemErr;
		}
	}
	else
	{
		goto MemErr;
	}

	MethodRing* pMethods = NULL;
	pMethods = GenerateMethodRing();
	pMethods =
		InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Eat, "Eat"))
	  ->InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Sleep, "Sleep"))
	  ->InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Introduce, "Introduce"))
	  ->pRing;
	pCreate->pChain = InsertInstance(EXTEND(Object)(CREATE(Object)()), GenerateInstance(pCreate, "Animal", pMethods));

	return pCreate;

MemErr:
#ifdef ___DEBUG
	printf("Failed to allocate memory IN Create_Animal().\n");
#endif // ___DEBUG

	return NULL;
}
