
#define ___DEBUG

#include <stdio.h>
#include "Animal.h"
#include "Penguin.h"

int main(int argc, char** argv)
{
	bool bRet = false;

	////////////////////////////////////////////////////////////////////////////////
	//

	Animal* pAnimal = CREATE(Animal)("taoxing", 17);
	INVOKE(Animal)(pAnimal, "Eat", NULL);
	INVOKE(Animal)(pAnimal, "Sleep", NULL);
	INVOKE(Animal)(pAnimal, "Introduce", NULL);
	INVOKE(Animal)(pAnimal, "ToString", NULL);
	INVOKE(Animal)(pAnimal, "Equal", &(Object_Equal){&bRet, pAnimal	});

	DELETE(Animal)(&pAnimal);

	////////////////////////////////////////////////////////////////////////////////
	//

	Penguin* pS = CREATE(Penguin)("Æó¶ì", 113);
	INVOKE(Penguin)(pS, "Eat", NULL);
	INVOKE(Penguin)(pS, "Sleep", NULL);
	INVOKE(Penguin)(pS, "Introduce", NULL);
	INVOKE(Penguin)(pS, "ToString", NULL);
	INVOKE(Penguin)(pS, "Equal", &(Object_Equal){&bRet, pAnimal});
	INVOKE(Penguin)(pS, "Equal", &(Object_Equal){&bRet, pS});
	DELETE(Penguin)(&pS);

	return 0;
}