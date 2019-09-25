
#include "CalculatorExtdCommon.h"

#include <malloc.h>

struct CalculatorExtdCommon
{
	CHAINDEF;
};

/////////////////////////////////////////////////////////////////////////////
//

static void Add(void* pParams)
{
	CalculatorExtdCommon* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExtdCommon_Add* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pIn->dblOpL + pIn->dblOpR;
}

static void Subtract(void* pParams)
{
	CalculatorExtdCommon* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExtdCommon_Subtract* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pIn->dblOpL - pIn->dblOpR;
}

static void Multiply(void* pParams)
{
	CalculatorExtdCommon* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExtdCommon_Multiply* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pIn->dblOpL * pIn->dblOpR;
}

static void Divide(void* pParams)
{
	CalculatorExtdCommon* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExtdCommon_Divide* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pIn->dblOpL / pIn->dblOpR;// */0
}

/////////////////////////////////////////////////////////////////////////////
//

void INVOKE(CalculatorExtdCommon)(CalculatorExtdCommon* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(CalculatorExtdCommon)(CalculatorExtdCommon* pInst)
{
	return pInst->pChain;
}

void DELETE(CalculatorExtdCommon)(CalculatorExtdCommon** ppInst)
{
	CalculatorBase* pSuper = SWITCH((*ppInst), CalculatorExtdCommon, CalculatorBase);
	DELETE(CalculatorBase)(&pSuper);
	*ppInst = NULL;
}

CalculatorExtdCommon* CREATE(CalculatorExtdCommon)()
{
	CalculatorExtdCommon* pCreate = malloc(sizeof(CalculatorExtdCommon));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

    pMethods = InsertMethod(pMethods, 4,
        GenerateMethod(Add, "Add"),
        GenerateMethod(Subtract, "Subtract"),
        GenerateMethod(Multiply, "Multiply"),
        GenerateMethod(Divide, "Divide"));
	pCreate->pChain = InsertInstance(EXTEND(CalculatorBase)(CREATE(CalculatorBase)()), GenerateInstance(pCreate, "CalculatorExtdCommon", NULL, pMethods));

	return pCreate;
}
