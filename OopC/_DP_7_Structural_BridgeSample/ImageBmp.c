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


#include "ImageBmp.h"

#include <stdio.h>

struct ImageBmp
{
	CHAINDEF;

};

/////////////////////////////////////////////////////////////////////////
//

static void ParseFile(void *pParams)
{
	ImageBmp *pThis = ((ParamIn *)pParams)->pInst;
	ImageBmp_ParseFile *pIn = ((ParamIn *)pParams)->pIn;

	//Todo: 
    printf("½âÎöBmp¸ñÊ½Í¼Æ¬ %s\n", pIn->pFileName);
    Matrix *pMat = CREATE(Matrix)();
    DOINVOKESUPER(pThis, "DoPaint", &(IImage_DoPaint){pMat});
    DELETE(Matrix)(&pMat);
}

/////////////////////////////////////////////////////////////////////////
//

bool INVOKE(ImageBmp)(ImageBmp *pInst, char *pFuncName, void *pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(ImageBmp)(ImageBmp *pInst)
{
	DOEXTEND(pInst);
}

void DELETE(ImageBmp)(ImageBmp **ppInst)
{
	DODELETE(ppInst, ImageBmp, IImage);
}

ImageBmp *CREATE(ImageBmp)()
{
	DOCREATE(pCreate, ImageBmp, IImage, NULL,
		METHOD(ParseFile));

	return pCreate;
}
