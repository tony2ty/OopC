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

struct Actor
{
	CHAINDEF;

	char *pType;
	char *pGender;
	char *pFace;
	char *pCostume;
	char *pHairStyle;
};

///////////////////////////////////////////////////////////////////////
//

static void Type(void *pParams)
{
	Actor *pThis = ((ParamIn *)pParams)->pInst;
	Actor_Type *pIn = ((ParamIn *)pParams)->pIn;

	if (pIn->bSetter)
	{
		int nLen = strlen(*pIn->ppType) + 1;
		pThis->pType = memcpy(realloc(pThis->pType, nLen), *pIn->ppType, nLen);
	}
	else
	{
		int nLen = strlen(pThis->pType) + 1;
		*pIn->ppType = memcpy(realloc(*pIn->ppType, nLen), pThis->pType, nLen);
	}
}

static void Gender(void *pParams)
{
	Actor *pThis = ((ParamIn *)pParams)->pInst;
	Actor_Gender *pIn = ((ParamIn *)pParams)->pIn;

	if (pIn->bSetter)
	{
		int nLen = strlen(*pIn->ppGender) + 1;
		pThis->pGender = memcpy(realloc(pThis->pGender, nLen), *pIn->ppGender, nLen);
	}
	else
	{
		int nLen = strlen(pThis->pGender) + 1;
		*pIn->ppGender = memcpy(realloc(*pIn->ppGender, nLen), pThis->pGender, nLen);
	}
}

static void Face(void *pParams)
{
	Actor *pThis = ((ParamIn *)pParams)->pInst;
	Actor_Face *pIn = ((ParamIn *)pParams)->pIn;

	if (pIn->bSetter)
	{
		int nLen = strlen(*pIn->ppFace) + 1;
		pThis->pFace = memcpy(realloc(pThis->pFace, nLen), *pIn->ppFace, nLen);
	}
	else
	{
		int nLen = strlen(pThis->pFace) + 1;
		*pIn->ppFace = memcpy(realloc(*pIn->ppFace, nLen), pThis->pFace, nLen);
	}
}

static void Costume(void *pParams)
{
	Actor *pThis = ((ParamIn *)pParams)->pInst;
	Actor_Costume *pIn = ((ParamIn *)pParams)->pIn;

	if (pIn->bSetter)
	{
		int nLen = strlen(*pIn->ppCostume) + 1;
		pThis->pCostume = memcpy(realloc(pThis->pCostume, nLen), *pIn->ppCostume, nLen);
	}
	else
	{
		int nLen = strlen(pThis->pCostume) + 1;
		*pIn->ppCostume = memcpy(realloc(*pIn->ppCostume, nLen), pThis->pCostume, nLen);
	}
}

static void HairStyle(void *pParams)
{
	Actor *pThis = ((ParamIn *)pParams)->pInst;
	Actor_HairStyle *pIn = ((ParamIn *)pParams)->pIn;

	if (pIn->bSetter)
	{
		int nLen = strlen(*pIn->ppHairStype) + 1;
		pThis->pHairStyle = memcpy(realloc(pThis->pHairStyle, nLen), *pIn->ppHairStype, nLen);
	}
	else
	{
		int nLen = strlen(pThis->pHairStyle) + 1;
		*pIn->ppHairStype = memcpy(realloc(*pIn->ppHairStype, nLen), pThis->pHairStyle, nLen);
	}
}

///////////////////////////////////////////////////////////////////////
//

static void ClearExtraMem(void *pToClear)
{
	Actor *pInst = (Actor *)pToClear;
	free(pInst->pType);
	free(pInst->pGender);
	free(pInst->pFace);
	free(pInst->pCostume);
	free(pInst->pHairStyle);
}

/////////////////////////////////////////////////////////////////////////
//

bool INVOKE(Actor)(Actor *pInst, char *pFuncName, void *pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(Actor)(Actor *pInst)
{
	DOEXTEND(pInst);
}

void DELETE(Actor)(Actor **ppInst)
{
	DODELETE(ppInst, Actor, Object);
}

Actor *CREATE(Actor)()
{
	DOCREATE(pCreate, Actor, Object, GenerateExtraMemRef(ClearExtraMem, pCreate),
		METHOD(Type)
		METHOD(Gender)
		METHOD(Face)
		METHOD(Costume)
		METHOD(HairStyle));

	pCreate->pType = NULL;
	pCreate->pGender = NULL;
	pCreate->pFace = NULL;
	pCreate->pCostume = NULL;
	pCreate->pHairStyle = NULL;

	return pCreate;
}
