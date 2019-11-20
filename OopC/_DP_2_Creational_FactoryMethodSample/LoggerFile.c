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


#include "LoggerFile.h"

#include <stdio.h>

struct LoggerFile_Fld
{
	CHAINDECLARE;
};

//////////////////////////////////////////////////////////////////////////
//

OVERRIDE static void WriteLog(ParamIn* pParams)
{
	LoggerFile* pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	printf("文件日志记录.\n");
}

//////////////////////////////////////////////////////////////////////////
//

static bool __CALL(LoggerFile)(LoggerFile* pSelf, const char* pMethodName, ...)
{
	DOCALL(pSelf, pMethodName);
}

static void* __EXTEND(LoggerFile)(LoggerFile* pSelf, const char* pMethodName, ...)
{
	DOEXTEND(pSelf);
}

void __DEL(LoggerFile)(LoggerFile* pSelf)
{
	DODEL(pSelf, Object);
}

LoggerFile* __NEW(LoggerFile)()
{
	DONEW(pNew, LoggerFile, Object, NULL,
		AMETHOD(WriteLog));

	return pNew;
}