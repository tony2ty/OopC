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


#include "OprtSysLinux.h"

#include <stdio.h>

struct OprtSysLinux
{
	CHAINDEF;

};

/////////////////////////////////////////////////////////////////////////
//

static void DoPaint(void *pParams)
{
	OprtSysLinux *pThis = ((ParamIn *)pParams)->pInst;
	OprtSysLinux_DoPaint *pIn = ((ParamIn *)pParams)->pIn;

	//Todo: 
    printf("在Linux操作系统中显示图像.\n");
}

/////////////////////////////////////////////////////////////////////////
//

bool INVOKE(OprtSysLinux)(OprtSysLinux *pInst, char *pFuncName, void *pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(OprtSysLinux)(OprtSysLinux *pInst)
{
	DOEXTEND(pInst);
}

void DELETE(OprtSysLinux)(OprtSysLinux **ppInst)
{
	DODELETE(ppInst, OprtSysLinux, IOprtSys);
}

OprtSysLinux *CREATE(OprtSysLinux)()
{
	DOCREATE(pCreate, OprtSysLinux, IOprtSys, NULL,
		METHOD(DoPaint));

	return pCreate;
}
