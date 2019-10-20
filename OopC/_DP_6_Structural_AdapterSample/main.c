
#include <stdio.h>
#include "IOperationScore.h"
#include "OperationScoreAdapter.h"

int main(int argc, char **argv)
{
	IOperationScore *pOprtScr = NULL;
	{
		OperationScoreAdapter *pAdapter = CREATE(OperationScoreAdapter)();
		pOprtScr = SWITCH(pAdapter, OperationScoreAdapter, IOperationScore);
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

	INVOKE(IOperationScore)(pOprtScr, "DoSort", &(IOperationScore_DoSort){arr, szLen});
	//排序后
	printf("After sort: ");
	for (size_t i = 0; i < szLen; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");

	int nIndexFind = -1;
	INVOKE(IOperationScore)(pOprtScr, "DoSearch", &(IOperationScore_DoSearch){arr, szLen, 6, &nIndexFind});
	printf("Index of 6 is: %d.\n", nIndexFind);

	DELETE(IOperationScore)(&pOprtScr);

	return 0;
}