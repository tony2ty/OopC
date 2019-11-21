
#include <stdio.h>
#include "ModelGenerator.h"

int main(int argc, char **argv)
{
    RLSLOCALMEMBRA();

    ModelGenerator *pGenerator = NEW(ModelGenerator); TORLS(DEL(ModelGenerator), pGenerator);
    ModelGenerator *pGenerator2 = NEW(ModelGenerator); //TORLS(DEL(ModelGenerator), pGenerator2);//两次create均使用的相同单例，因此不能再次标记TORLS，可以取消注释运行试试

    if (pGenerator == pGenerator2)
    {
        printf("The two Generator is the same.\n");
    }
    else
    {
        printf("The two Generator is not the same.\n");
    }

    int nModel = -1;
    pGenerator->Call(pGenerator, "GetModel", &nModel);
    printf("The new model generated is %d.\n", nModel);

    RLSLOCALMEMKET();

    return 0;
}