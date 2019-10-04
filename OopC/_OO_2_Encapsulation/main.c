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