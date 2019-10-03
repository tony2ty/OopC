
#include <stdlib.h>
#include <stdio.h>
#include "CalculatorExtdCommon.h"
#include "CalculatorExtdEnhanced.h"

int main(int argc, char** argv)
{
	CalculatorBase* pBase = NULL;
	{
		CalculatorExtdCommon* pCommon = CREATE(CalculatorExtdCommon)();
		pBase = SWITCH(pCommon, CalculatorExtdCommon, CalculatorBase);
	}

	double dblRet = 0;
	INVOKE(CalculatorBase)(pBase, "Add", &(CalculatorBase_Add){ 10, 12, & dblRet });
	printf("10 + 12 = ? %f.\n", dblRet);
	INVOKE(CalculatorBase)(pBase, "Subtract", &(CalculatorBase_Subtract){ 10, 12, & dblRet });
	printf("10 - 12 = ? %f.\n", dblRet);
	INVOKE(CalculatorBase)(pBase, "Multiply", &(CalculatorBase_Multiply){ 10, 12, & dblRet });
	printf("10 * 12 = ? %f.\n", dblRet);
	INVOKE(CalculatorBase)(pBase, "Divide", &(CalculatorBase_Divide){ 12, 10, & dblRet });
	printf("12 / 10 = ? %f.\n", dblRet);

	DELETE(CalculatorBase)(&pBase);

    printf("-----------------------------------------------------------\n");

	{
		CalculatorExtdEnhanced* pEnhanced = CREATE(CalculatorExtdEnhanced)();
		pBase = SWITCH(pEnhanced, CalculatorExtdEnhanced, CalculatorBase);
	}

	INVOKE(CalculatorBase)(pBase, "Add", &(CalculatorBase_Add){ 10, 12, & dblRet });
	printf("10 + 12 = ? %f.\n", dblRet);
	INVOKE(CalculatorBase)(pBase, "Subtract", &(CalculatorBase_Subtract){ 10, 12, & dblRet });
	printf("10 - 12 = ? %f.\n", dblRet);
	INVOKE(CalculatorBase)(pBase, "Multiply", &(CalculatorBase_Multiply){ 10, 12, & dblRet });
	printf("10 * 12 = ? %f.\n", dblRet);
	INVOKE(CalculatorBase)(pBase, "Divide", &(CalculatorBase_Divide){ 12, 10, & dblRet });
	printf("12 / 10 = ? %f.\n", dblRet);

	system("pause");
	return 0;
}