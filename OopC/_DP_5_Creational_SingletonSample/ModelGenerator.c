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

static void GetModel(void *_pThis, va_list* pvlArgs)
{
    ModelGenerator *pThis = _pThis;

    int *pIntRetAsModel = va_arg(*pvlArgs, int *);

    //Todo: 
    *pIntRetAsModel = 11;
    printf("Model generated.\n");
}

/////////////////////////////////////////////////////////////////////////
//

static void Clear(void *pParams)
{
    ModelGenerator *pSelf = pParams;

    //对象销毁后，便没有单例了，
    //因此标识变量设为false
    bHasBeenGenerated = false;
    pSingleton = NULL;
}

__CONSTRUCTOR(ModelGenerator)
{
    //这里通过变量判断，
    //单例出现并发问题的情况就归结为
    //同时访问一个基本类型变量出现数据竞争。
    //并发量很大的时候，仍然不推荐这样处理
    if (bHasBeenGenerated)
    {
        return pSingleton;
    }
    bHasBeenGenerated = true;

	pSingleton = __New(__TYPE(ModelGenerator), 0, Clear, 1, 0,
		__METHOD(GetModel));

	return pSingleton;
}
