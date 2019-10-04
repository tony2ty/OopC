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


#include "Calculator.h"

#include <malloc.h>
#include <stddef.h>

struct Calculator
{
    CHAINDEF;

    double dblOperandL;
    double dblOperandR;
    double dblResult;
};

///////////////////////////////////////////////////////////////////////////////
//

static void Input(void *pParams)
{
    Calculator *pThis = ((ParamIn *)pParams)->pInst;
    Calculator_Input *pIn = ((ParamIn *)pParams)->pIn;

    pThis->dblOperandL = pIn->dblOperandL;
    pThis->dblOperandR = pIn->dblOperandR;
}

static void Add(void *pParams)
{
    Calculator *pThis = ((ParamIn *)pParams)->pInst;
    Calculator_Add *pIn = ((ParamIn *)pParams)->pIn;

    pThis->dblResult = pThis->dblOperandL + pThis->dblOperandR;
}

static void Output(void *pParams)
{
    Calculator *pThis = ((ParamIn *)pParams)->pInst;
    Calculator_Output *pIn = ((ParamIn *)pParams)->pIn;

    *pIn->pResult = pThis->dblResult;
}

///////////////////////////////////////////////////////////////////////////////
//

void INVOKE(Calculator)(Calculator *pInst, char *pFuncName, void *pParams)
{
    DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(Calculator)(Calculator *pInst)
{
    DOEXTEND(pInst);
}

void DELETE(Calculator)(Calculator **ppInst)
{
    DODELETE(ppInst, Calculator, Object);
}

Calculator *CREATE(Calculator)()
{
    DOCREATE(pCreate, Calculator, Object, NULL,
        METHOD(Input)
        METHOD(Add)
        METHOD(Output));

    return pCreate;
}