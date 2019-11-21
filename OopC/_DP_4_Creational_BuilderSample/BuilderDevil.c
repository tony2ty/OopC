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


#include "BuilderDevil.h"


struct BuilderDevil_Fld
{
	CHAINDECLARE;

	Actor *pActor;
};

/////////////////////////////////////////////////////////////////////////
//

OVERRIDE static void BuildType(ParamIn*pParams)
{
	BuilderDevil *pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	bool* pRet = va_arg(vlArgs, bool*);

	const char *pTmp = "��ħ";
	pThis->pFld->pActor->Call(pThis->pFld->pActor, "SetType", pTmp, pRet);
}

OVERRIDE static void BuildGender(ParamIn*pParams)
{
	BuilderDevil *pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	bool* pRet = va_arg(vlArgs, bool*);

	const char *pTmp = "��";
	pThis->pFld->pActor->Call(pThis->pFld->pActor, "SetGender", pTmp, pRet);
}

OVERRIDE static void BuildFace(ParamIn*pParams)
{
	BuilderDevil *pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	bool* pRet = va_arg(vlArgs, bool*);

	const char *pTmp = "��ª";
	pThis->pFld->pActor->Call(pThis->pFld->pActor, "SetFace", pTmp, pRet);
}

OVERRIDE static void BuildCostume(ParamIn*pParams)
{
	BuilderDevil *pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	bool* pRet = va_arg(vlArgs, bool*);

	const char *pTmp = "����";
	pThis->pFld->pActor->Call(pThis->pFld->pActor, "SetCostume", pTmp, pRet);
}

OVERRIDE static void BuildHairStyle(ParamIn*pParams)
{
	BuilderDevil *pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	bool* pRet = va_arg(vlArgs, bool*);

	const char *pTmp = "��ͷ";
	pThis->pFld->pActor->Call(pThis->pFld->pActor, "SetHairStyle", pTmp, pRet);
}

OVERRIDE static void CreateActor(ParamIn*pParams)
{
	BuilderDevil *pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	Actor** ppRet = va_arg(vlArgs, Actor * *);

	*ppRet = pThis->pFld->pActor;
}

/////////////////////////////////////////////////////////////////////////
//

static bool __CALL(BuilderDevil)(BuilderDevil* pSelf, const char* pMethodName, ...)
{
	DOCALL(pSelf, pMethodName);
}

static void* __EXTEND(BuilderDevil)(BuilderDevil* pSelf)
{
	DOEXTEND(pSelf);
}

void __DEL(BuilderDevil)(BuilderDevil* pSelf)
{
	DODEL(pSelf, IBuilderActor);
}

BuilderDevil* __NEW(BuilderDevil)()
{
	DONEW(pNew, BuilderDevil, IBuilderActor, NULL,
		METHOD(BuildType)
		METHOD(BuildGender)
		METHOD(BuildFace)
		METHOD(BuildCostume)
		METHOD(BuildHairStyle)
		METHOD(CreateActor));

	pNew->pFld->pActor = NEW(Actor);

	return pNew;
}
