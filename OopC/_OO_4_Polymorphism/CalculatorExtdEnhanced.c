
#include "CalculatorExtdEnhanced.h"

#include <stdio.h>
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

    printf("Add operation using enhanced calculator.\n");

	*pIn->pdblRet = pIn->dblOpL + pIn->dblOpR;
}

static void Subtract(void* pParams)
{
	CalculatorExtdEnhanced* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExtdEnhanced_Subtract* pIn = ((ParamIn*)pParams)->pIn;

    printf("Subtract operation using enhanced calculator.\n");

	*pIn->pdblRet = pIn->dblOpL - pIn->dblOpR;
}

static void Multiply(void* pParams)
{
	CalculatorExtdEnhanced* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExtdEnhanced_Multiply* pIn = ((ParamIn*)pParams)->pIn;

    printf("multiply operation using enhanced calculator.\n");

	*pIn->pdblRet = pIn->dblOpL * pIn->dblOpR;
}

static void Divide(void* pParams)
{
	CalculatorExtdEnhanced* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExtdEnhanced_Divide* pIn = ((ParamIn*)pParams)->pIn;

    printf("divide operation using enhanced calculator.\n");

	*pIn->pdblRet = pIn->dblOpL / pIn->dblOpR;// */0
}

///////////////////////////////////////////////////////////////////////////
//

void INVOKE(CalculatorExtdEnhanced)(CalculatorExtdEnhanced* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(CalculatorExtdEnhanced)(CalculatorExtdEnhanced* pInst)
{
    DOEXTEND(pInst);
}

void DELETE(CalculatorExtdEnhanced)(CalculatorExtdEnhanced** ppInst)
{
    DODELETE(ppInst, CalculatorExtdEnhanced, CalculatorBase);
}

CalculatorExtdEnhanced* CREATE(CalculatorExtdEnhanced)()
{
    DOCREATE(pCreate, CalculatorExtdEnhanced, CalculatorBase, NULL,
        METHOD(Add)
        METHOD(Subtract)
        METHOD(Multiply)
        METHOD(Divide));

	return pCreate;
}
