
#include "ILoggerFactory.h"

#include <malloc.h>

struct ILoggerFactory
{
	CHAINDEF;
};

////////////////////////////////////////////////////////////////////////
//

////////////////////////////////////////////////////////////////////////
//

void INVOKE(ILoggerFactory)(ILoggerFactory* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(ILoggerFactory)(ILoggerFactory* pInst)
{
	return pInst->pChain;
}

void DELETE(ILoggerFactory)(ILoggerFactory** ppInst)
{
	//

	Object* pSuper = SWITCH((*ppInst), ILoggerFactory, Object);
	DELETE(Object)(&pSuper);
	(*ppInst) = NULL;
}

ILoggerFactory* CREATE(ILoggerFactory)()
{
	ILoggerFactory* pCreate = malloc(sizeof(ILoggerFactory));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

	pMethods =
		  InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(NULL, "CreateLogger"))
		->pRing;
	pCreate->pChain = InsertInstance(EXTEND(Object)(CREATE(Object)()), GenerateInstance(pCreate, "ILoggerFactory", pMethods));

	return pCreate;
}
