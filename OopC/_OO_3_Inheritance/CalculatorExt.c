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

static void Add(void *_pThis, va_list* pvlArgs)
{
	CalculatorExt* pThis = _pThis;

	double dblOpL = va_arg(*pvlArgs, double);
	double dblOpR = va_arg(*pvlArgs, double);
	double* pdblRet = va_arg(*pvlArgs, double*);

    *pdblRet = dblOpL + dblOpR;
}

//static void Subtract(void* pParams);//直接继承

__OVERRIDE static void Multiply(void *_pThis, va_list* pvlArgs)
{
	CalculatorExt* pThis = _pThis;

	double dblOpL = va_arg(*pvlArgs, double);
	double dblOpR = va_arg(*pvlArgs, double);
	double* pdblRet = va_arg(*pvlArgs, double*);

	//当前方法OVERRIDE父类的方法，
    //通过SUPER调用父类的方法
    __Spr(pThis, "Multiply", dblOpL, dblOpR, pdblRet);
}

static void Divide(void *_pThis, va_list* pvlArgs)
{
	CalculatorExt* pThis = _pThis;

	double dblOpL = va_arg(*pvlArgs, double);
	double dblOpR = va_arg(*pvlArgs, double);
	double* pdblRet = va_arg(*pvlArgs, double*);

	*pdblRet = dblOpL / dblOpR;//除0.。。
}

__CONSTRUCTOR(CalculatorExt)
{
    return __New(__TYPE(CalculatorExt), 0, NULL, 3, 1,
        __METHOD(Add),
        __METHOD(Multiply),
        __METHOD(Divide),
        __INHERIT(Calculator));
}
