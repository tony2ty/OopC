
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

    printf("��ʾ����ͼ��\n");
}

///////////////////////////////////////////////////////////////////////
//

void INVOKE(ChartLine)(ChartLine *pInst, char *pFuncName, void *pParams)
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

    printf("��������ͼ.\n");

    return pCreate;
}
