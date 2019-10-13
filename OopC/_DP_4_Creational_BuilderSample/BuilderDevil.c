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


struct BuilderDevil
{
	CHAINDEF;

	Actor *pActor;
};

/////////////////////////////////////////////////////////////////////////
//

static void BuildType(void *pParams)
{
	BuilderDevil *pThis = ((ParamIn *)pParams)->pInst;
	BuilderDevil_BuildType *pIn = ((ParamIn *)pParams)->pIn;

	char *pTmp = "¶ñÄ§";
	INVOKE(Actor)(pThis->pActor, "Type", &(Actor_Type){true, &pTmp});
}

static void BuildGender(void *pParams)
{
	BuilderDevil *pThis = ((ParamIn *)pParams)->pInst;
	BuilderDevil_BuildGender *pIn = ((ParamIn *)pParams)->pIn;

	char *pTmp = "Ñý";
	INVOKE(Actor)(pThis->pActor, "Gender", &(Actor_Gender){true, &pTmp});
}

static void BuildFace(void *pParams)
{
	BuilderDevil *pThis = ((ParamIn *)pParams)->pInst;
	BuilderDevil_BuildFace *pIn = ((ParamIn *)pParams)->pIn;

	char *pTmp = "³óÂª";
	INVOKE(Actor)(pThis->pActor, "Face", &(Actor_Face){true, &pTmp});
}

static void BuildCostume(void *pParams)
{
	BuilderDevil *pThis = ((ParamIn *)pParams)->pInst;
	BuilderDevil_BuildCostume *pIn = ((ParamIn *)pParams)->pIn;

	char *pTmp = "ºÚÒÂ";
	INVOKE(Actor)(pThis->pActor, "Costume", &(Actor_Costume){true, &pTmp});
}

static void BuildHairStyle(void *pParams)
{
	BuilderDevil *pThis = ((ParamIn *)pParams)->pInst;
	BuilderDevil_BuildHairStyle *pIn = ((ParamIn *)pParams)->pIn;

	char *pTmp = "¹âÍ·";
	INVOKE(Actor)(pThis->pActor, "HairStyle", &(Actor_HairStyle){true, &pTmp});
}

static void CreateActor(void *pParams)
{
	BuilderDevil *pThis = ((ParamIn *)pParams)->pInst;
	BuilderDevil_CreateActor *pIn = ((ParamIn *)pParams)->pIn;

	*pIn->ppRet = pThis->pActor;
}

/////////////////////////////////////////////////////////////////////////
//

bool INVOKE(BuilderDevil)(BuilderDevil *pInst, char *pFuncName, void *pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(BuilderDevil)(BuilderDevil *pInst)
{
	DOEXTEND(pInst);
}

void DELETE(BuilderDevil)(BuilderDevil **ppInst)
{
	DODELETE(ppInst, BuilderDevil, IBuilderActor);
}

BuilderDevil *CREATE(BuilderDevil)()
{
	DOCREATE(pCreate, BuilderDevil, IBuilderActor, NULL,
		METHOD(BuildType)
		METHOD(BuildGender)
		METHOD(BuildFace)
		METHOD(BuildCostume)
		METHOD(BuildHairStyle)
		METHOD(CreateActor));

	pCreate->pActor = CREATE(Actor)();

	return pCreate;
}
