
#include "Calculator.h"

#include <malloc.h>

struct Calculator
{
	CHAINDEF;

	double dblOperandL;
	double dblOperandR;

	double dblResult;
};

////////////////////////////////////////////////////////////////////////////////////
//

static void Input(void* pParams)
{
	Calculator* pThis = ((ParamIn*)pParams)->pInst;
	Calculator_Input* pIn = ((ParamIn*)pParams)->pIn;

	pThis->dblOperandL = pIn->dblOpL;
	pThis->dblOperandR = pIn->dblOpR;
}

static void Add(void* pParams)
{
	Calculator* pThis = ((ParamIn*)pParams)->pInst;
	Calculator_Add* pIn = ((ParamIn*)pParams)->pIn;

	pThis->dblResult = pThis->dblOperandL + pThis->dblOperandR;
}

static void Output(void* pParams)
{
	Calculator* pThis = ((ParamIn*)pParams)->pInst;
	Calculator_Output* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pThis->dblResult;
}

static void Subtract(void* pParams)
{
	Calculator* pThis = ((ParamIn*)pParams)->pInst;
	Calculator_Subtract* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pIn->dblOpL - pIn->dblOpR;
}

static void Multiply(void* pParams)
{
	Calculator* pThis = ((ParamIn*)pParams)->pInst;
	Calculator_Multiply* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pIn->dblOpL * pIn->dblOpR;
}

////////////////////////////////////////////////////////////////////////////////////
//

void INVOKE(Calculator)(Calculator* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(Calculator)(Calculator* pInst)
{
    DOEXTEND(pInst);
}

void DELETE(Calculator)(Calculator** ppInst)
{
    DODELETE(ppInst, Calculator, Object);
}

Calculator* CREATE(Calculator)()
{
    DOCREATE(pCreate, Calculator, Object, NULL,
        METHOD(Input)
        METHOD(Add)
        METHOD(Output)
        METHOD(Subtract));

	return pCreate;
}