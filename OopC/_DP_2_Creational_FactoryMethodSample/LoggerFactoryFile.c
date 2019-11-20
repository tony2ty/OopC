//MIT License
//
//Copyright(c) 2019 Goodman Tao
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.


#include "LoggerFactoryFile.h"

#include "LoggerFile.h"

struct LoggerFactoryFile_Fld
{
	CHAINDECLARE;
};

/////////////////////////////////////////////////////////////////////////
//

OVERRIDE static void CreateLogger(ParamIn* pParams)
{
	LoggerFactoryFile* pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	ILogger** ppRet = va_arg(vlArgs, ILogger * *);

	LoggerFile* pLoggerFile = NEW(LoggerFile);
	*ppRet = SWITCH(pLoggerFile, ILogger);
}

/////////////////////////////////////////////////////////////////////////
//

static bool __CALL(LoggerFactoryFile)(LoggerFactoryFile* pSelf, const char* pMethodName, ...)
{
	DOCALL(pSelf, pMethodName);
}

static void* __EXTEND(LoggerFactoryFile)(LoggerFactoryFile* pSelf)
{
	DOEXTEND(pSelf);
}

void __DEL(LoggerFactoryFile)(LoggerFactoryFile* pSelf)
{
	DODEL(pSelf, ILoggerFactory);
}

LoggerFactoryFile* __NEW(LoggerFactoryFile)()
{
	DONEW(pNew, LoggerFactoryFile, ILoggerFactory, NULL,
		METHOD(CreateLogger));

	return pNew;
}
