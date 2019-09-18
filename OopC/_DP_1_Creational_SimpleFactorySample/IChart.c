
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
    return pInst->pChain;
}

void DELETE(IChart)(IChart **ppInst)
{
    //

    Object *pSuper = SWITCH((*ppInst), IChart, Object);
    DELETE(Object)(&pSuper);
    (*ppInst) = NULL;
}

IChart *CREATE(IChart)()
{
    IChart *pCreate = malloc(sizeof(IChart));
    if (!pCreate) { return NULL; }

    MethodRing *pMethods = GenerateMethodRing();
    if (!pMethods) { return NULL; }

    pMethods =
          InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(NULL, "Display"))
        ->pRing;
    pCreate->pChain = InsertInstance(EXTEND(Object)(CREATE(Object)()), GenerateInstance(pCreate, "IChart", NULL, pMethods));

    return pCreate;
}
