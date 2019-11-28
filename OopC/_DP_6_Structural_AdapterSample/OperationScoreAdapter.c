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


#include "OperationScoreAdapter.h"

#include "QuickSorter.h"
#include "BinarySearcher.h"

typedef struct
{
	QuickSorter * pSorter;
	BinarySearcher * pSearcher;
} Fld;

/////////////////////////////////////////////////////////////////////////
//

__OVERRIDE static void DoSort(void *_pThis, va_list* pvlArgs)
{
    OperationScoreAdapter *pThis = _pThis;
	Fld* pFld = pThis->Fld;

    int *pArr = va_arg(*pvlArgs, int *);
    size_t szLen = va_arg(*pvlArgs, size_t);

	//Todo: 
    pFld->pSorter->Call(pFld->pSorter, "DoSort", pArr, szLen);
}
__OVERRIDE static void DoSearch(void *_pThis, va_list* pvlArgs)
{
    OperationScoreAdapter *pThis = _pThis;
	Fld* pFld = pThis->Fld;

    int *pArrToSearch = va_arg(*pvlArgs, int *);
    size_t szLen = va_arg(*pvlArgs, size_t);
    int nKey = va_arg(*pvlArgs, int);
    int *pRetIndexFind = va_arg(*pvlArgs, int *);

	//Todo: 
    pFld->pSearcher->Call(pFld->pSearcher, "DoSearch", pArrToSearch, szLen, nKey, pRetIndexFind);
}

/////////////////////////////////////////////////////////////////////////
//

static void Clear(void *pParams)
{
    OperationScoreAdapter *pSelf = pParams;
	Fld* pFld = pSelf->Fld;

	pFld->pSearcher->Destroy(pFld->pSearcher);
	pFld->pSorter->Destroy(pFld->pSorter);
}

__CONSTRUCTOR(OperationScoreAdapter)
{
	OperationScoreAdapter* pNew = __New(__TYPE(OperationScoreAdapter), sizeof(Fld), Clear, 2, 1,
		__METHOD(DoSort),
		__METHOD(DoSearch),
		__INHERIT(IOperationScore));

	Fld* pFld = pNew->Fld;
	pFld->pSearcher = __NEW(BinarySearcher);
	pFld->pSorter = __NEW(QuickSorter);

	return pNew;
}
