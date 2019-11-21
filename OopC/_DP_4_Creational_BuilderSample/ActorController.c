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


#include "ActorController.h"


struct ActorController_Fld
{
	CHAINDECLARE;
};

////////////////////////////////////////////////////////////////////////////
//

static void Construct(ParamIn*pParams)
{
	ActorController* pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	Actor** ppActor = va_arg(vlArgs, Actor * *);
	IBuilderActor* pBuilder = va_arg(vlArgs, IBuilderActor*);
	bool* pRet = va_arg(vlArgs, bool*);

	bool bTmp = false;
	pBuilder->Call(pBuilder, "BuildType", &bTmp);
	if (!bTmp)
	{
		*pRet = false;
		return;
	}
	pBuilder->Call(pBuilder, "BuildGender", &bTmp);
	if (!bTmp)
	{
		*pRet = false;
		return;
	}
	pBuilder->Call(pBuilder, "BuildFace", &bTmp);
	if (!bTmp)
	{
		*pRet = false;
		return;
	}
	pBuilder->Call(pBuilder, "BuildCostume", &bTmp);
	if (!bTmp)
	{
		*pRet = false;
		return;
	}
	pBuilder->Call(pBuilder, "BuildHairStyle", &bTmp);
	if (!bTmp)
	{
		*pRet = false;
		return;
	}

	pBuilder->Call(pBuilder, "CreateActor", ppActor);
}

////////////////////////////////////////////////////////////////////////////
//

static bool __CALL(ActorController)(ActorController* pSelf, const char* pMethodName, ...)
{
	DOCALL(pSelf, pMethodName);
}

static void* __EXTEND(ActorController)(ActorController* pSelf)
{
	DOEXTEND(pSelf);
}

void __DEL(ActorController)(ActorController* pSelf)
{
	DODEL(pSelf, Object);
}

ActorController* __NEW(ActorController)()
{
	DONEW(pNew, ActorController, Object, NULL,
		METHOD(Construct));

	return pNew;
}
