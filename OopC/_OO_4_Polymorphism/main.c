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
#include "CalculatorExtdCommon.h"
#include "CalculatorExtdEnhanced.h"

int main(int argc, char** argv)
{
    RLSLOCALMEMBRA();

	CalculatorBase* pBase = NULL;
	{
        CalculatorExtdCommon* pCommon = CREATE(CalculatorExtdCommon)(); TORLS(DELETE(CalculatorExtdCommon), pCommon);
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

    printf("-----------------------------------------------------------\n");

	{
		CalculatorExtdEnhanced* pEnhanced = CREATE(CalculatorExtdEnhanced)(); TORLS(DELETE(CalculatorExtdEnhanced), pEnhanced);
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

    RLSLOCALMEMKET();
	return 0;
}