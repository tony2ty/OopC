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

struct ImageGif
{
	CHAINDEF;

};

/////////////////////////////////////////////////////////////////////////
//

static void ParseFile(void *pParams)
{
	ImageGif *pThis = ((ParamIn *)pParams)->pInst;
	ImageGif_ParseFile *pIn = ((ParamIn *)pParams)->pIn;

    RLSLOCALMEMBRA();

	//Todo: 
    printf("½âÎöGif¸ñÊ½Í¼Æ¬ %s\n", pIn->pFileName);
    Matrix *pMat = CREATE(Matrix)(); TORLS(DELETE(Matrix), pMat);
    DOINVOKESUPER(pThis, "DoPaint", &(IImage_DoPaint){pMat});

    RLSLOCALMEMKET();
}

/////////////////////////////////////////////////////////////////////////
//

bool INVOKE(ImageGif)(ImageGif *pInst, char *pFuncName, void *pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(ImageGif)(ImageGif *pInst)
{
	DOEXTEND(pInst);
}

void DELETE(ImageGif)(ImageGif *pInst)
{
	DODELETE(pInst, ImageGif, IImage);
}

ImageGif *CREATE(ImageGif)()
{
	DOCREATE(pCreate, ImageGif, IImage, NULL,
		METHOD(ParseFile));

	return pCreate;
}
