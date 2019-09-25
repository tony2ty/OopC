
#include "ILoggerFactory.h"
#include "LoggerFactoryFile.h"
#include "LoggerFactoryDatabase.h"

int main(int argc, char** argv)
{
	ILogger* pLogger = NULL;
	ILoggerFactory* pLoggerFactory = NULL;
	
	{
		LoggerFactoryFile* pLoggerFactoryFile = CREATE(LoggerFactoryFile)();
		pLoggerFactory = SWITCH(pLoggerFactoryFile, LoggerFactoryFile, ILoggerFactory);
	}
	INVOKE(ILoggerFactory)(pLoggerFactory, "CreateLogger", &(ILoggerFactory_CreateLogger){&pLogger});
	DELETE(ILoggerFactory)(&pLoggerFactory);
	INVOKE(ILogger)(pLogger, "WriteLog", NULL);
	DELETE(ILogger)(&pLogger);

	{
		LoggerFactoryDatabase* pLoggerFactoryDatabase = CREATE(LoggerFactoryDatabase)();
		pLoggerFactory = SWITCH(pLoggerFactoryDatabase, LoggerFactoryDatabase, ILoggerFactory);
	}
	INVOKE(ILoggerFactory)(pLoggerFactory, "CreateLogger", &(ILoggerFactory_CreateLogger){&pLogger});
	DELETE(ILoggerFactory)(&pLoggerFactory);
	INVOKE(ILogger)(pLogger, "WriteLog", NULL);
	DELETE(ILogger)(&pLogger);

	return 0;
}