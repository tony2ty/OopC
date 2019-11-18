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

struct IniWrapper_Fld
{
	CHAINDECLARE;

    char* pIniFileName;

    dictionary* pDict;
};

////////////////////////////////////////////////////////////////////
//

static void Init(ParamIn* pParams)
{
	IniWrapper* pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	const char* pIniFileName = va_arg(vlArgs, const char*);
	bool* pRet = va_arg(vlArgs, bool*);

    size_t szTmp = strlen(pIniFileName);
    pThis->pFld->pIniFileName = malloc(szTmp + 1);
    if (pThis->pFld->pIniFileName == NULL)
    {
        *pRet = false;
        return;
    }

    memcpy(pThis->pFld->pIniFileName, pIniFileName, szTmp + 1);
    pThis->pFld->pDict = iniparser_load(pIniFileName);

    *pRet = pThis->pFld->pDict != NULL;
}

static void WriteIni(ParamIn* pParams)
{
	IniWrapper* pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	const char* pSection = va_arg(vlArgs, const char*);
	const char* pKey = va_arg(vlArgs, const char*);
	const char* pVal = va_arg(vlArgs, const char*);
	bool* pRet = va_arg(vlArgs, bool*);

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

        *pRet = 0 == iniparser_set(pThis->pFld->pDict, pBufEntry, pVal);
        free(pBufEntry);

        return;
    }

    //new section
    if (pSection != NULL && pKey == NULL)
    {
        *pRet = 0 == iniparser_set(pThis->pFld->pDict, pSection, NULL);
        return;
    }

    *pRet = false;
}

static void ReadIni(ParamIn* pParams)
{
	IniWrapper* pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	const char* pSection = va_arg(vlArgs, const char*);
	const char* pKey = va_arg(vlArgs, const char*);
	const char** ppRetVal = va_arg(vlArgs, const char**);
	bool* pRet = va_arg(vlArgs, bool*);

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

    *ppRetVal = iniparser_getstring(pThis->pFld->pDict, pBufKey, "");
    free(pBufKey);

    *pRet = true;
}

static void Save(ParamIn* pParams)
{
	IniWrapper* pThis = pParams->pThis;
	va_list vlArgs = pParams->vlArgs;

	const char* pSaveAs = va_arg(vlArgs, const char*);
	bool* pRet = va_arg(vlArgs, bool*);

    const char* pFileName = pThis->pFld->pIniFileName;
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

    iniparser_dump_ini(pThis->pFld->pDict, fp);
    fclose(fp);

    *pRet = true;
}

////////////////////////////////////////////////////////////////////
//

static void  __CLEAR (IniWrapper)(void* pParams)
{
    IniWrapper* pInst = pParams;

    free(pInst->pFld->pIniFileName);

    iniparser_freedict(pInst->pFld->pDict);
}

static bool  __CALL  (IniWrapper)(IniWrapper* pSelf, const char* pMethodName, ...)
{
	DOCALL(pSelf, pMethodName);
}

static void* __EXTEND(IniWrapper)(IniWrapper* pSelf)
{
	DOEXTEND(pSelf);
}

       void  __DEL   (IniWrapper)(IniWrapper* pSelf)
{
	DODEL(pSelf, Object);
}

IniWrapper*  __NEW   (IniWrapper)()
{
	DONEW(pNew, IniWrapper, Object, __CLEAR(IniWrapper),
		METHOD(Init)
		METHOD(WriteIni)
		METHOD(ReadIni)
		METHOD(Save));

	return pNew;
}

