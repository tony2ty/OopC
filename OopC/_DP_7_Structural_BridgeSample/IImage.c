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


#include "IImage.h"


struct IImage
{
	CHAINDEF;

	IOprtSys * pOS;
};

/////////////////////////////////////////////////////////////////////////
//

static void DoPaint(void *pParams)
{
	IImage *pThis = ((ParamIn *)pParams)->pInst;
	IImage_DoPaint *pIn = ((ParamIn *)pParams)->pIn;

	//Todo: 
    INVOKE(IOprtSys)(pThis->pOS, "DoPaint", &(IOprtSys_DoPaint){pIn->pMat});
}
static void SetOprtSys(void *pParams)
{
	IImage *pThis = ((ParamIn *)pParams)->pInst;
	IImage_SetOprtSys *pIn = ((ParamIn *)pParams)->pIn;

	//Todo: 
    pThis->pOS = pIn->pOS;
}

//////////////////////////////////////////////////////////////////////////
//

static void ClearExtraMem(void *pToClear)
{
    IImage *pInst = pToClear;
    if (pInst->pOS)
    {
        DELETE(IOprtSys)(&pInst->pOS);
    }
}

/////////////////////////////////////////////////////////////////////////
//

bool INVOKE(IImage)(IImage *pInst, char *pFuncName, void *pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(IImage)(IImage *pInst)
{
	DOEXTEND(pInst);
}

void DELETE(IImage)(IImage **ppInst)
{
	DODELETE(ppInst, IImage, Object);
}

IImage *CREATE(IImage)()
{
	DOCREATE(pCreate, IImage, Object, GenerateExtraMemRef(ClearExtraMem, pCreate),
		METHOD(DoPaint)
		METHOD(SetOprtSys)
		AMETHOD(ParseFile));

    pCreate->pOS = NULL;

	return pCreate;
}
