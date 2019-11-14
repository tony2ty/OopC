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

struct IniWrapper
{
    CHAINDEF;

    char* pIniFileName;

    dictionary* pDict;
};

////////////////////////////////////////////////////////////////////
//

static void Init(void* pParams)
{
    IniWrapper* pThis = ((ParamIn*)pParams)->pInst;
    IniWrapper_Init* pIn = ((ParamIn*)pParams)->pIn;

    size_t szTmp = strlen(pIn->pIniFileName);
    pThis->pIniFileName = malloc(szTmp + 1);
    if (pThis->pIniFileName == NULL)
    {
        *pIn->pRet = false;
        return;
    }

    memcpy(pThis->pIniFileName, pIn->pIniFileName, szTmp + 1);
    pThis->pDict = iniparser_load(pIn->pIniFileName);

    *pIn->pRet = pThis->pDict != NULL;
}

static void WriteIni(void* pParams)
{
    IniWrapper* pThis = ((ParamIn*)pParams)->pInst;
    IniWrapper_WriteIni* pIn = ((ParamIn*)pParams)->pIn;

    //write value
    if (pIn->pSection != NULL && pIn->pKey != NULL)
    {
        size_t szLenKey = 0;
        char* pBufEntry = NULL;

        {
            szLenKey = strlen(pIn->pSection) + 1/* : */ + strlen(pIn->pKey) + 1/* \0 */;
            pBufEntry = malloc(szLenKey);
        }
        if (pBufEntry == NULL)
        {
            *pIn->pRet = false;
            return;
        }
        memset(pBufEntry, 0, szLenKey);
        sprintf(pBufEntry, "%s:%s", pIn->pSection, pIn->pKey);

        *pIn->pRet = 0 == iniparser_set(pThis->pDict, pBufEntry, pIn->pValue);
        free(pBufEntry);

        return;
    }

    //new section
    if (pIn->pSection != NULL && pIn->pKey == NULL)
    {
        *pIn->pRet = 0 == iniparser_set(pThis->pDict, pIn->pSection, NULL);
        return;
    }

    *pIn->pRet = false;
}

static void ReadIni(void* pParams)
{
    IniWrapper* pThis = ((ParamIn*)pParams)->pInst;
    IniWrapper_ReadIni* pIn = ((ParamIn*)pParams)->pIn;

    size_t szLenKey = 0;
    char* pBufKey = NULL;

    {
        szLenKey = strlen(pIn->pSection) + 1/* : */ + strlen(pIn->pKey) + 1/* \0 */;
        pBufKey = malloc(szLenKey);
    }
    if (pBufKey == NULL)
    {
        //failed to alloc mem
        *pIn->pRet = false;
        return;
    }
    memset(pBufKey, 0, szLenKey);
    sprintf(pBufKey, "%s:%s", pIn->pSection, pIn->pKey);

    *pIn->ppRetVal = iniparser_getstring(pThis->pDict, pBufKey, "");
    free(pBufKey);

    *pIn->pRet = true;
}

static void Save(void* pParams)
{
    IniWrapper* pThis = ((ParamIn*)pParams)->pInst;
    IniWrapper_Save* pIn = ((ParamIn*)pParams)->pIn;

    const char* pFileName = pThis->pIniFileName;
    if (pIn->pSaveAs != NULL)
    {
        pFileName = pIn->pSaveAs;
    }
    if (pFileName == NULL)
    {
        *pIn->pRet = false;
        return;
    }

    FILE* fp = fopen(pFileName, "w");
    if (fp == NULL)
    {
        *pIn->pRet = false;
        return;
    }

    iniparser_dump_ini(pThis->pDict, fp);
    fclose(fp);

    *pIn->pRet = true;
}

static void Clear(void* pParams)
{
    IniWrapper* pInst = pParams;

    free(pInst->pIniFileName);

    iniparser_freedict(pInst->pDict);
}

bool INVOKE(IniWrapper)(IniWrapper* pInst, char* pFuncName, void* pParams)
{
    DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(IniWrapper)(IniWrapper* pInst)
{
    DOEXTEND(pInst);
}

void DELETE(IniWrapper)(IniWrapper* pInst)
{
    DODELETE(pInst, IniWrapper, Object);
}

IniWrapper* CREATE(IniWrapper)()
{
    DOCREATE(pCreate, IniWrapper, Object, CLASSEXTRAMEM(Clear, pCreate),
        METHOD(pCreate, Init)
        METHOD(pCreate, WriteIni)
        METHOD(pCreate, ReadIni)
        METHOD(pCreate, Save));

    pCreate->pIniFileName = NULL;
    pCreate->pDict = NULL;

    return pCreate;
}
