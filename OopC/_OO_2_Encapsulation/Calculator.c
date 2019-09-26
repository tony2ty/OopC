
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
    DOEXTEND(pInst);
}

void DELETE(Calculator)(Calculator **ppInst)
{
    DODELETE(ppInst, Calculator, Object);
}

Calculator *CREATE(Calculator)()
{
    DOCREATE(pCreate, Calculator, Object, NULL,
        METHOD(Input)
        METHOD(Add)
        METHOD(Output));

    return pCreate;
}