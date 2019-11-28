
#include <assert.h>
#include <stdio.h>
#include <OopUtil.h>

int main(int argc, char **argv)
{
	IniWrapper* pIni = __NEW(IniWrapper);

    bool bRet = false;
	pIni->Call(pIni, "Init", "./my.ini", &bRet);
	pIni->Call(pIni, "WriteIni", "firstsec", NULL, NULL, &bRet);
	pIni->Call(pIni, "WriteIni", "firstsec", "firstkey", "val1", &bRet);
	pIni->Call(pIni, "WriteIni", "firstsec", "firstkey", "val2", &bRet);
    char *pVal = NULL;
	pIni->Call(pIni, "ReadIni", "firstsec", "firstkey", &pVal, &bRet);
	printf("The val of firstkey in firstsec is : %s.\n", pVal);
	pIni->Call(pIni, "Save", NULL, &bRet);
    
    return 0;
}