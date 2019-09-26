
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

    printf("��ʾ��״ͼ.\n");
}

////////////////////////////////////////////////////////////////////////
//

void INVOKE(ChartHistogram)(ChartHistogram *pInst, char *pFuncName, void *pParams)
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

    printf("������״ͼ.\n");

    return pCreate;
}
