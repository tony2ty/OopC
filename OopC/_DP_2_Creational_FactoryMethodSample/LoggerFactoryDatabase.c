
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
	return pInst->pChain;
}

void DELETE(LoggerFactoryDatabase)(LoggerFactoryDatabase** ppInst)
{
	ILoggerFactory* pSuper = SWITCH((*ppInst), LoggerFactoryDatabase, ILoggerFactory);
	DELETE(ILoggerFactory)(&pSuper);
	*ppInst = NULL;
}

LoggerFactoryDatabase* CREATE(LoggerFactoryDatabase)()
{
	LoggerFactoryDatabase* pCreate = malloc(sizeof(LoggerFactoryDatabase));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

	pMethods = InsertMethod(pMethods, 1,
		GenerateMethod(CreateLogger, "CreateLogger"));
	pCreate->pChain = InsertInstance(EXTEND(ILoggerFactory)(CREATE(ILoggerFactory)()), GenerateInstance(pCreate, "LoggerFactoryDatabase", NULL, pMethods));

	return pCreate;
}
