
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

//static void Subtract(void* pParams);//直接继承

static void Multiply(void* pParams)
{
	CalculatorExt* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExt_Multiply* pIn = ((ParamIn*)pParams)->pIn;

	//调用转发
	DOINVOKESUPER(pThis, "Multiply", pIn);
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
	*ppInst = NULL;
}

CalculatorExt* CREATE(CalculatorExt)()
{
	CalculatorExt* pCreate = malloc(sizeof(CalculatorExt));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

    pMethods = InsertMethod(pMethods, 3,
        GenerateMethod(Add, "Add"),
        GenerateMethod(Multiply, "Multiply"),
        GenerateMethod(Divide, "Divide"));
	pCreate->pChain = InsertInstance(EXTEND(Calculator)(CREATE(Calculator)()), GenerateInstance(pCreate, "CalculatorExt", NULL, pMethods));

	return pCreate;
}
