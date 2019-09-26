
#include "ILogger.h"

#include <malloc.h>

struct ILogger
{
	CHAINDEF;
};

//////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////
//

void INVOKE(ILogger)(ILogger* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(ILogger)(ILogger* pInst)
{
    DOEXTEND(pInst);
}

void DELETE(ILogger)(ILogger** ppInst)
{
    DODELETE(ppInst, ILogger, Object);
}

ILogger* CREATE(ILogger)()
{
    DOCREATE(pCreate, ILogger, Object, NULL,
        AMETHOD(WriteLog));

	return pCreate;
}
