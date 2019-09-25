
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
    return pInst->pChain;
}

void DELETE(ChartLine)(ChartLine **ppInst)
{
    IChart *pSuper = SWITCH((*ppInst), ChartLine, IChart);
    DELETE(IChart)(&pSuper);
	*ppInst = NULL;
}

ChartLine *CREATE(ChartLine)()
{
    ChartLine *pCreate = malloc(sizeof(ChartLine));
    if (!pCreate) { return NULL; }

    MethodRing *pMethods = GenerateMethodRing();
    if (!pMethods) { return NULL; }

    pMethods = InsertMethod(pMethods, 1,
        GenerateMethod(Display, "Display"));
    pCreate->pChain = InsertInstance(EXTEND(IChart)(CREATE(IChart)()), GenerateInstance(pCreate, "ChartLine", NULL, pMethods));

    printf("��������ͼ.\n");

    return pCreate;
}
