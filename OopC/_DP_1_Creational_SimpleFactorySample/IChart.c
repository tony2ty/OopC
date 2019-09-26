
#include "IChart.h"

#include <malloc.h>

struct IChart
{
    CHAINDEF;
};

///////////////////////////////////////////////////////////////////////////
//

///////////////////////////////////////////////////////////////////////////
//

void INVOKE(IChart)(IChart *pInst, char *pFuncName, void *pParams)
{
    DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(IChart)(IChart *pInst)
{
    DOEXTEND(pInst);
}

void DELETE(IChart)(IChart **ppInst)
{
    DODELETE(ppInst, IChart, Object);
}

IChart *CREATE(IChart)()
{
    DOCREATE(pCreate, IChart, Object, NULL,
        AMETHOD(Display));

    return pCreate;
}
