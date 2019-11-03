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

struct OperationScoreAdapter
{
	CHAINDEF;

	QuickSorter * pSorter;
	BinarySearcher * pSearcher;
};

/////////////////////////////////////////////////////////////////////////
//

static void Clear(void *pToClear)
{
	OperationScoreAdapter *pInst = (OperationScoreAdapter *)pToClear;
	DELETE(QuickSorter)(pInst->pSorter);
	DELETE(BinarySearcher)(pInst->pSearcher);
}

static void DoSort(void *pParams)
{
	OperationScoreAdapter *pThis = ((ParamIn *)pParams)->pInst;
	OperationScoreAdapter_DoSort *pIn = ((ParamIn *)pParams)->pIn;

	//Todo: 
	INVOKE(QuickSorter)(pThis->pSorter, "DoSort", &(QuickSorter_DoSort){pIn->pArr, pIn->szLen});
}
static void DoSearch(void *pParams)
{
	OperationScoreAdapter *pThis = ((ParamIn *)pParams)->pInst;
	OperationScoreAdapter_DoSearch *pIn = ((ParamIn *)pParams)->pIn;

	//Todo: 
	INVOKE(BinarySearcher)(pThis->pSearcher, "DoSearch", &(BinarySearcher_DoSearch){pIn->pArrToSearch, pIn->szLen, pIn->nKey, pIn->pRetIndexFind});
}

/////////////////////////////////////////////////////////////////////////
//

bool INVOKE(OperationScoreAdapter)(OperationScoreAdapter *pInst, char *pFuncName, void *pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(OperationScoreAdapter)(OperationScoreAdapter *pInst)
{
	DOEXTEND(pInst);
}

void DELETE(OperationScoreAdapter)(OperationScoreAdapter *pInst)
{
	DODELETE(pInst, OperationScoreAdapter, IOperationScore);
}

OperationScoreAdapter *CREATE(OperationScoreAdapter)()
{
	DOCREATE(pCreate, OperationScoreAdapter, IOperationScore, GenerateReleaserRef(Clear, pCreate),
		METHOD(DoSort)
		METHOD(DoSearch));

	pCreate->pSorter = CREATE(QuickSorter)();
	pCreate->pSearcher = CREATE(BinarySearcher)();

	return pCreate;
}
