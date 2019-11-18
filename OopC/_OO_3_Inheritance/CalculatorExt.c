//MIT License
//
//Copyright(c) 2019 Goodman Tao
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.


#include "CalculatorExt.h"


struct CalculatorExt_Fld
{
	CHAINDECLARE;
};

/////////////////////////////////////////////////////////////////////////////////////////
//

static void Add(ParamIn* pParams)
{
	CalculatorExt* pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	double dblOpL = va_arg(vlArgs, double);
	double dblOpR = va_arg(vlArgs, double);
	double* pdblRet = va_arg(vlArgs, double*);

    *pdblRet = dblOpL + dblOpR;
}

//static void Subtract(void* pParams);//直接继承

OVERRIDE static void Multiply(ParamIn* pParams)
{
	CalculatorExt* pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	double dblOpL = va_arg(vlArgs, double);
	double dblOpR = va_arg(vlArgs, double);
	double* pdblRet = va_arg(vlArgs, double*);

	//调用转发
	Calculator* pSuper = SWITCH(pThis, Calculator);
	pSuper->Call(pSuper, "Multiply", dblOpL, dblOpR, pdblRet);
}

static void Divide(ParamIn* pParams)
{
	CalculatorExt* pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	double dblOpL = va_arg(vlArgs, double);
	double dblOpR = va_arg(vlArgs, double);
	double* pdblRet = va_arg(vlArgs, double*);

	*pdblRet = dblOpL / dblOpR;//除0.。。
}

/////////////////////////////////////////////////////////////////////////////////////////
//

static bool __CALL(CalculatorExt)(CalculatorExt* pSelf, const char* pMethodName, ...)
{
	DOCALL(pSelf, pMethodName);
}

static void* __EXTEND(CalculatorExt)(CalculatorExt* pSelf)
{
	DOEXTEND(pSelf);
}

void __DEL(CalculatorExt)(CalculatorExt* pSelf)
{
	DODEL(pSelf, Calculator);
}

CalculatorExt* __NEW(CalculatorExt)()
{
	DONEW(pNew, CalculatorExt, Calculator, NULL,
		METHOD(Add)
		METHOD(Multiply)
		METHOD(Divide));

	return pNew;
}
