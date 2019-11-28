
#include <stdio.h>
#include "ModelGenerator.h"

int main(int argc, char **argv)
{
    ModelGenerator *pGenerator = __NEW(ModelGenerator);
    ModelGenerator *pGenerator2 = __NEW(ModelGenerator);

	printf("The two Generator is%sthe same.\n", (pGenerator == pGenerator2 ? " " : " not "));
    int nModel = -1;
    pGenerator->Call(pGenerator, "GetModel", &nModel);
    printf("The new model generated is %d.\n", nModel);

	pGenerator->Destroy(pGenerator);
	//pGenerator2->Destroy(pGenerator2);//!!!

    return 0;
}