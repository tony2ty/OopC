
#include <stdio.h>
#include "Animal.h"

int main(int argc, char** argv)
{
	Animal* pAnimal = CREATE(Animal)("taoxing", 17);

	INVOKE(Animal)(pAnimal, "Eat", NULL);
	INVOKE(Animal)(pAnimal, "Sleep", NULL);
	INVOKE(Animal)(pAnimal, "Introduce", NULL);

	INVOKE(Animal)(pAnimal, "ToString", NULL);
	bool bRet = false;
	INVOKE(Animal)(pAnimal, "Equal", &(Object_Equal){&bRet, pAnimal	});

	DELETE(Animal)(&pAnimal);

	return 0;
}