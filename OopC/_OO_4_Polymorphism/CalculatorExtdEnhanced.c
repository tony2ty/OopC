
#include "CalculatorExtdEnhanced.h"

#include <malloc.h>

struct CalculatorExtdEnhanced
{
	CHAINDEF;
};

///////////////////////////////////////////////////////////////////////////
//

static void Add(void* pParams)
{
	CalculatorExtdEnhanced* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExtdEnhanced_Add* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pIn->dblOpL + pIn->dblOpR + 1;
}

static void Subtract(void* pParams)
{
	CalculatorExtdEnhanced* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExtdEnhanced_Subtract* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pIn->dblOpL - pIn->dblOpR + 1;
}

static void Multiply(void* pParams)
{
	CalculatorExtdEnhanced* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExtdEnhanced_Multiply* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pIn->dblOpL * pIn->dblOpR + 1;
}

static void Divide(void* pParams)
{
	CalculatorExtdEnhanced* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExtdEnhanced_Divide* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pIn->dblOpL / pIn->dblOpR + 1;// */0
}

///////////////////////////////////////////////////////////////////////////
//

void INVOKE(CalculatorExtdEnhanced)(CalculatorExtdEnhanced* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(CalculatorExtdEnhanced)(CalculatorExtdEnhanced* pInst)
{
	return pInst->pChain;
}

void DELETE(CalculatorExtdEnhanced)(CalculatorExtdEnhanced** ppInst)
{
	//

	CalculatorBase* pSuper = SWITCH((*ppInst), CalculatorExtdEnhanced, CalculatorBase);
	DELETE(CalculatorBase)(&pSuper);
    (*ppInst) = NULL;
}

CalculatorExtdEnhanced* CREATE(CalculatorExtdEnhanced)()
{
	CalculatorExtdEnhanced* pCreate = malloc(sizeof(CalculatorExtdEnhanced));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

	pMethods =
		  InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Add, "Add"))
		->InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Subtract, "Subtract"))
		->InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Multiply, "Multiply"))
		->InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Divide, "Divide"))
		->pRing;
	pCreate->pChain = InsertInstance(EXTEND(CalculatorBase)(CREATE(CalculatorBase)()), GenerateInstance(pCreate, "CalculatorExtdEnhanced", pMethods));

	return pCreate;
}