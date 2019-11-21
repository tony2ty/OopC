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


struct IImage_Fld
{
    CHAINDECLARE;

	IOprtSys * pOS;
};

/////////////////////////////////////////////////////////////////////////
//

static void DoPaint(ParamIn *pParams)
{
    IImage *pThis = pParams->pThis;
    va_list vlArgs = pParams->vlArgs;

    Matrix * pMat = va_arg(vlArgs, Matrix *);

	//Todo: 
    pThis->pFld->pOS->Call(pThis->pFld->pOS, "DoPaint", pMat);
}
static void SetOprtSys(ParamIn *pParams)
{
	IImage *pThis = pParams->pThis;
    va_list vlArgs = pParams->vlArgs;

    IOprtSys *pOS = va_arg(vlArgs, IOprtSys *);

	//Todo: 
    pThis->pFld->pOS = pOS;
}

//////////////////////////////////////////////////////////////////////////
//

static void __CLEAR(IImage)(void *pParams)
{
    IImage *pSelf = pParams;

    if (pSelf->pFld->pOS)
    {
        DEL(IOprtSys)(pSelf->pFld->pOS);
    }
    pSelf->pFld->pOS = NULL;
}

static bool __CALL(IImage)(IImage *pSelf, const char *pMethodName, ...)
{
    DOCALL(pSelf, pMethodName);
}

static void *__EXTEND(IImage)(IImage *pSelf)
{
    DOEXTEND(pSelf);
}

void __DEL(IImage)(IImage *pSelf)
{
    DODEL(pSelf, Object);
}

IImage *__NEW(IImage)()
{
	DONEW(pNew, IImage, Object, __CLEAR(IImage),
		METHOD(DoPaint)
		METHOD(SetOprtSys)
		AMETHOD(ParseFile));

    pNew->pFld->pOS = NULL;

	return pNew;
}
