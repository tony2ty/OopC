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

struct BinarySearcher
{
	CHAINDEF;

};

/////////////////////////////////////////////////////////////////////////
//

static int Comparer(const void *pL, const void *pR)
{
	return *(int *)pL - *(int *)pR;
}

static void DoSearch(void *pParams)
{
	BinarySearcher *pThis = ((ParamIn *)pParams)->pInst;
	BinarySearcher_DoSearch *pIn = ((ParamIn *)pParams)->pIn;

	//Todo: 
	int *pFind = bsearch(&pIn->nKey, pIn->pArrToSearch, pIn->szLen, sizeof(int), Comparer);
	for (size_t i = 0; i < pIn->szLen; i++)
	{
		if (&pIn->pArrToSearch[i] == pFind)
		{
			*pIn->pRetIndexFind = i;
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////
//

bool INVOKE(BinarySearcher)(BinarySearcher *pInst, char *pFuncName, void *pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(BinarySearcher)(BinarySearcher *pInst)
{
	DOEXTEND(pInst);
}

void DELETE(BinarySearcher)(BinarySearcher *pInst)
{
	DODELETE(pInst, BinarySearcher, Object);
}

BinarySearcher *CREATE(BinarySearcher)()
{
	DOCREATE(pCreate, BinarySearcher, Object, NULL,
		METHOD(pCreate, DoSearch));

	return pCreate;
}
