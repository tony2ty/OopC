
#include "Penguin.h"

#include <stdio.h>
#include <malloc.h>
#include <stddef.h>

struct Penguin
{
	InstanceChain* pChain;
};

/////////////////////////////////////////////////////////////
//

/////////////////////////////////////////////////////////////
//

void  INVOKE(Penguin)(Penguin* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(Penguin)(Penguin* pInst)
{
	return pInst->pChain;
}

void  DELETE(Penguin)(Penguin** ppInst)
{
	Animal* pSuper = AsBase((*ppInst)->pChain, *ppInst, TYPE(Animal));
	DELETE(Animal)(&pSuper);
}

Penguin* CREATE(Penguin)(const char* pName, int nID)
{
	Penguin* pCreate = malloc(sizeof(Penguin));
	if (!pCreate)
	{
		goto MemErr;
	}

	MethodRing* pMethods = NULL;
	pMethods = GenerateMethodRing();
	pCreate->pChain = InsertInstance(EXTEND(Animal)(CREATE(Animal)(pName, nID)), GenerateInstance(pCreate, "Penguin", pMethods));
	return pCreate;

MemErr:
#ifdef ___DEBUG
	printf("Failed to allocate memory IN Penguin_Create().\n");
#endif // ___DEBUG


	return NULL;
}
