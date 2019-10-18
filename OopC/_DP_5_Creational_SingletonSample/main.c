
#include <stdio.h>
#include "ModelGenerator.h"

int main(int argc, char **argv)
{
    ModelGenerator *pGenerator = CREATE(ModelGenerator)();
    ModelGenerator *pGenerator2 = CREATE(ModelGenerator)();

    if (pGenerator == pGenerator2)
    {
        printf("The two Generator is the same.\n");
    }
    else
    {
        printf("The two Generator is not the same.\n");
    }

    int nModel = -1;
    INVOKE(ModelGenerator)(pGenerator, "GetModel", &(ModelGenerator_GetModel){ &nModel });
    printf("The new model generated is %d.\n", nModel);

    return 0;
}