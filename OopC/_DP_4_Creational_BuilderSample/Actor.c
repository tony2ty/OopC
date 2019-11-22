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


#include "Actor.h"

#include <string.h>

struct Actor_Fld
{
	CHAINDECLARE;

	char *pType;
	char *pGender;
	char *pFace;
	char *pCostume;
	char *pHairStyle;
};

///////////////////////////////////////////////////////////////////////
//

static void SetType(void *_pThis, va_list vlArgs)
{
	Actor* pThis = _pThis;

	const char* pType = va_arg(vlArgs, const char*);
	bool* pRet = va_arg(vlArgs, bool*);

	size_t szLen = strlen(pType) + 1;
	if (strlen(pThis->pFld->pType) + 1 < szLen)
	{
		free(pThis->pFld->pType);
		pThis->pFld->pType = malloc(szLen);
		if (!pThis->pFld->pType)
		{
			*pRet = false;
			return;
		}
	}
	memcpy(pThis->pFld->pType, pType, szLen);
	*pRet = true;
}

static void GetType(void *_pThis, va_list vlArgs)
{
	Actor* pThis = _pThis;

	char** ppType = va_arg(vlArgs, char**);
	bool* pRet = va_arg(vlArgs, bool*);

	size_t szLen = strlen(pThis->pFld->pType) + 1;
	if (*ppType || !(*ppType = malloc(szLen)))
	{
		*pRet = false;
		return;
	}
	memcpy(*ppType, pThis->pFld->pType, szLen);
	*pRet = true;
}

static void SetGender(void *_pThis, va_list vlArgs)
{
	Actor* pThis = _pThis;

	const char* pGender = va_arg(vlArgs, const char*);
	bool* pRet = va_arg(vlArgs, bool*);

	size_t szLen = strlen(pGender) + 1;
	if (strlen(pThis->pFld->pGender) + 1 < szLen)
	{
		free(pThis->pFld->pGender);
		pThis->pFld->pGender = malloc(szLen);
		if (!pThis->pFld->pGender)
		{
			*pRet = false;
			return;
		}
	}
	memcpy(pThis->pFld->pGender, pGender, szLen);
	*pRet = true;
}

static void GetGender(void *_pThis, va_list vlArgs)
{
	Actor* pThis = _pThis;

	char** ppGender = va_arg(vlArgs, char**);
	bool* pRet = va_arg(vlArgs, bool*);

	size_t szLen = strlen(pThis->pFld->pGender) + 1;
	if (*ppGender || !(*ppGender = malloc(szLen)))
	{
		*pRet = false;
		return;
	}
	memcpy(*ppGender, pThis->pFld->pGender, szLen);
	*pRet = true;
}

static void SetFace(void *_pThis, va_list vlArgs)
{
	Actor* pThis = _pThis;

	const char* pFace = va_arg(vlArgs, const char*);
	bool* pRet = va_arg(vlArgs, bool*);

	size_t szLen = strlen(pFace) + 1;
	if (strlen(pThis->pFld->pFace) + 1 < szLen)
	{
		free(pThis->pFld->pFace);
		pThis->pFld->pFace = malloc(szLen);
		if (!pThis->pFld->pFace)
		{
			*pRet = false;
			return;
		}
	}
	memcpy(pThis->pFld->pFace, pFace, szLen);
	*pRet = true;
}

static void GetFace(void *_pThis, va_list vlArgs)
{
	Actor* pThis = _pThis;

	char** ppFace = va_arg(vlArgs, char**);
	bool* pRet = va_arg(vlArgs, bool*);

	size_t szLen = strlen(pThis->pFld->pFace) + 1;
	if (*ppFace || !(*ppFace = malloc(szLen)))
	{
		*pRet = false;
		return;
	}
	memcpy(*ppFace, pThis->pFld->pFace, szLen);
	*pRet = true;
}

