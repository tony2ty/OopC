
#ifndef LOGGERFACTORYFILE_H__
#define LOGGERFACTORYFILE_H__

#include "ILoggerFactory.h"

CLASSDEF(LoggerFactoryFile)

typedef struct { ILogger** ppRet; } LoggerFactoryFile_CreateLogger;

#endif // !LOGGERFACTORYFILE_H__
