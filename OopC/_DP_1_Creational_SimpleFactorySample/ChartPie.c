
#include "ChartPie.h"

#include <malloc.h>
#include <stdio.h>

struct ChartPie
{
    CHAINDEF;
};

////////////////////////////////////////////////////////////////////////////////
//

static void Display(void *pParams)
{
    ChartPie *pThis = ((ParamIn *)pParams)->pInst;
    ChartPie_Display *pIn = ((ParamIn *)pParams)->pIn;

    printf("ÏÔÊ¾±ý×´Í¼.\n");
}

////////////////////////////////////////////////////////////////////////////////
//

void INVOKE(ChartPie)(ChartPie *pInst, char *pFuncName, void *pParams)
{
    DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(ChartPie)(ChartPie *pInst)
{
    DOEXTEND(pInst);
}

void DELETE(ChartPie)(ChartPie **ppInst)
{
    DODELETE(ppInst, ChartPie, IChart);
}

ChartPie *CREATE(ChartPie)()
{
    DOCREATE(pCreate, ChartPie, IChart, NULL,
        METHOD(Display));

    printf("´´½¨±ý×´Í¼.\n");

    return pCreate;
}
