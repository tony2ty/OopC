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


struct Calculator_Fld
{
	CHAINDECLARE;

};

////////////////////////////////////////////////////////////////////////////////////
//

static void Subtract(ParamIn* pParams)
{
	Calculator* pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	double dblOpL = va_arg(vlArgs, double);
	double dblOpR = va_arg(vlArgs, double);
	double* pdblRet = va_arg(vlArgs, double*);

	*pdblRet = dblOpL - dblOpR;
}

static void Multiply(ParamIn* pParams)
{
	Calculator* pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	double dblOpL = va_arg(vlArgs, double);
	double dblOpR = va_arg(vlArgs, double);
	double* pdblRet = va_arg(vlArgs, double*);

	*pdblRet = dblOpL * dblOpR;
}

////////////////////////////////////////////////////////////////////////////////////
//

static bool __CALL(Calculator)(Calculator* pSelf, const char* pMethodName, ...)
{
	DOCALL(pSelf, pMethodName);
}

static void* __EXTEND(Calculator)(Calculator* pSelf)
{
	DOEXTEND(pSelf);
}

void __DEL(Calculator)(Calculator* pSelf)
{
	DODEL(pSelf, Object);
}

Calculator* __NEW(Calculator)()
{
	DONEW(pNew, Calculator, Object, NULL,
		METHOD(Subtract)
		METHOD(Multiply));

	return pNew;
}
