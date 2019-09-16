
#include "Calculator.h"

#include <malloc.h>
#include <stddef.h>

struct Calculator
{
    CHAINDEF;

    double dblOperandL;
    double dblOperandR;
    double dblResult;
};

///////////////////////////////////////////////////////////////////////////////
//

static void Input(void *pParams)
{
    Calculator *pThis = ((ParamIn *)pParams)->pInst;
    Calculator_Input *pIn = ((ParamIn *)pParams)->pIn;

    pThis->dblOperandL = pIn->dblOperandL;
    pThis->dblOperandR = pIn->dblOperandR;
}

static void Add(void *pParams)
{
    Calculator *pThis = ((ParamIn *)pParams)->pInst;
    Calculator_Add *pIn = ((ParamIn *)pParams)->pIn;

    pThis->dblResult = pThis->dblOperandL + pThis->dblOperandR;
}

static void Output(void *pParams)
{
    Calculator *pThis = ((ParamIn *)pParams)->pInst;
    Calculator_Output *pIn = ((ParamIn *)pParams)->pIn;

    *pIn->pResult = pThis->dblResult;
}

///////////////////////////////////////////////////////////////////////////////
//

void INVOKE(Calculator)(Calculator *pInst, char *pFuncName, void *pParams)
{
    DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(Calculator)(Calculator *pInst)
{
    return pInst->pChain;
}

void DELETE(Calculator)(Calculator **ppInst)
{
    Object *pSuper = AsBaseByType((*ppInst)->pChain, (*ppInst), TYPE(Object));
    DELETE(Object)(&pSuper);
    *ppInst = NULL;
}

Calculator *CREATE(Calculator)()
{
    Calculator *pCreate = malloc(sizeof(Calculator));
    if (!pCreate) { return NULL; }

    MethodRing *pMethods = GenerateMethodRing();
    if (!pMethods) { return NULL; };

    pMethods = 
        InsertMethod(&(MethodUtil){ pMethods, InsertMethod }, GenerateMethod(Input, "Input"))
      ->InsertMethod(&(MethodUtil){ pMethods, InsertMethod }, GenerateMethod(Add, "Add"))
      ->InsertMethod(&(MethodUtil){ pMethods, InsertMethod }, GenerateMethod(Output, "Output"))
      ->pRing;
    pCreate->pChain = InsertInstance(EXTEND(Object)(CREATE(Object)()), GenerateInstance(pCreate, TYPE(Calculator), pMethods));

    return pCreate;
}