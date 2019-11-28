
#include <stdlib.h>
#include <stdio.h>

#include "ActorController.h"
#include "IBuilderActor.h"
#include "BuilderHero.h"
#include "BuilderAngel.h"
#include "BuilderDevil.h"

int main(int argc, char **argv)
{
	bool bRet = false;

	IBuilderActor *pBuilder = NULL;
	{
		//BuilderHero *pBuilderHero = NEW(BuilderHero);
		//pBuilder = __Cvt(pBuilderHero, __TYPE(IBuilderActor));

		//BuilderAngel *pBuilderAngel = NEW(BuilderAngel);
		//pBuilder = __Cvt(pBuilderAngel, __TYPE(IBuilderActor));

        BuilderDevil *pBuilderDevil = __NEW(BuilderDevil);
		pBuilder = __Cvt(pBuilderDevil, __TYPE(IBuilderActor));
	}

    ActorController *pController = __NEW(ActorController);
	Actor *pActor = NULL;
	pController->Call(pController, "Construct", &pActor, pBuilder, &bRet);

	char* pDesc = NULL;
	pActor->Call(pActor, "GetType", &pDesc, &bRet);
	printf("%s\n", pDesc);
	free(pDesc); pDesc = NULL;
	pActor->Call(pActor, "GetGender", &pDesc, &bRet);
	printf("%s\n", pDesc);
	free(pDesc); pDesc = NULL;
	pActor->Call(pActor, "GetFace", &pDesc, &bRet);
	printf("%s\n", pDesc);
	free(pDesc); pDesc = NULL;
	pActor->Call(pActor, "GetCostume", &pDesc, &bRet);
	printf("%s\n", pDesc);
	free(pDesc); pDesc = NULL;
	pActor->Call(pActor, "GetHairStyle", &pDesc, &bRet);
	printf("%s\n", pDesc);

	free(pDesc);
	pActor->Destroy(pActor);
	pController->Destroy(pController);
	pBuilder->Destroy(pBuilder);

	return 0;
}