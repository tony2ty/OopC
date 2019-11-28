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


#include "BuilderHero.h"


typedef struct
{
	Actor *pActor;
} Fld;

/////////////////////////////////////////////////////////////////////////
//

__OVERRIDE static void BuildType(void *_pThis, va_list* pvlArgs)
{
	BuilderHero* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	bool* pRet = va_arg(*pvlArgs, bool*);

	const char* pTmp = "Ó¢ÐÛ";
	pFld->pActor->Call(pFld->pActor, "SetType", pTmp, pRet);
}

__OVERRIDE static void BuildGender(void *_pThis, va_list* pvlArgs)
{
	BuilderHero* pThis = pThis = _pThis;
	Fld* pFld = pThis->Fld;

	bool* pRet = va_arg(*pvlArgs, bool*);

	const char* pTmp = "ÄÐ";
	pFld->pActor->Call(pFld->pActor, "SetGender", pTmp, pRet);
}

__OVERRIDE static void BuildFace(void *_pThis, va_list* pvlArgs)
{
	BuilderHero* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	bool* pRet = va_arg(*pvlArgs, bool*);

	const char* pTmp = "Ó¢¿¡";
	pFld->pActor->Call(pFld->pActor, "SetFace", pTmp, pRet);
}

__OVERRIDE static void BuildCostume(void *_pThis, va_list* pvlArgs)
{
	BuilderHero* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	bool* pRet = va_arg(*pvlArgs, bool*);

	const char* pTmp = "¿ø¼×";
	pFld->pActor->Call(pFld->pActor, "SetCostume", pTmp, pRet);
}

__OVERRIDE static void BuildHairStyle(void *_pThis, va_list* pvlArgs)
{
	BuilderHero* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	bool* pRet = va_arg(*pvlArgs, bool*);

	const char* pTmp = "Æ®ÒÝ";
	pFld->pActor->Call(pFld->pActor, "SetHairStyle", pTmp, pRet);
}

__OVERRIDE static void CreateActor(void *_pThis, va_list* pvlArgs)
{
	BuilderHero* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	Actor** ppRet = va_arg(*pvlArgs, Actor * *);

	*ppRet = pFld->pActor;
}

/////////////////////////////////////////////////////////////////////////
//

__CONSTRUCTOR(BuilderHero)
{
	BuilderHero *pNew = __New(__TYPE(BuilderHero), sizeof(Fld), NULL, 6, 1,
		__METHOD(BuildType),
		__METHOD(BuildGender),
		__METHOD(BuildCostume),
		__METHOD(BuildHairStyle),
		__METHOD(CreateActor),
		__INHERIT(IBuilderActor));

	Fld* pFld = pNew->Fld;
	pFld->pActor = __NEW(Actor);

	return pNew;
}
