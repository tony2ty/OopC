
#include "CalculatorBase.h"

#include <malloc.h>

struct CalculatorBase
{
	CHAINDEF;
};

//////////////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////////////
//

void INVOKE(CalculatorBase)(CalculatorBase* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(CalculatorBase)(CalculatorBase* pInst)
{
	return pInst->pChain;
}

void DELETE(CalculatorBase)(CalculatorBase** ppInst)
{
	//

	Object* pSuper = SWITCH((*ppInst), CalculatorBase, Object);
	DELETE(Object)(&pSuper);
}

CalculatorBase* CREATE(CalculatorBase)()
{
	CalculatorBase* pCreate = malloc(sizeof(CalculatorBase));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

	pMethods =
		  InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(NULL, "Add"))
		->InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(NULL, "Subtract"))
		->InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(NULL, "Multiply"))
		->InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(NULL, "Divide"))
		->pRing;
	pCreate->pChain = InsertInstance(EXTEND(Object)(CREATE(Object)()), GenerateInstance(pCreate, "CalculatorBase", pMethods));

	return pCreate;
}
