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


#define OOPCOLLECTION_API __declspec(dllexport)
#include "OopCollection.h"

////List////////////////////////////////////////////////////////////////////////////////////
//

struct List
{
    CHAINDEF;

    int nCount;

    struct ListElem
    {
        struct ListElem *pPrev;
        struct ListElem *pNext;
        void *pData;
    };

    struct _ListHead
    {
        struct ListElem *pHead;
        struct ListElem *pTail;
    } ListHead;
};

static void Append(void *pParams)
{
    List *pThis = ((ParamIn *)pParams)->pInst;
    List_Append *pIn = ((ParamIn *)pParams)->pIn;

    if (pThis->nCount != 0)
    {
        //构造链表元素
        struct ListElem *pToAppend = malloc(sizeof(struct ListElem));
        pToAppend->pData = pIn->pElem;
        pToAppend->pPrev = pThis->ListHead.pTail;
        pToAppend->pNext = NULL;

        pThis->ListHead.pTail->pNext = pToAppend;
        pThis->ListHead.pTail = pToAppend;

        pThis->nCount++;

        return;
    }
    if (pThis->nCount == 0)
    {
        //添加第一个元素

        //构造链表元素
        struct ListElem *pToAppend = malloc(sizeof(struct ListElem));
        pToAppend->pPrev = NULL;
        pToAppend->pNext = NULL;
        pToAppend->pData = pIn->pElem;

        pThis->ListHead.pHead = pToAppend;
        pThis->ListHead.pTail = pToAppend;

        pThis->nCount++;

        return;
    }
}

static void AppendRange(void *pParams)
{
    List *pThis = ((ParamIn *)pParams)->pInst;
    List_AppendRange *pIn = ((ParamIn *)pParams)->pIn;

    //这个地方可以优化
    for (int i = 0; i < pIn->nCount; i++)
    {
        INVOKE(List)(pThis, "Append", &(List_Append){*(pIn->ppElems + i)});
    }
}

static void InsertAt(void *pParams)
{
    List *pThis = ((ParamIn *)pParams)->pInst;
    List_InsertAt *pIn = ((ParamIn *)pParams)->pIn;

    //使pIn->pElem成为链表的第pIn->nIndex个元素，以0为起始索引

    if (pThis->nCount != 0)
    {
        int nIndexTmp = pIn->nIndex;
        if (nIndexTmp < 0)
        {
            nIndexTmp = 0;
        }
        if (nIndexTmp > pThis->nCount)
        {
            nIndexTmp = pThis->nCount;
        }

        if (nIndexTmp != 0 && nIndexTmp != pThis->nCount)
        {
            int nTmp = 0;
            struct ListElem *pItrtr = NULL;
            for (pItrtr = pThis->ListHead.pHead; pItrtr != pThis->ListHead.pTail; pItrtr = pItrtr->pNext)
            {
                if (nTmp++ == pIn->nIndex - 1)
                {
                    break;
                }
            }

            struct ListElem *pToInsert = malloc(sizeof(struct ListElem));
            pToInsert->pPrev = pItrtr;
            pToInsert->pNext = pItrtr->pNext;
            pToInsert->pData = pIn->pElem;

            pItrtr->pNext->pPrev = pToInsert;
            pItrtr->pNext = pToInsert;

            return;
        }

        if (nIndexTmp == 0)
        {
            struct ListElem *pToInsert = malloc(sizeof(struct ListElem));
            pToInsert->pPrev = NULL;
            pToInsert->pNext = pThis->ListHead.pHead;
            pToInsert->pData = pIn->pElem;

            pThis->ListHead.pHead->pPrev = pToInsert;
            pThis->ListHead.pHead = pToInsert;

            pThis->nCount++;

            return;
        }

        if (nIndexTmp == pThis->nCount)
        {
            struct ListElem *pToInsert = malloc(sizeof(struct ListElem));
            pToInsert->pPrev = pThis->ListHead.pTail;
            pToInsert->pNext = NULL;
            pToInsert->pData = pIn->pElem;

            pThis->ListHead.pTail->pNext = pToInsert;
            pThis->ListHead.pTail = pToInsert;

            pThis->nCount++;

            return;
        }

        return;
    }

    if (pThis->nCount == 0)
    {
        INVOKE(List)(pThis, "Append", &(List_Append){pIn->pElem});
    }
}
////删除
//typedef struct { void *pElem; } List_Remove;
//typedef struct { int nIndex; } List_RemoveAt;
//typedef struct { int nIndex; int nCount; } List_RemoveRange;
//typedef struct { bool(*fnProc)(void * /*pElem*/); } List_RemoveBy;
//typedef ParamNull List_RemoveAll;
////查找
//typedef struct { bool *pIsEmpty; } List_IsEmpty;
//typedef struct { void *pElem; bool *pIsContain; } List_Contain;
//typedef struct { int nIndex; } List_FindAt;
//typedef struct { void *pElem; int *pIndex; } List_FirstIndexOf;
//typedef struct { void *pElem; int *pIndex; } List_LastIndexOf;
////遍历
//typedef struct { void(*fnProc)(void * /*pElem*/); } List_Foreach;
//typedef struct { void *pElem; void **ppNext; } List_Next;
//typedef struct { void *pElem; void **ppPrev; } List_Prev;
//typedef struct { int *pCount; } List_Count;

//额外内存删除

bool INVOKE(List)(List* pInst, char* pFuncName, void* pParams)
{
    DOINVOKE(pInst, pFuncName, pParams);
}

void* EXTEND(List)(List* pInst)
{
    DOEXTEND(pInst);
}

void DELETE(List)(List** ppInst)
{
    DODELETE(ppInst, List, Object);
}

List* CREATE(List)()
{
    DOCREATE(pCreate, List, Object, NULL,
        );//方法添加

    pCreate->nCount = 0;
    pCreate->ListHead.pHead = NULL;
    pCreate->ListHead.pTail = NULL;

    return pCreate;
}
