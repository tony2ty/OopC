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


#include "ChartLine.h"

#include <malloc.h>
#include <stdio.h>

struct ChartLine
{
    CHAINDEF;
};

///////////////////////////////////////////////////////////////////////
//

static void Display(void *pParams)
{
    ChartLine *pThis = ((ParamIn *)pParams)->pInst;
    ChartLine_Display *pIn = ((ParamIn *)pParams)->pIn;

    printf("显示折线图。\n");
}

///////////////////////////////////////////////////////////////////////
//

bool INVOKE(ChartLine)(ChartLine *pInst, char *pFuncName, void *pParams)
{
    DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(ChartLine)(ChartLine *pInst)
{
    DOEXTEND(pInst);
}

void DELETE(ChartLine)(ChartLine **ppInst)
{
    DODELETE(ppInst, ChartLine, IChart);
}

ChartLine *CREATE(ChartLine)()
{
    DOCREATE(pCreate, ChartLine, IChart, NULL,
        METHOD(Display));

    printf("创建折线图.\n");

    return pCreate;
}
