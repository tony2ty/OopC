
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

#include "ActorController.h"
#include "IBuilderActor.h"
#include "BuilderHero.h"
#include "BuilderAngel.h"
#include "BuilderDevil.h"

int main(int argc, char **argv)
{
	IBuilderActor *pBuilder = NULL;
	{
		//BuilderHero *pBuilderHero = CREATE(BuilderHero)();
		//pBuilder = SWITCH(pBuilderHero, BuilderHero, IBuilderActor);

		//BuilderAngel *pBuilderAngel = CREATE(BuilderAngel)();
		//pBuilder = SWITCH(pBuilderAngel, BuilderAngel, IBuilderActor);

		BuilderDevil *pBuilderDevil = CREATE(BuilderDevil)();
		pBuilder = SWITCH(pBuilderDevil, BuilderDevil, IBuilderActor);
	}

	ActorController *pController = CREATE(ActorController)();
	Actor *pActor = NULL;
	INVOKE(ActorController)(pController, "Construct", &(ActorController_Construct){ &pActor, pBuilder });

	char *pDesc = malloc(sizeof(char) * 10);
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

	free(pDesc);
	DELETE(Actor)(&pActor);
	DELETE(ActorController)(&pController);
	DELETE(IBuilderActor)(&pBuilder);

	system("pause");

	return 0;
}