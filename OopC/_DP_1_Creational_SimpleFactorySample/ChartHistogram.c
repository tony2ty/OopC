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


#include "ChartHistogram.h"

#include <stdio.h>

struct ChartHistogram
{
    CHAINDEF;
};

////////////////////////////////////////////////////////////////////////
//

static void Display(void *pParams)
{
    ChartHistogram *pThis = ((ParamIn *)pParams)->pInst;
    ChartHistogram_Display *pIn = ((ParamIn *)pParams)->pIn;

    printf("ÏÔÊ¾Öù×´Í¼.\n");
}

////////////////////////////////////////////////////////////////////////
//

bool INVOKE(ChartHistogram)(ChartHistogram *pInst, char *pFuncName, void *pParams)
{
    DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(ChartHistogram)(ChartHistogram *pInst)
{
    DOEXTEND(pInst);
}

void DELETE(ChartHistogram)(ChartHistogram **ppInst)
{
    DODELETE(ppInst, ChartHistogram, IChart);
}

ChartHistogram *CREATE(ChartHistogram)()
{
    DOCREATE(pCreate, ChartHistogram, IChart, NULL,
        METHOD(Display));

    printf("´´½¨Öù×´Í¼.\n");

    return pCreate;
}
