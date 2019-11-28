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


#include <stdio.h>
#include "IOperationScore.h"
#include "OperationScoreAdapter.h"

int main(int argc, char **argv)
{
	IOperationScore *pOprtScr = NULL;
	{
        OperationScoreAdapter *pAdapter = __NEW(OperationScoreAdapter);
		pOprtScr = __Cvt(pAdapter, __TYPE(IOperationScore));
	}

	int arr[] = {4, 2, 10, 6, 8};
	size_t szLen = 5;
	int *pArrSorted = NULL;

	//原始数组
	printf("Before sort: ");
	for (size_t i = 0; i < szLen; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");

    pOprtScr->Call(pOprtScr, "DoSort", arr, szLen);
	//排序后
	printf("After sort: ");
	for (size_t i = 0; i < szLen; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");

	int nIndexFind = -1;
    pOprtScr->Call(pOprtScr, "DoSearch", arr, szLen, 6, &nIndexFind);
	printf("Index of 6 is: %d.\n", nIndexFind);

	pOprtScr->Destroy(pOprtScr);

	return 0;
}