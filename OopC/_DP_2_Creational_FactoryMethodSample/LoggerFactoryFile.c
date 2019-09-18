
#include "LoggerFactoryFile.h"

#include <malloc.h>

struct LoggerFactoryFile
{
	CHAINDEF;

	ILogger* pLogger;
};

/////////////////////////////////////////////////////////////////////////
//

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
	//
	//DELETE()

	ILoggerFactory* pSuper = SWITCH((*ppInst), LoggerFactoryFile, ILoggerFactory);
	DELETE(ILoggerFactory)(&pSuper);
	(*ppInst) = NULL;
}
