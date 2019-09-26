
#include "ILoggerFactory.h"

#include <malloc.h>

struct ILoggerFactory
{
	CHAINDEF;
};

////////////////////////////////////////////////////////////////////////
//

////////////////////////////////////////////////////////////////////////
//

void INVOKE(ILoggerFactory)(ILoggerFactory* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(ILoggerFactory)(ILoggerFactory* pInst)
{
    DOEXTEND(pInst);
}

void DELETE(ILoggerFactory)(ILoggerFactory** ppInst)
{
    DODELETE(ppInst, ILoggerFactory, Object);
}

ILoggerFactory* CREATE(ILoggerFactory)()
{
    DOCREATE(pCreate, ILoggerFactory, Object, NULL,
        AMETHOD(CreateLogger));

	return pCreate;
}
