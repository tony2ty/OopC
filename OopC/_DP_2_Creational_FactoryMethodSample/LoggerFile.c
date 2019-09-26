
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
    DOEXTEND(pInst);
}

void DELETE(LoggerFile)(LoggerFile** ppInst)
{
    DODELETE(ppInst, LoggerFile, ILogger);
}

LoggerFile* CREATE(LoggerFile)()
{
    DOCREATE(pCreate, LoggerFile, ILogger, NULL,
        METHOD(WriteLog));

	return pCreate;
}