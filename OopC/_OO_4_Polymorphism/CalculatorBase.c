
#include "CalculatorBase.h"

#include <malloc.h>

struct CalculatorBase
{
	CHAINDEF;
};

//////////////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////////////
//

void INVOKE(CalculatorBase)(CalculatorBase* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(CalculatorBase)(CalculatorBase* pInst)
{
    DOEXTEND(pInst);
}

void DELETE(CalculatorBase)(CalculatorBase** ppInst)
{
    DODELETE(ppInst, CalculatorBase, Object);
}

CalculatorBase* CREATE(CalculatorBase)()
{
    DOCREATE(pCreate, CalculatorBase, Object, NULL,
        AMETHOD(Add)
        AMETHOD(Subtract)
        AMETHOD(Multiply)
        AMETHOD(Divide));

	return pCreate;
}
