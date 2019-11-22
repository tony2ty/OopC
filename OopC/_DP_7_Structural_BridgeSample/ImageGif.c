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


#include "ImageGif.h"

#include <stdio.h>

struct ImageGif_Fld
{
    CHAINDECLARE;

};

/////////////////////////////////////////////////////////////////////////
//

OVERRIDE static void ParseFile(void *_pThis, va_list vlArgs)
{
	ImageGif *pThis = _pThis;

    const char *pFileName = va_arg(vlArgs, const char *);

	//Todo: 
    printf("Ω‚ŒˆGif∏Ò ΩÕº∆¨ %s\n", pFileName);
    Matrix *pMat = NEW(Matrix);
    SUPER(pThis, "DoPaint", pMat);
    DEL(Matrix)(pMat);
}

/////////////////////////////////////////////////////////////////////////
//

static bool __CALL(ImageGif)(ImageGif *pSelf, const char *pMethodName, ...)
{
    DOCALL(pSelf, pMethodName);
}

static void *__EXTEND(ImageGif)(ImageGif *pSelf)
{
    DOEXTEND(pSelf);
}

void __DEL(ImageGif)(ImageGif *pSelf)
{
    DODEL(pSelf, IImage);
}

ImageGif *__NEW(ImageGif)()
{
    DONEW(pNew, ImageGif, IImage, NULL,
        METHOD(ParseFile));

    return pNew;
}