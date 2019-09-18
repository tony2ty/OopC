
#include "ILogger.h"

#include <malloc.h>

struct ILogger
{
	CHAINDEF;
};

//////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////
//

void INVOKE(ILogger)(ILogger* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(ILogger)(ILogger* pInst)
{
	return pInst->pChain;
}

void DELETE(ILogger)(ILogger** ppInst)
{
	//

	Object* pSuper = SWITCH((*ppInst), ILogger, Object);
	DELETE(Object)(&pSuper);
	(*ppInst) = NULL;
}

ILogger* CREATE(ILogger)()
{
	ILogger* pCreate = malloc(sizeof(ILogger));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

	pMethods =
		  InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(NULL, "WriteLog"))
		->pRing;
	pCreate->pChain = InsertInstance(EXTEND(Object)(CREATE(Object)()), GenerateInstance(pCreate, "ILogger", NULL, pMethods));

	return pCreate;
}
