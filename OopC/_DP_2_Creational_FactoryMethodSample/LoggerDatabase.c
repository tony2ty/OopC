
#include "LoggerDatabase.h"

#include <malloc.h>
#include <stdio.h>

struct LoggerDatabase
{
	CHAINDEF;
};

///////////////////////////////////////////////////////////////////
//

static void WriteLog(void* pParams)
{
	LoggerDatabase* pThis = ((ParamIn*)pParams)->pInst;
	LoggerDatabase_WriteLog* pIn = ((ParamIn*)pParams)->pIn;

	printf("数据库日志记录。\n");
}

///////////////////////////////////////////////////////////////////
//

void INVOKE(LoggerDatabase)(LoggerDatabase* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(LoggerDatabase)(LoggerDatabase* pInst)
{
	return pInst->pChain;
}

void DELETE(LoggerDatabase)(LoggerDatabase** ppInst)
{
	//

	ILogger* pSuper = SWITCH((*ppInst), LoggerDatabase, ILogger);
	DELETE(ILogger)(&pSuper);
	(*ppInst) = NULL;
}

LoggerDatabase* CREATE(LoggerDatabase)()
{
	LoggerDatabase* pCreate = malloc(sizeof(LoggerDatabase));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

    pMethods = InsertMethod(pMethods, 1,
        GenerateMethod(WriteLog, "WriteLog"));
	pCreate->pChain = InsertInstance(EXTEND(ILogger)(CREATE(ILogger)()), GenerateInstance(pCreate, "LoggerDatabase", NULL, pMethods));

	return pCreate;
}
