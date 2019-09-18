
#ifndef ILOGGERFACTORY_H__
#define ILOGGERFACTORY_H__

#include <OopBase.h>
#include "ILogger.h"

CLASSDEF(ILoggerFactory)

typedef struct { ILogger** ppRet; } ILoggerFactory_CreateLogger;

#endif // !ILOGGERFACTORY_H__
