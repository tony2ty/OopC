
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
    DOEXTEND(pInst);
}

void DELETE(LoggerDatabase)(LoggerDatabase** ppInst)
{
    DODELETE(ppInst, LoggerDatabase, ILogger);
}

LoggerDatabase* CREATE(LoggerDatabase)()
{
    DOCREATE(pCreate, LoggerDatabase, ILogger, NULL,
        METHOD(WriteLog));

	return pCreate;
}
