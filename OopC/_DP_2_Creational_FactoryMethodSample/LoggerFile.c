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

bool INVOKE(LoggerFile)(LoggerFile* pInst, char* pFuncName, void* pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(LoggerFile)(LoggerFile* pInst)
{
    DOEXTEND(pInst);
}

void DELETE(LoggerFile)(LoggerFile* pInst)
{
    DODELETE(pInst, LoggerFile, ILogger);
}

LoggerFile* CREATE(LoggerFile)()
{
    DOCREATE(pCreate, LoggerFile, ILogger, NULL,
        METHOD(WriteLog));

	return pCreate;
}