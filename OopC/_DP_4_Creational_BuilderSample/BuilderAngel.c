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


#include "BuilderAngel.h"


struct BuilderAngel_Fld
{
	CHAINDECLARE;

	Actor *pActor;
};

/////////////////////////////////////////////////////////////////////////
//

OVERRIDE static void BuildType(void *_pThis, va_list vlArgs)
{
	BuilderAngel* pThis = _pThis;

	bool* pRet = va_arg(vlArgs, bool*);

	const char* pTmp = "天使";
	pThis->pFld->pActor->Call(pThis->pFld->pActor, "SetType", pTmp, pRet);
}

OVERRIDE static void BuildGender(void *_pThis, va_list vlArgs)
{
	BuilderAngel* pThis = _pThis;

	bool* pRet = va_arg(vlArgs, bool*);

	const char* pTmp = "女";
	pThis->pFld->pActor->Call(pThis->pFld->pActor, "SetGender", pTmp, pRet);
}

OVERRIDE static void BuildFace(void *_pThis, va_list vlArgs)
{
	BuilderAngel* pThis = _pThis;

	bool* pRet = va_arg(vlArgs, bool*);

	const char* pTmp = "漂亮";
	pThis->pFld->pActor->Call(pThis->pFld->pActor, "SetFace", pTmp, pRet);
}

OVERRIDE static void BuildCostume(void *_pThis, va_list vlArgs)
{
	BuilderAngel* pThis = _pThis;

	bool* pRet = va_arg(vlArgs, bool*);

	const char* pTmp = "白裙";
	pThis->pFld->pActor->Call(pThis->pFld->pActor, "SetCostume", pTmp, pRet);
}

OVERRIDE static void BuildHairStyle(void *_pThis, va_list vlArgs)
{
	BuilderAngel* pThis = _pThis;

	bool* pRet = va_arg(vlArgs, bool*);

	const char* pTmp = "披肩长发";
	pThis->pFld->pActor->Call(pThis->pFld->pActor, "SetHairStyle", pTmp, pRet);
}

OVERRIDE static void CreateActor(void *_pThis, va_list vlArgs)
{
	BuilderAngel* pThis = _pThis;

	Actor** ppRet = va_arg(vlArgs, Actor * *);

	*ppRet = pThis->pFld->pActor;
}

/////////////////////////////////////////////////////////////////////////
//

static bool __CALL(BuilderAngel)(BuilderAngel* pSelf, const char* pMethodName, ...)
{
	DOCALL(pSelf, pMethodName);
}

static void* __EXTEND(BuilderAngel)(BuilderAngel* pSelf)
{
	DOEXTEND(pSelf);
}

void __DEL(BuilderAngel)(BuilderAngel* pSelf)
{
	DODEL(pSelf, IBuilderActor);
}

BuilderAngel* __NEW(BuilderAngel)()
{
	DONEW(pNew, BuilderAngel, IBuilderActor, NULL,
		METHOD(BuildType)
		METHOD(BuildGender)
		METHOD(BuildFace)
		METHOD(BuildCostume)
		METHOD(BuildHairStyle)
		METHOD(CreateActor));

	pNew->pFld->pActor = NEW(Actor);

	return pNew;
}
