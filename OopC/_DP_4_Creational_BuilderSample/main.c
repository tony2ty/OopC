
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

	IBuilderActor *pBuilder = NULL;
	{
		//BuilderHero *pBuilderHero = CREATE(BuilderHero)(); TORLS(DELETE(BuilderHero), pBuilderHero);
		//pBuilder = SWITCH(pBuilderHero, BuilderHero, IBuilderActor);

		//BuilderAngel *pBuilderAngel = CREATE(BuilderAngel)(); TORLS(DELETE(BuilderAngel), pBuilderAngel);
		//pBuilder = SWITCH(pBuilderAngel, BuilderAngel, IBuilderActor);

        BuilderDevil *pBuilderDevil = CREATE(BuilderDevil)(); TORLS(DELETE(BuilderDevil), pBuilderDevil);
		pBuilder = SWITCH(pBuilderDevil, BuilderDevil, IBuilderActor);
	}

    ActorController *pController = CREATE(ActorController)(); TORLS(DELETE(ActorController), pController);
	Actor *pActor = NULL;
    INVOKE(ActorController)(pController, "Construct", &(ActorController_Construct){ &pActor, pBuilder }); TORLS(DELETE(Actor), pActor);

    char *pDesc = malloc(sizeof(char) * 10); TORLS(free, pDesc);
	INVOKE(Actor)(pActor, "Type", &(Actor_Type){false, &pDesc});
	printf("%s\n", pDesc);
	INVOKE(Actor)(pActor, "Gender", &(Actor_Gender){false, &pDesc});
	printf("%s\n", pDesc);
	INVOKE(Actor)(pActor, "Face", &(Actor_Face){false, &pDesc});
	printf("%s\n", pDesc);
	INVOKE(Actor)(pActor, "Costume", &(Actor_Costume){false, &pDesc});
	printf("%s\n", pDesc);
	INVOKE(Actor)(pActor, "HairStyle", &(Actor_HairStyle){false, &pDesc});
	printf("%s\n", pDesc);

	system("pause");

    RLSLOCALMEMKET();

	return 0;
}