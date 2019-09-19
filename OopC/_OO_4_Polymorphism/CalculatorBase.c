
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
	return pInst->pChain;
}

void DELETE(CalculatorBase)(CalculatorBase** ppInst)
{
	//

	Object* pSuper = SWITCH((*ppInst), CalculatorBase, Object);
	DELETE(Object)(&pSuper);
    (*ppInst) = NULL;
}

CalculatorBase* CREATE(CalculatorBase)()
{
	CalculatorBase* pCreate = malloc(sizeof(CalculatorBase));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

    pMethods = InsertMethod(pMethods, 4,
        GenerateMethod(NULL, "Add"),
        GenerateMethod(NULL, "Subtract"),
        GenerateMethod(NULL, "Multiply"),
        GenerateMethod(NULL, "Divide"));
	pCreate->pChain = InsertInstance(EXTEND(Object)(CREATE(Object)()), GenerateInstance(pCreate, "CalculatorBase", NULL, pMethods));

	return pCreate;
}
