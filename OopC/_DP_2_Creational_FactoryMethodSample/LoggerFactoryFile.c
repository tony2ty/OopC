
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
	return pInst->pChain;
}

void DELETE(LoggerFactoryFile)(LoggerFactoryFile** ppInst)
{
	ILoggerFactory* pSuper = SWITCH((*ppInst), LoggerFactoryFile, ILoggerFactory);
	DELETE(ILoggerFactory)(&pSuper);
	*ppInst = NULL;
}

LoggerFactoryFile* CREATE(LoggerFactoryFile)()
{
	LoggerFactoryFile* pCreate = malloc(sizeof(LoggerFactoryFile));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

	pMethods = InsertMethod(pMethods, 1,
		GenerateMethod(CreateLogger, "CreateLogger"));
	pCreate->pChain = InsertInstance(EXTEND(ILoggerFactory)(CREATE(ILoggerFactory)()), GenerateInstance(pCreate, "LoggerFactoryFile", NULL, pMethods));

	return pCreate;
}
