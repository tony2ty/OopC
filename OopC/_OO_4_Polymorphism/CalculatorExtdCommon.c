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


#include "CalculatorExtdCommon.h"

#include <stdio.h>

struct CalculatorExtdCommon_Fld
{
    CHAINDECLARE;
};

/////////////////////////////////////////////////////////////////////////////
//

OVERRIDE static void Add(ParamIn* pParams)
{
    CalculatorExtdCommon* pThis = pParams->pThis;
    va_list vlArgs = pParams->vlArgs;

    double dblOpL = va_arg(vlArgs, double);
    double dblOpR = va_arg(vlArgs, double);
    double* pdblRet = va_arg(vlArgs, double*);

    printf("Add operation using common calculator.\n");

	*pdblRet = dblOpL + dblOpR;
}

OVERRIDE static void Subtract(ParamIn* pParams)
{
    CalculatorExtdCommon* pThis = pParams->pThis;
    va_list vlArgs = pParams->vlArgs;

    double dblOpL = va_arg(vlArgs, double);
    double dblOpR = va_arg(vlArgs, double);
    double* pdblRet = va_arg(vlArgs, double*);

    printf("Subtract operation using common calculator.\n");

	*pdblRet = dblOpL - dblOpR;
}

OVERRIDE static void Multiply(ParamIn* pParams)
{
    CalculatorExtdCommon* pThis = pParams->pThis;
    va_list vlArgs = pParams->vlArgs;

    double dblOpL = va_arg(vlArgs, double);
    double dblOpR = va_arg(vlArgs, double);
    double* pdblRet = va_arg(vlArgs, double*);

    printf("Multiply operation using common calculator.\n");

	*pdblRet = dblOpL * dblOpR;
}

OVERRIDE static void Divide(ParamIn* pParams)
{
    CalculatorExtdCommon* pThis = pParams->pThis;
    va_list vlArgs = pParams->vlArgs;

    double dblOpL = va_arg(vlArgs, double);
    double dblOpR = va_arg(vlArgs, double);
    double* pdblRet = va_arg(vlArgs, double*);

    printf("Divide operation using common calculator.\n");

	*pdblRet = dblOpL / dblOpR;// */0
}

/////////////////////////////////////////////////////////////////////////////
//

static bool __CALL(CalculatorExtdCommon)(CalculatorExtdCommon *pSelf, const char *pMethodName, ...)
{
    DOCALL(pSelf, pMethodName);
}

static void *__EXTEND(CalculatorExtdCommon)(CalculatorExtdCommon *pSelf)
{
    DOEXTEND(pSelf);
}

void __DEL(CalculatorExtdCommon)(CalculatorExtdCommon *pSelf)
{
    DODEL(pSelf, CalculatorBase);
}

CalculatorExtdCommon *__NEW(CalculatorExtdCommon)()
{
    DONEW(pNew, CalculatorExtdCommon, CalculatorBase, NULL,
        METHOD(Add)
        METHOD(Subtract)
        METHOD(Multiply)
        METHOD(Divide));

    return pNew;
}
