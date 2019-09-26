
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
    DOEXTEND(pInst);
}

void DELETE(CalculatorExtdCommon)(CalculatorExtdCommon** ppInst)
{
    DODELETE(ppInst, CalculatorExtdCommon, CalculatorBase);
}

CalculatorExtdCommon* CREATE(CalculatorExtdCommon)()
{
    DOCREATE(pCreate, CalculatorExtdCommon, CalculatorBase, NULL,
        METHOD(Add)
        METHOD(Subtract)
        METHOD(Multiply)
        METHOD(Divide));

	return pCreate;
}
