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

#include <malloc.h>

struct ActorController
{
	CHAINDEF;
};

////////////////////////////////////////////////////////////////////////////
//

static void Construct(void *pParams)
{
	ActorController *pThis = ((ParamIn *)pParams)->pInst;
	ActorController_Construct *pIn = ((ParamIn *)pParams)->pIn;

	INVOKE(IBuilderActor)(pIn->pBuilder, "BuildType", NULL);
	INVOKE(IBuilderActor)(pIn->pBuilder, "BuildGender", NULL);
	INVOKE(IBuilderActor)(pIn->pBuilder, "BuildFace", NULL);
	INVOKE(IBuilderActor)(pIn->pBuilder, "BuildCostume", NULL);
	INVOKE(IBuilderActor)(pIn->pBuilder, "BuildHairStyle", NULL);

	INVOKE(IBuilderActor)(pIn->pBuilder, "CreateActor", &(IBuilderActor_CreateActor){ pIn->ppRet });
}

////////////////////////////////////////////////////////////////////////////
//

bool INVOKE(ActorController)(ActorController *pInst, char *pFuncName, void *pParams)
{
	DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(ActorController)(ActorController *pInst)
{
	DOEXTEND(pInst);
}

void DELETE(ActorController)(ActorController **ppInst)
{
	DODELETE(ppInst, ActorController, Object);
}

ActorController *CREATE(ActorController)()
{
	DOCREATE(pCreate, ActorController, Object, NULL,
		METHOD(Construct));

	return pCreate;
}
