
#include "LoggerFile.h"

#include <malloc.h>
#include <stdio.h>

struct LoggerFile
{
	CHAINDEF;
};

//////////////////////////////////////////////////////////////////////////
//

static void WriteLog(void* pParams)
{
	LoggerFile* pThis = ((ParamIn*)pParams)->pInst;
	LoggerFile_WriteLog* pIn = ((ParamIn*)pParams)->pIn;

	printf("文件日志记录.\n");
}

//////////////////////////////////////////////////////////////////////////
//

void INVOKE(LoggerFile)(LoggerFile* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(LoggerFile)(LoggerFile* pInst)
{
	return pInst->pChain;
}

void DELETE(LoggerFile)(LoggerFile** ppInst)
{
	//

	ILogger* pSuper = SWITCH((*ppInst), LoggerFile, ILogger);
	DELETE(ILogger)(&pSuper);
	(*ppInst) = NULL;
}

LoggerFile* CREATE(LoggerFile)()
{
	LoggerFile* pCreate = malloc(sizeof(LoggerFile));
	if (!pCreate) { return NULL; }

	MethodRing* pMethods = GenerateMethodRing();
	if (!pMethods) { return NULL; }

	pMethods =
		  InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(WriteLog, "WriteLog"))
		->pRing;
	pCreate->pChain = InsertInstance(EXTEND(ILogger)(CREATE(ILogger)()), GenerateInstance(pCreate, "LoggerFile", NULL, pMethods));

	return pCreate;
}