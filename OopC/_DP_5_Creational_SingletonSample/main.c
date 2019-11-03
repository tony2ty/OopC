
#include <stdio.h>
#include "ModelGenerator.h"

int main(int argc, char **argv)
{
    RLSLOCALMEMBRA();

    ModelGenerator *pGenerator = CREATE(ModelGenerator)(); TORLS(DELETE(ModelGenerator), pGenerator);
    ModelGenerator *pGenerator2 = CREATE(ModelGenerator)(); //TORLS(DELETE(ModelGenerator), pGenerator2);//����create��ʹ�õ���ͬ��������˲����ٴα��TORLS������ȡ��ע����������

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

    RLSLOCALMEMKET();

    return 0;
}