
#include "ChartHistogram.h"

#include <malloc.h>
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

void INVOKE(ChartHistogram)(ChartHistogram *pInst, char *pFuncName, void *pParams)
{
    DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(ChartHistogram)(ChartHistogram *pInst)
{
    return pInst->pChain;
}

void DELETE(ChartHistogram)(ChartHistogram **ppInst)
{
    IChart *pSuper = SWITCH((*ppInst), ChartHistogram, IChart);
    DELETE(IChart)(&pSuper);
    (*ppInst) = NULL;
}

ChartHistogram *CREATE(ChartHistogram)()
{
    ChartHistogram *pCreate = malloc(sizeof(ChartHistogram));
    if (!pCreate) { return NULL; }

    MethodRing *pMethods = GenerateMethodRing();
    if (!pMethods) { return NULL; }

    pMethods = InsertMethod(pMethods, 1,
        GenerateMethod(Display, "Display"));
    pCreate->pChain = InsertInstance(EXTEND(IChart)(CREATE(IChart)()), GenerateInstance(pCreate, "ChartHistogram", NULL, pMethods));

    printf("´´½¨Öù×´Í¼.\n");

    return pCreate;
}
