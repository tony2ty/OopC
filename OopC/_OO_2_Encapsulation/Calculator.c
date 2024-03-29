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

typedef struct
{
    double dblOperandL;
    double dblOperandR;
    double dblResult;
} Fld;

static void Input(void *_pThis, va_list* pvlArgs)
{
	Calculator *pThis = _pThis;
	Fld* pFld = pThis->Fld;

    double dblOperandL = va_arg(*pvlArgs, double);
    double dblOperandR = va_arg(*pvlArgs, double);

    pFld->dblOperandL = dblOperandL;
    pFld->dblOperandR = dblOperandR;
}

static void Add(void* _pThis, va_list* pvlArgs)
{
    Calculator *pThis = _pThis;
	Fld* pFld = pThis->Fld;

    pFld->dblResult = pFld->dblOperandL + pFld->dblOperandR;
}

static void Output(void* _pThis, va_list* pvlArgs)
{
    Calculator *pThis = _pThis;
	Fld* pFld = pThis->Fld;

    double *pResult = va_arg(*pvlArgs, double *);

    *pResult = pFld->dblResult;
}

__CONSTRUCTOR(Calculator)
{
	return __New(__TYPE(Calculator), sizeof(Fld), NULL, 3, 0,
		   __METHOD(Input),
		   __METHOD(Add),
		   __METHOD(Output));
}
