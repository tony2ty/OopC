
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
	return pInst->pChain;
}

void DELETE(Calculator)(Calculator** ppInst)
{
	Object* pSuper = SWITCH((*ppInst), Calculator, Object);
	DELETE(Object)(&pSuper);
    (*ppInst) = NULL;
}

Calculator* CREATE(Calculator)()
{
	Calculator* pCreate = malloc(sizeof(Calculator));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

    pMethods = InsertMethod(pMethods, 4,
        GenerateMethod(Input, "Input"),
        GenerateMethod(Add, "Add"),
        GenerateMethod(Output, "Output"),
        GenerateMethod(Subtract, "Subtract"));
	pCreate->pChain = InsertInstance(EXTEND(Object)(CREATE(Object)()), GenerateInstance(pCreate, "Calculator", NULL, pMethods));

	return pCreate;
}