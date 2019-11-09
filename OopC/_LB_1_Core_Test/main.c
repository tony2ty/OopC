
#include <stdio.h>
#include <OopCore.h>

int main(int argc, char **argv)
{
    RLSLOCALMEMBRA();

    String *pStr = CREATE(String)("You are my friend."); TORLS(DELETE(String), pStr);
    size_t szLenStr = 0;
    INVOKE(String)(pStr, "GetLength", &(String_GetLength){&szLenStr});
    printf("len of pStr: %d\n", szLenStr);

    char *pInner = NULL;
    INVOKE(String)(pStr, "GetInnerPtr", &(String_GetInnerPtr){&pInner});
    pInner[szLenStr - 1] = 's';
    for (size_t i = 0; i < szLenStr; i++)
    {
        printf("%c ", pInner[i]);
    }
    printf("\n");

    RLSLOCALMEMKET();

    return 0;
}