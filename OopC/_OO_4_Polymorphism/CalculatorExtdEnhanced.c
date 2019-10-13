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

bool INVOKE(CalculatorExtdEnhanced)(CalculatorExtdEnhanced* pInst, char* pFuncName, void* pParams)
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
