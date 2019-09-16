
#include "CalculatorExt.h"

#include <malloc.h>
#include "Calculator.h"

struct CalculatorExt
{
	CHAINDEF;
};

/////////////////////////////////////////////////////////////////////////////////////////
//

static void Add(void* pParams)
{
	CalculatorExt* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExt_Add* pIn = ((ParamIn*)pParams)->pIn;

	//这里类似于对象组合技术中的调用转发
	DOINVOKESUPER(pThis, "Input", &(Calculator_Input) { pIn->dblOpL, pIn->dblOpR });
	DOINVOKESUPER(pThis, "Add", NULL);
	DOINVOKESUPER(pThis, "Output", &(Calculator_Output){pIn->pdblRet});
}

static void Subtract(void* pParams)
{
	CalculatorExt* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExt_Subtract* pIn = ((ParamIn*)pParams)->pIn;

	//调用转发
	DOINVOKESUPER(pThis, "Subtract", pIn);
}

static void Multiply(void* pParams)
{
	CalculatorExt* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExt_Multiply* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pIn->dblOpL * pIn->dblOpR;
}

static void Divide(void* pParams)
{
	CalculatorExt* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExt_Divide* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pIn->dblOpL / pIn->dblOpR;//除0.。。
}

/////////////////////////////////////////////////////////////////////////////////////////
//

void INVOKE(CalculatorExt)(CalculatorExt* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(CalculatorExt)(CalculatorExt* pInst)
{
	return pInst->pChain;
}

void DELETE(CalculatorExt)(CalculatorExt** ppInst)
{
	Calculator* pSuper = SWITCH((*ppInst), CalculatorExt, Calculator);
	DELETE(Calculator)(&pSuper);
}

CalculatorExt* CREATE(CalculatorExt)()
{
	CalculatorExt* pCreate = malloc(sizeof(CalculatorExt));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

	pMethods =
		  InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Add, "Add"))
		->InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Subtract, "Subtract"))
		->InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Multiply, "Multiply"))
		->InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Divide, "Divide"))
		->pRing;
	pCreate->pChain = InsertInstance(EXTEND(Calculator)(CREATE(Calculator)()), GenerateInstance(pCreate, "CalculatorExt", pMethods));

	return pCreate;
}
