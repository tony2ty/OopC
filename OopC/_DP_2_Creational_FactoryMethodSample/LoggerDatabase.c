
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

	printf("���ݿ���־��¼��\n");
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
	DELETE(LoggerDatabase)(&pSuper);
	(*ppInst) = NULL;
}

LoggerDatabase* CREATE(LoggerDatabase)()
{
	LoggerDatabase* pCreate = malloc(sizeof(LoggerDatabase));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

	pMethods =
		InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(WriteLog, "WriteLog"))
		->pRing;
	pCreate->pChain = InsertInstance(EXTEND(ILogger)(CREATE(ILogger)()), GenerateInstance(pCreate, "LoggerDatabase", pMethods));

	return pCreate;
}