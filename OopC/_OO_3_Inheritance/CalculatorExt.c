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

    *pIn->pdblRet = pIn->dblOpL + pIn->dblOpR;
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

bool INVOKE(CalculatorExt)(CalculatorExt* pInst, char* pFuncName, void* pParams)
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
