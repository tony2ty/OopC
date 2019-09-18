
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

    printf("��ʾ��״ͼ.\n");
}

////////////////////////////////////////////////////////////////////////////////
//

void INVOKE(ChartPie)(ChartPie *pInst, char *pFuncName, void *pParams)
{
    DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(ChartPie)(ChartPie *pInst)
{
    return pInst->pChain;
}

void DELETE(ChartPie)(ChartPie **ppInst)
{
    //

    IChart *pSuper = SWITCH((*ppInst), ChartPie, IChart);
    DELETE(ChartPie)(&pSuper);
    (*ppInst) = NULL;
}

ChartPie *CREATE(ChartPie)()
{
    ChartPie *pCreate = malloc(sizeof(ChartPie));
    if (!pCreate) { return NULL; }

    MethodRing *pMethods = GenerateMethodRing();
    if (!pMethods) { return NULL; }

    pMethods =
          InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Display, "Display"))
        ->pRing;
    pCreate->pChain = InsertInstance(EXTEND(IChart)(CREATE(IChart)()), GenerateInstance(pCreate, "ChartPie", pMethods));

    printf("������״ͼ.\n");

    return pCreate;
}