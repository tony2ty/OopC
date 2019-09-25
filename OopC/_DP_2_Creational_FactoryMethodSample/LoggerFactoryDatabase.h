
#ifndef LOGGERFACTORYDATABASE_H__
#define LOGGERFACTORYDATABASE_H__

#include "ILoggerFactory.h"

CLASSDEF(LoggerFactoryDatabase)

typedef struct { ILogger** ppRet; } LoggerFactoryDatabase_CreateLogger;

#endif // !LOGGERFACTORYDATABASE_H__
