
#include <stdlib.h>
#include <stdio.h>

#include "ActorController.h"
#include "IBuilderActor.h"
#include "BuilderHero.h"
#include "BuilderAngel.h"
#include "BuilderDevil.h"

int main(int argc, char **argv)
{
    RLSLOCALMEMBRA();

	bool bRet = false;

	IBuilderActor *pBuilder = NULL;
	{
		//BuilderHero *pBuilderHero = NEW(BuilderHero); TORLS(DEL(BuilderHero), pBuilderHero);
		//pBuilder = SWITCH(pBuilderHero, BuilderHero, IBuilderActor);

		//BuilderAngel *pBuilderAngel = NEW(BuilderAngel); TORLS(DEL(BuilderAngel), pBuilderAngel);
		//pBuilder = SWITCH(pBuilderAngel, BuilderAngel, IBuilderActor);

        BuilderDevil *pBuilderDevil = NEW(BuilderDevil); TORLS(DEL(BuilderDevil), pBuilderDevil);
		pBuilder = SWITCH(pBuilderDevil, IBuilderActor);
	}

    ActorController *pController = NEW(ActorController); TORLS(DEL(ActorController), pController);
	Actor *pActor = NULL;
	pController->Call(pController, "Construct", &pActor, pBuilder, &bRet); TORLS(DEL(Actor), pActor);
	!!!
    char *pDesc = malloc(sizeof(char) * 10); TORLSMUTABLE(free, pDesc);
	pActor->Call(pActor, "GetType", &pDesc, &bRet);
	printf("%s\n", pDesc);
	pActor->Call(pActor, "GetGender", &pDesc, &bRet);
	printf("%s\n", pDesc);
	pActor->Call(pActor, "GetFace", &pDesc, &bRet);
	printf("%s\n", pDesc);
	pActor->Call(pActor, "GetCostume", &pDesc, &bRet);
	printf("%s\n", pDesc);
	pActor->Call(pActor, "GetHairStyle", &pDesc, &bRet);
	printf("%s\n", pDesc);

    RLSLOCALMEMKET();

	return 0;
}