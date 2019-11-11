
#include <assert.h>
#include <stdio.h>
#include <OopUtil.h>

int main(int argc, char **argv)
{
    RLSLOCALMEMBRA();

    FILE *fp = fopen("./my.ini", "w");
    assert(fp != NULL);

    IniWrapper *pIni = CREATE(IniWrapper)(); TORLS(DELETE(IniWrapper), pIni);

    bool bRet = false;
    INVOKE(IniWrapper)(pIni, "Init", &(IniWrapper_Init){"./my.ini", &bRet});
    INVOKE(IniWrapper)(pIni, "WriteIni", &(IniWrapper_WriteIni){"firstsec", NULL, NULL, &bRet});
    INVOKE(IniWrapper)(pIni, "WriteIni", &(IniWrapper_WriteIni){"firstsec", "firstkey", "val1", &bRet});
    INVOKE(IniWrapper)(pIni, "WriteIni", &(IniWrapper_WriteIni){"firstsec", "firstkey", "val2", &bRet});
    char *pVal = NULL;
    INVOKE(IniWrapper)(pIni, "ReadIni", &(IniWrapper_ReadIni){"firstsec", "firstkey", &pVal, &bRet});
    printf("The val of firstkey in firstsec is : %s.\n", pVal);
    INVOKE(IniWrapper)(pIni, "Save", &(IniWrapper_Save){NULL, &bRet});

    fclose(fp);

    RLSLOCALMEMKET();
    
    return 0;
}