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


#include "ModelGenerator.h"

#include <stdio.h>

//单例模式，标识单例是否生成的变量
static bool bHasBeenGenerated = false;
//单例
static ModelGenerator *pSingleton = NULL;

struct ModelGenerator
{
	CHAINDEF;

};

/////////////////////////////////////////////////////////////////////////
//

static void GetModel(void *pParams)
{
    ModelGenerator *pThis = ((ParamIn *)pParams)->pInst;
    ModelGenerator_GetModel *pIn = ((ParamIn *)pParams)->pIn;

    //Todo: 
    *pIn->pIntRetAsModel = 11;
    printf("Model generated.\n");
}

/////////////////////////////////////////////////////////////////////////
//

bool INVOKE(ModelGenerator)(ModelGenerator *pInst, char *pFuncName, void *pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(ModelGenerator)(ModelGenerator *pInst)
{
	DOEXTEND(pInst);
}

void DELETE(ModelGenerator)(ModelGenerator *pInst)
{
	DODELETE(pInst, ModelGenerator, Object);
}

ModelGenerator *CREATE(ModelGenerator)()
{
    //这里通过变量判断，
    //单例出现并发问题的情况就归结为
    //同时访问一个基本类型变量出现数据竞争。
    if (bHasBeenGenerated)
    {
        return pSingleton;
    }
    bHasBeenGenerated = true;

	DOCREATE(pCreate, ModelGenerator, Object, NULL,
		METHOD(GetModel));

    pSingleton = pCreate;

	return pCreate;
}
