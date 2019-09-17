
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "Calculator.h"

int main(int argc, char** argv)
{
    Calculator *pCalc = CREATE(Calculator)();

    bool bRet = false;
    double dblResult = 0;
    INVOKE(Calculator)(pCalc, "ToString", NULL);
    INVOKE(Calculator)(pCalc, "Equal", &(Object_Equal){ &bRet, pCalc });
    INVOKE(Calculator)(pCalc, "Input", &(Calculator_Input){ 11, 13 });
    INVOKE(Calculator)(pCalc, "Add", NULL);
    INVOKE(Calculator)(pCalc, "Output", &(Calculator_Output){ &dblResult });
    printf("\n11 + 13 = ? %f.\n", dblResult);

    DELETE(Calculator)(&pCalc);

	system("pause");

	return 0;
}