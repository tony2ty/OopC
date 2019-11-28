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
#include <stdlib.h>


typedef struct
{
	char *pType;
	char *pGender;
	char *pFace;
	char *pCostume;
	char *pHairStyle;
} Fld;

///////////////////////////////////////////////////////////////////////
//

static void SetType(void *_pThis, va_list* pvlArgs)
{
	Actor* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	const char* pType = va_arg(*pvlArgs, const char*);
	bool* pRet = va_arg(*pvlArgs, bool*);

	size_t szLen = strlen(pType) + 1;
	if (strlen(pFld->pType) + 1 < szLen)
	{
		free(pFld->pType);
		pFld->pType = malloc(szLen);
		if (!pFld->pType)
		{
			*pRet = false;
			return;
		}
	}
	memcpy(pFld->pType, pType, szLen);
	*pRet = true;
}

static void GetType(void *_pThis, va_list* pvlArgs)
{
	Actor* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	char** ppType = va_arg(*pvlArgs, char**);
	bool* pRet = va_arg(*pvlArgs, bool*);

	size_t szLen = strlen(pFld->pType) + 1;
	if (*ppType || !(*ppType = malloc(szLen)))
	{
		*pRet = false;
		return;
	}
	memcpy(*ppType, pFld->pType, szLen);
	*pRet = true;
}

static void SetGender(void *_pThis, va_list* pvlArgs)
{
	Actor* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	const char* pGender = va_arg(*pvlArgs, const char*);
	bool* pRet = va_arg(*pvlArgs, bool*);

	size_t szLen = strlen(pGender) + 1;
	if (strlen(pFld->pGender) + 1 < szLen)
	{
		free(pFld->pGender);
		pFld->pGender = malloc(szLen);
		if (!pFld->pGender)
		{
			*pRet = false;
			return;
		}
	}
	memcpy(pFld->pGender, pGender, szLen);
	*pRet = true;
}

static void GetGender(void *_pThis, va_list* pvlArgs)
{
	Actor* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	char** ppGender = va_arg(*pvlArgs, char**);
	bool* pRet = va_arg(*pvlArgs, bool*);

	size_t szLen = strlen(pFld->pGender) + 1;
	if (*ppGender || !(*ppGender = malloc(szLen)))
	{
		*pRet = false;
		return;
	}
	memcpy(*ppGender, pFld->pGender, szLen);
	*pRet = true;
}

static void SetFace(void *_pThis, va_list* pvlArgs)
{
	Actor* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	const char* pFace = va_arg(*pvlArgs, const char*);
	bool* pRet = va_arg(*pvlArgs, bool*);

	size_t szLen = strlen(pFace) + 1;
	if (strlen(pFld->pFace) + 1 < szLen)
	{
		free(pFld->pFace);
		pFld->pFace = malloc(szLen);
		if (!pFld->pFace)
		{
			*pRet = false;
			return;
		}
	}
	memcpy(pFld->pFace, pFace, szLen);
	*pRet = true;
}

static void GetFace(void *_pThis, va_list* pvlArgs)
{
	Actor* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	char** ppFace = va_arg(*pvlArgs, char**);
	bool* pRet = va_arg(*pvlArgs, bool*);

	size_t szLen = strlen(pFld->pFace) + 1;
	if (*ppFace || !(*ppFace = malloc(szLen)))
	{
		*pRet = false;
		return;
	}
	memcpy(*ppFace, pFld->pFace, szLen);
	*pRet = true;
}

static void SetCostume(void *_pThis, va_list* pvlArgs)
{
	Actor *pThis = _pThis;
	Fld* pFld = pThis->Fld;

	const char* pCostume = va_arg(*pvlArgs, const char*);
	bool* pRet = va_arg(*pvlArgs, bool*);

	size_t szLen = strlen(pCostume) + 1;
	if (strlen(pFld->pCostume) + 1 < szLen)
	{
		free(pFld->pCostume);
		pFld->pCostume = malloc(szLen);
		if (!pFld->pCostume)
		{
			*pRet = false;
			return;
		}
	}
	memcpy(pFld->pCostume, pCostume, szLen);
	*pRet = true;
}

static void GetCostume(void *_pThis, va_list* pvlArgs)
{
	Actor* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	char** ppCostume = va_arg(*pvlArgs, char**);
	bool* pRet = va_arg(*pvlArgs, bool*);

	size_t szLen = strlen(pFld->pCostume) + 1;
	if (*ppCostume || !(*ppCostume = malloc(szLen)))
	{
		*pRet = false;
		return;
	}
	memcpy(*ppCostume, pFld->pCostume, szLen);
	*pRet = true;
}

static void SetHairStyle(void *_pThis, va_list* pvlArgs)
{
	Actor* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	const char* pHairStyle = va_arg(*pvlArgs, const char*);
	bool* pRet = va_arg(*pvlArgs, bool*);

	size_t szLen = strlen(pHairStyle) + 1;
	if (strlen(pFld->pHairStyle) + 1 < szLen)
	{
		free(pFld->pHairStyle);
		pFld->pHairStyle = malloc(szLen);
		if (!pFld->pHairStyle)
		{
			*pRet = false;
			return;
		}
	}
	memcpy(pFld->pHairStyle, pHairStyle, szLen);
	*pRet = true;
}

static void GetHairStyle(void *_pThis, va_list* pvlArgs)
{
	Actor* pThis = _pThis;
	Fld* pFld = pThis->Fld;

	char** ppHairStyle = va_arg(*pvlArgs, char**);
	bool* pRet = va_arg(*pvlArgs, bool*);

	size_t szLen = strlen(pFld->pHairStyle) + 1;
	if (*ppHairStyle || !(*ppHairStyle = malloc(szLen)))
	{
		*pRet = false;
		return;
	}
	memcpy(*ppHairStyle, pFld->pHairStyle, szLen);
	*pRet = true;
}

/////////////////////////////////////////////////////////////////////////
//

static void Clear(void* pParams)
{
	Actor* pSelf = pParams;
	Fld* pFld = pSelf->Fld;
	free(pFld->pType);
	free(pFld->pGender);
	free(pFld->pFace);
	free(pFld->pCostume);
	free(pFld->pHairStyle);
}

__CONSTRUCTOR(Actor)
{
	Actor *pNew = __New(__TYPE(Actor), sizeof(Fld), Clear, 10, 0,
		__METHOD(SetType),
		__METHOD(GetType),
		__METHOD(SetGender),
		__METHOD(GetGender),
		__METHOD(SetFace),
		__METHOD(GetFace),
		__METHOD(SetCostume),
		__METHOD(GetCostume),
		__METHOD(SetHairStyle),
		__METHOD(GetHairStyle));

	Fld* pFld = pNew->Fld;

	char* pTmp = "OK";
	size_t szLen = strlen(pTmp) + 1;
	pFld->pType = malloc(szLen); memcpy(pFld->pType, pTmp, szLen);
	pFld->pGender = malloc(szLen); memcpy(pFld->pGender, pTmp, szLen);
	pFld->pFace = malloc(szLen); memcpy(pFld->pFace, pTmp, szLen);
	pFld->pCostume = malloc(szLen); memcpy(pFld->pCostume, pTmp, szLen);
	pFld->pHairStyle = malloc(szLen); memcpy(pFld->pHairStyle, pTmp, szLen);

	return pNew;
}
