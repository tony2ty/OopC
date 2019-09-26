
#include "LoggerFactoryFile.h"

#include <malloc.h>
#include "LoggerFile.h"

struct LoggerFactoryFile
{
	CHAINDEF;

	ILogger* pLogger;
};

/////////////////////////////////////////////////////////////////////////
//

static void CreateLogger(void* pParams)
{
	LoggerFactoryFile* pThis = ((ParamIn*)pParams)->pInst;
	LoggerFactoryFile_CreateLogger* pIn = ((ParamIn*)pParams)->pIn;

	LoggerFile* pLoggerFile = CREATE(LoggerFile)();
	*pIn->ppRet = SWITCH(pLoggerFile, LoggerFile, ILogger);
}

/////////////////////////////////////////////////////////////////////////
//

void INVOKE(LoggerFactoryFile)(LoggerFactoryFile* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(LoggerFactoryFile)(LoggerFactoryFile* pInst)
{
    DOEXTEND(pInst);
}

void DELETE(LoggerFactoryFile)(LoggerFactoryFile** ppInst)
{
    DODELETE(ppInst, LoggerFactoryFile, ILoggerFactory);
}

LoggerFactoryFile* CREATE(LoggerFactoryFile)()
{
    DOCREATE(pCreate, LoggerFactoryFile, ILoggerFactory, NULL,
        METHOD(CreateLogger));

	return pCreate;
}
