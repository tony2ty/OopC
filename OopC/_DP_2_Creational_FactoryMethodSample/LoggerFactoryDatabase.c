
#include "LoggerFactoryDatabase.h"

#include <malloc.h>
#include "LoggerDatabase.h"

struct LoggerFactoryDatabase
{
	CHAINDEF;
};

/////////////////////////////////////////////////////////////////////
//

static void CreateLogger(void* pParams)
{
	LoggerFactoryDatabase* pThis = ((ParamIn*)pParams)->pInst;
	LoggerFactoryDatabase_CreateLogger* pIn = ((ParamIn*)pParams)->pIn;

	LoggerDatabase* pLoggerDatabase = CREATE(LoggerDatabase)();
	*pIn->ppRet = SWITCH(pLoggerDatabase, LoggerDatabase, ILogger);
}

///////////////////////////////////////////////////////////////////////
//

void INVOKE(LoggerFactoryDatabase)(LoggerFactoryDatabase* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(LoggerFactoryDatabase)(LoggerFactoryDatabase* pInst)
{
    DOEXTEND(pInst);
}

void DELETE(LoggerFactoryDatabase)(LoggerFactoryDatabase** ppInst)
{
    DODELETE(ppInst, LoggerFactoryDatabase, ILoggerFactory);
}

LoggerFactoryDatabase* CREATE(LoggerFactoryDatabase)()
{
    DOCREATE(pCreate, LoggerFactoryDatabase, ILoggerFactory, NULL,
        METHOD(CreateLogger));

	return pCreate;
}
