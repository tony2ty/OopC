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


struct BuilderAngel
{
	CHAINDEF;

	Actor *pActor;
};

/////////////////////////////////////////////////////////////////////////
//

OVERRIDE static void BuildType(void *pParams)
{
	BuilderAngel *pThis = ((ParamIn *)pParams)->pInst;
	IBuilderActor_BuildType *pIn = ((ParamIn *)pParams)->pIn;

	char *pTmp = "天使";
	INVOKE(Actor)(pThis->pActor, "Type", &(Actor_Type){true, &pTmp});
}

OVERRIDE static void BuildGender(void *pParams)
{
	BuilderAngel *pThis = ((ParamIn *)pParams)->pInst;
    IBuilderActor_BuildGender *pIn = ((ParamIn *)pParams)->pIn;

	char *pTmp = "女";
	INVOKE(Actor)(pThis->pActor, "Gender", &(Actor_Gender){true, &pTmp});
}

OVERRIDE static void BuildFace(void *pParams)
{
	BuilderAngel *pThis = ((ParamIn *)pParams)->pInst;
    IBuilderActor_BuildFace *pIn = ((ParamIn *)pParams)->pIn;

	char *pTmp = "漂亮";
	INVOKE(Actor)(pThis->pActor, "Face", &(Actor_Face){true, &pTmp});
}

OVERRIDE static void BuildCostume(void *pParams)
{
	BuilderAngel *pThis = ((ParamIn *)pParams)->pInst;
    IBuilderActor_BuildCostume *pIn = ((ParamIn *)pParams)->pIn;

	char *pTmp = "白裙";
	INVOKE(Actor)(pThis->pActor, "Costume", &(Actor_Costume){true, &pTmp});
}

OVERRIDE static void BuildHairStyle(void *pParams)
{
	BuilderAngel *pThis = ((ParamIn *)pParams)->pInst;
    IBuilderActor_BuildHairStyle *pIn = ((ParamIn *)pParams)->pIn;

	char *pTmp = "披肩长发";
	INVOKE(Actor)(pThis->pActor, "HairStyle", &(Actor_HairStyle){true, &pTmp});
}

OVERRIDE static void CreateActor(void *pParams)
{
	BuilderAngel *pThis = ((ParamIn *)pParams)->pInst;
    IBuilderActor_CreateActor *pIn = ((ParamIn *)pParams)->pIn;

	*pIn->ppRet = pThis->pActor;
}

/////////////////////////////////////////////////////////////////////////
//

bool INVOKE(BuilderAngel)(BuilderAngel *pInst, char *pFuncName, void *pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(BuilderAngel)(BuilderAngel *pInst)
{
	DOEXTEND(pInst);
}

void DELETE(BuilderAngel)(BuilderAngel *pInst)
{
	DODELETE(pInst, BuilderAngel, IBuilderActor);
}

BuilderAngel *CREATE(BuilderAngel)()
{
	DOCREATE(pCreate, BuilderAngel, IBuilderActor, NULL,
		METHOD(BuildType)
		METHOD(BuildGender)
		METHOD(BuildFace)
		METHOD(BuildCostume)
		METHOD(BuildHairStyle)
		METHOD(CreateActor));

	pCreate->pActor = CREATE(Actor)();

	return pCreate;
}
