
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

	//���������ڶ�����ϼ����еĵ���ת��
	DOINVOKESUPER(pThis, "Input", &(Calculator_Input) { pIn->dblOpL, pIn->dblOpR });
	DOINVOKESUPER(pThis, "Add", NULL);
	DOINVOKESUPER(pThis, "Output", &(Calculator_Output){pIn->pdblRet});
}

//static void Subtract(void* pParams);//ֱ�Ӽ̳�

static void Multiply(void* pParams)
{
	CalculatorExt* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExt_Multiply* pIn = ((ParamIn*)pParams)->pIn;

	//����ת��
	DOINVOKESUPER(pThis, "Multiply", pIn);
}

static void Divide(void* pParams)
{
	CalculatorExt* pThis = ((ParamIn*)pParams)->pInst;
	CalculatorExt_Divide* pIn = ((ParamIn*)pParams)->pIn;

	*pIn->pdblRet = pIn->dblOpL / pIn->dblOpR;//��0.����
}

/////////////////////////////////////////////////////////////////////////////////////////
//

void INVOKE(CalculatorExt)(CalculatorExt* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(CalculatorExt)(CalculatorExt* pInst)
{
    DOEXTEND(pInst);
}

void DELETE(CalculatorExt)(CalculatorExt** ppInst)
{
    DODELETE(ppInst, CalculatorExt, Calculator);
}

CalculatorExt* CREATE(CalculatorExt)()
{
    DOCREATE(pCreate, CalculatorExt, Calculator, NULL,
        METHOD(Add)
        METHOD(Multiply)
        METHOD(Divide));

	return pCreate;
}
