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


#include "BinarySearcher.h"

#include <stdlib.h>

struct BinarySearcher_Fld
{
    CHAINDECLARE;

};

/////////////////////////////////////////////////////////////////////////
//

/*
 * ±È½ÏÆ÷ */
static int Comparer(const void *pL, const void *pR)
{
	return *(int *)pL - *(int *)pR;
}

static void DoSearch(void *_pThis, va_list vlArgs)
{
    BinarySearcher *pThis = _pThis;

    int *pArrToSearch = va_arg(vlArgs, int *);
    size_t szLen = va_arg(vlArgs, size_t);
    int nKey = va_arg(vlArgs, int);
    int *pRetIndexFind = va_arg(vlArgs, int *);

	//Todo: 
	int *pFind = bsearch(&nKey, pArrToSearch, szLen, sizeof(int), Comparer);
	for (size_t i = 0; i < szLen; i++)
	{
		if (&pArrToSearch[i] == pFind)
		{
			*pRetIndexFind = i;
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////
//

static bool __CALL(BinarySearcher)(BinarySearcher *pSelf, const char *pMethodName, ...)
{
    DOCALL(pSelf, pMethodName);
}

static void *__EXTEND(BinarySearcher)(BinarySearcher *pSelf)
{
    DOEXTEND(pSelf);
}

void __DEL(BinarySearcher)(BinarySearcher *pSelf)
{
    DODEL(pSelf, Object);
}

BinarySearcher *__NEW(BinarySearcher)()
{
    DONEW(pNew, BinarySearcher, Object, NULL,
        METHOD(DoSearch));

    return pNew;
}
