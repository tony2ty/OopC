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


#include <stdlib.h>
#include <stdio.h>

#include "Calculator.h"
#include "CalculatorExt.h"

int main(int argc, char** argv)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//

	{
		Calculator* pCalc = CREATE(Calculator)();

		double dblRet = 0;
		INVOKE(Calculator)(pCalc, "Subtract", &(Calculator_Subtract){10, 12, &dblRet});
		printf("10 - 12 = ? %f.\n", dblRet);

		DELETE(Calculator)(&pCalc);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//

	{
		CalculatorExt* pCalcExt = CREATE(CalculatorExt)();

		double dblRet = 0;
		INVOKE(CalculatorExt)(pCalcExt, "Add", &(CalculatorExt_Add){11, 21, & dblRet});
		printf("11 + 21 = ? %f.\n", dblRet);
		INVOKE(CalculatorExt)(pCalcExt, "Subtract", &(CalculatorExt_Subtract){11, 5, & dblRet});
		printf("11 - 5  = ? %f.\n", dblRet);
		INVOKE(CalculatorExt)(pCalcExt, "Multiply", &(CalculatorExt_Multiply){11, 7, & dblRet});
		printf("11 * 7  = ? %f.\n", dblRet);
		INVOKE(CalculatorExt)(pCalcExt, "Divide", &(CalculatorExt_Divide){11, 1, & dblRet});
		printf("11 / 1  = ? %f.\n", dblRet);

		DELETE(CalculatorExt)(&pCalcExt);
	}

	{
		Calculator* pBase = NULL;
		{
			CalculatorExt* pExact = CREATE(CalculatorExt)();
			pBase = SWITCH(pExact, CalculatorExt, Calculator);
		}

		double dblRet = 0;
		INVOKE(Calculator)(pBase, "Subtract", &(Calculator_Subtract){11, 5, & dblRet});
		printf("11 - 5  = ? %f.\n", dblRet);
		INVOKE(Calculator)(pBase, "Multiply", &(Calculator_Multiply){11, 7, & dblRet});
		printf("11 * 7  = ? %f.\n", dblRet);

		DELETE(Calculator)(&pBase);
	}

	system("pause");

	return 0;
}