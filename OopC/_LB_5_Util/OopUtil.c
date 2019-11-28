//MIT License
//
//Copyright(c) 2019 Goodman Tao
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.


#define OOPUTIL_API __declspec(dllexport)
#include "OopUtil.h"

/**************************************************/
/****************** IniWrapper ********************/
/**************************************************/

#include "iniparser.h"

typedef struct
{
    char* pIniFileName;

    dictionary* pDict;
} IniWrapper_Fld;

////////////////////////////////////////////////////////////////////
//

static void IniWrapper_Init(void *_pThis, va_list* pvlArgs)
{
	IniWrapper* pThis = _pThis;
    IniWrapper_Fld *pFld = pThis->Fld;

	const char* pIniFileName = va_arg(*pvlArgs, const char*);
	bool* pRet = va_arg(*pvlArgs, bool*);

    size_t szTmp = strlen(pIniFileName);
    pFld->pIniFileName = malloc(szTmp + 1);
    if (pFld->pIniFileName == NULL)
    {
        *pRet = false;
        return;
    }

    memcpy(pFld->pIniFileName, pIniFileName, szTmp + 1);
    pFld->pDict = iniparser_load(pIniFileName);

    *pRet = pFld->pDict != NULL;
}

static void IniWrapper_WriteIni(void *_pThis, va_list* pvlArgs)
{
	IniWrapper* pThis = _pThis;
    IniWrapper_Fld *pFld = pThis->Fld;

	const char* pSection = va_arg(*pvlArgs, const char*);
	const char* pKey = va_arg(*pvlArgs, const char*);
	const char* pVal = va_arg(*pvlArgs, const char*);
	bool* pRet = va_arg(*pvlArgs, bool*);

    //write value
    if (pSection != NULL && pKey != NULL)
    {
        size_t szLenKey = 0;
        char* pBufEntry = NULL;

        {
            szLenKey = strlen(pSection) + 1/* : */ + strlen(pKey) + 1/* \0 */;
            pBufEntry = malloc(szLenKey);
        }
        if (pBufEntry == NULL)
        {
            *pRet = false;
            return;
        }
        memset(pBufEntry, 0, szLenKey);
        sprintf(pBufEntry, "%s:%s", pSection, pKey);

        *pRet = 0 == iniparser_set(pFld->pDict, pBufEntry, pVal);
        free(pBufEntry);

        return;
    }

    //new section
    if (pSection != NULL && pKey == NULL)
    {
        *pRet = 0 == iniparser_set(pFld->pDict, pSection, NULL);
        return;
    }

    *pRet = false;
}

static void IniWrapper_ReadIni(void *_pThis, va_list* pvlArgs)
{
	IniWrapper* pThis = _pThis;
    IniWrapper_Fld *pFld = pThis->Fld;

	const char* pSection = va_arg(*pvlArgs, const char*);
	const char* pKey = va_arg(*pvlArgs, const char*);
	const char** ppRetVal = va_arg(*pvlArgs, const char**);
	bool* pRet = va_arg(*pvlArgs, bool*);

    size_t szLenKey = 0;
    char* pBufKey = NULL;

    {
        szLenKey = strlen(pSection) + 1/* : */ + strlen(pKey) + 1/* \0 */;
        pBufKey = malloc(szLenKey);
    }
    if (pBufKey == NULL)
    {
        //failed to alloc mem
        *pRet = false;
        return;
    }
    memset(pBufKey, 0, szLenKey);
    sprintf(pBufKey, "%s:%s", pSection, pKey);

    *ppRetVal = iniparser_getstring(pFld->pDict, pBufKey, "");
    free(pBufKey);

    *pRet = true;
}

static void IniWrapper_Save(void *_pThis, va_list* pvlArgs)
{
	IniWrapper* pThis = _pThis;
    IniWrapper_Fld *pFld = pThis->Fld;

	const char* pSaveAs = va_arg(*pvlArgs, const char*);
	bool* pRet = va_arg(*pvlArgs, bool*);

    const char* pFileName = pFld->pIniFileName;
    if (pSaveAs != NULL)
    {
        pFileName = pSaveAs;
    }
    if (pFileName == NULL)
    {
        *pRet = false;
        return;
    }

    FILE* fp = fopen(pFileName, "w");
    if (fp == NULL)
    {
        *pRet = false;
        return;
    }

    iniparser_dump_ini(pFld->pDict, fp);
    fclose(fp);

    *pRet = true;
}

////////////////////////////////////////////////////////////////////
//

static void  IniWrapper_Clear(void* pParams)
{
    IniWrapper* pSelf = pParams;
    IniWrapper_Fld *pFld = pSelf->Fld;

    free(pFld->pIniFileName);

    iniparser_freedict(pFld->pDict);
}

__CONSTRUCTOR(IniWrapper)
{
    return __New(__TYPE(IniWrapper), sizeof(IniWrapper_Fld), IniWrapper_Clear, 4, 0,
        //__METHOD(IniWrapper_Init),
        //__METHOD(IniWrapper_WriteIni),
        //__METHOD(IniWrapper_ReadIni),
        //__METHOD(IniWrapper_Save));
        "Init", IniWrapper_Init,
        "WriteIni", IniWrapper_WriteIni,
        "ReadIni", IniWrapper_ReadIni,
        "Save", IniWrapper_Save);
}

