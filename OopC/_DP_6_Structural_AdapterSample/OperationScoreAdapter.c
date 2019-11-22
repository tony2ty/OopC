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

struct OperationScoreAdapter_Fld
{
    CHAINDECLARE;

	QuickSorter * pSorter;
	BinarySearcher * pSearcher;
};

/////////////////////////////////////////////////////////////////////////
//

OVERRIDE static void DoSort(void *_pThis, va_list vlArgs)
{
    OperationScoreAdapter *pThis = _pThis;

    int *pArr = va_arg(vlArgs, int *);
    size_t szLen = va_arg(vlArgs, size_t);

	//Todo: 
    pThis->pFld->pSorter->Call(pThis->pFld->pSorter, "DoSort", pArr, szLen);
}
OVERRIDE static void DoSearch(void *_pThis, va_list vlArgs)
{
    OperationScoreAdapter *pThis = _pThis;

    int *pArrToSearch = va_arg(vlArgs, int *);
    size_t szLen = va_arg(vlArgs, size_t);
    int nKey = va_arg(vlArgs, int);
    int *pRetIndexFind = va_arg(vlArgs, int *);

	//Todo: 
    pThis->pFld->pSearcher->Call(pThis->pFld->pSearcher, "DoSearch", pArrToSearch, szLen, nKey, pRetIndexFind);
}

/////////////////////////////////////////////////////////////////////////
//

static void __CLEAR(OperationScoreAdapter)(void *pParams)
{
    OperationScoreAdapter *pSelf = pParams;

    DEL(QuickSorter)(pSelf->pFld->pSorter);
    DEL(BinarySearcher)(pSelf->pFld->pSearcher);
}

static bool __CALL(OperationScoreAdapter)(OperationScoreAdapter *pSelf, const char *pMethodName, ...)
{
    DOCALL(pSelf, pMethodName);
}

static void *__EXTEND(OperationScoreAdapter)(OperationScoreAdapter *pSelf)
{
    DOEXTEND(pSelf);
}

void __DEL(OperationScoreAdapter)(OperationScoreAdapter *pSelf)
{
    DODEL(pSelf, Object);
}

OperationScoreAdapter *__NEW(OperationScoreAdapter)()
{
    DONEW(pNew, OperationScoreAdapter, IOperationScore, __CLEAR(OperationScoreAdapter),
        METHOD(DoSort)
        METHOD(DoSearch));

    pNew->pFld->pSearcher = NEW(BinarySearcher);
    pNew->pFld->pSorter = NEW(QuickSorter);

    return pNew;
}