static void SetCostume(void *_pThis, va_list vlArgs)
{
	Actor *pThis = _pThis;

	const char* pCostume = va_arg(vlArgs, const char*);
	bool* pRet = va_arg(vlArgs, bool*);

	size_t szLen = strlen(pCostume) + 1;
	if (strlen(pThis->pFld->pCostume) + 1 < szLen)
	{
		free(pThis->pFld->pCostume);
		pThis->pFld->pCostume = malloc(szLen);
		if (!pThis->pFld->pCostume)
		{
			*pRet = false;
			return;
		}
	}
	memcpy(pThis->pFld->pCostume, pCostume, szLen);
	*pRet = true;
}

static void GetCostume(void *_pThis, va_list vlArgs)
{
	Actor* pThis = _pThis;

	char** ppCostume = va_arg(vlArgs, char**);
	bool* pRet = va_arg(vlArgs, bool*);

	size_t szLen = strlen(pThis->pFld->pCostume) + 1;
	if (*ppCostume || !(*ppCostume = malloc(szLen)))
	{
		*pRet = false;
		return;
	}
	memcpy(*ppCostume, pThis->pFld->pCostume, szLen);
	*pRet = true;
}

static void SetHairStyle(void *_pThis, va_list vlArgs)
{
	Actor* pThis = _pThis;

	const char* pHairStyle = va_arg(vlArgs, const char*);
	bool* pRet = va_arg(vlArgs, bool*);

	size_t szLen = strlen(pHairStyle) + 1;
	if (strlen(pThis->pFld->pHairStyle) + 1 < szLen)
	{
		free(pThis->pFld->pHairStyle);
		pThis->pFld->pHairStyle = malloc(szLen);
		if (!pThis->pFld->pHairStyle)
		{
			*pRet = false;
			return;
		}
	}
	memcpy(pThis->pFld->pHairStyle, pHairStyle, szLen);
	*pRet = true;
}

static void GetHairStyle(void *_pThis, va_list vlArgs)
{
	Actor* pThis = _pThis;

	char** ppHairStyle = va_arg(vlArgs, char**);
	bool* pRet = va_arg(vlArgs, bool*);

	size_t szLen = strlen(pThis->pFld->pHairStyle) + 1;
	if (*ppHairStyle || !(*ppHairStyle = malloc(szLen)))
	{
		*pRet = false;
		return;
	}
	memcpy(*ppHairStyle, pThis->pFld->pHairStyle, szLen);
	*pRet = true;
}

/////////////////////////////////////////////////////////////////////////
//

static void __CLEAR(Actor)(void* pParams)
{
	Actor* pSelf = pParams;
	free(pSelf->pFld->pType);
	free(pSelf->pFld->pGender);
	free(pSelf->pFld->pFace);
	free(pSelf->pFld->pCostume);
	free(pSelf->pFld->pHairStyle);
}

static bool __CALL(Actor)(Actor* pSelf, const char* pMethodName, ...)
{
	DOCALL(pSelf, pMethodName);
}

static void* __EXTEND(Actor)(Actor* pSelf)
{
	DOEXTEND(pSelf);
}

void __DEL(Actor)(Actor* pSelf)
{
	DODEL(pSelf, Object);
}

Actor* __NEW(Actor)()
{
	DONEW(pNew, Actor, Object, __CLEAR(Actor),
		METHOD(SetType)
		METHOD(GetType)
		METHOD(SetGender)
		METHOD(GetGender)
		METHOD(SetFace)
		METHOD(GetFace)
		METHOD(SetCostume)
		METHOD(GetCostume)
		METHOD(SetHairStyle)
		METHOD(GetHairStyle));

	pNew->pFld->pType = NULL;
	pNew->pFld->pGender = NULL;
	pNew->pFld->pFace = NULL;
	pNew->pFld->pCostume = NULL;
	pNew->pFld->pHairStyle = NULL;

	return pNew;
}
