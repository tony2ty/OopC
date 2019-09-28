
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
		INVOKE(Calculator)(pCalc, "Input", &(Calculator_Input){11, 13});
		INVOKE(Calculator)(pCalc, "Add", NULL);
		INVOKE(Calculator)(pCalc, "Output", &(Calculator_Output){&dblRet});
		printf("11 + 13 = ? %f.\n", dblRet);
		INVOKE(Calculator)(pCalc, "Subtract", &(Calculator_Subtract){10, 12, & dblRet});
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
		//INVOKE(Calculator)(pBase, "Add", NULL);
		//printf("11 + 21 = ? %f.\n", dblRet);
		INVOKE(Calculator)(pBase, "Subtract", &(Calculator_Subtract){11, 5, & dblRet});
		printf("11 - 5  = ? %f.\n", dblRet);
		INVOKE(Calculator)(pBase, "Multiply", &(Calculator_Multiply){11, 7, & dblRet});
		printf("11 * 7  = ? %f.\n", dblRet);

		DELETE(Calculator)(&pBase);
	}

	system("pause");

	return 0;
}