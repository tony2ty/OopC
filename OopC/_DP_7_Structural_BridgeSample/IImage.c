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


typedef struct
{
	IOprtSys * pOS;
} Fld;

/////////////////////////////////////////////////////////////////////////
//

static void DoPaint(void *_pThis, va_list* pvlArgs)
{
    IImage *pThis = _pThis;
	Fld* pFld = pThis->Fld;

    Matrix * pMat = va_arg(*pvlArgs, Matrix *);

	//Todo: 
    pFld->pOS->Call(pFld->pOS, "DoPaint", pMat);
}

static void SetOprtSys(void *_pThis, va_list* pvlArgs)
{
	IImage *pThis = _pThis;
	Fld* pFld = pThis->Fld;

    IOprtSys *pOS = va_arg(*pvlArgs, IOprtSys *);

	//Todo: 
    pFld->pOS = pOS;
}

//////////////////////////////////////////////////////////////////////////
//

static void Clear(void *pParams)
{
    IImage *pSelf = pParams;
	Fld* pFld = pSelf->Fld;

    if (pFld->pOS)
    {
		pFld->pOS->Destroy(pFld->pOS);
    }
    pFld->pOS = NULL;
}

__CONSTRUCTOR(IImage)
{
	return __New(__TYPE(IImage), sizeof(Fld), Clear, 3, 0,
		__METHOD(DoPaint),
		__METHOD(SetOprtSys),
		__METHODA(ParseFile));
}