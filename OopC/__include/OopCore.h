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


#ifndef OOPCORE_H__
#define OOPCORE_H__

#ifdef OOPCORE_API
#else
    #define OOPCORE_API __declspec(dllimport)
#endif // OOPCORE_API

#include <OopBase.h>

////String////////////////////////////////////////////////////////////////////////////////////
//

////List////////////////////////////////////////////////////////////////////////////////////
//

typedef struct List List;

OOPCORE_API List* CREATE(List)();
OOPCORE_API bool  INVOKE(List)(List*   pInst, char* pFuncName, void* pParams);
OOPCORE_API void* EXTEND(List)(List*   pInst);
OOPCORE_API void  DELETE(List)(List** ppInst);

//添加，添加时，要么添加值类型，要么添加指针地址
typedef struct { void *pElem; } List_Append;
typedef struct { void **ppElems; int nCount; } List_AppendRange;
typedef struct { void *pElem; int nIndex; } List_InsertAt;
//删除
typedef struct { void *pElem; void **ppRemoved; } List_Remove;
typedef struct { int nIndex; void **ppRemoved; } List_RemoveAt;
typedef struct { int nIndex; int nCount; void ***ppRemovedArr; } List_RemoveRange;
typedef struct { bool(*fnProc)(void * /*pElem*/); } List_RemoveBy;
typedef ParamNull List_RemoveAll;
//查找
typedef struct { bool *pIsEmpty; } List_IsEmpty;
typedef struct { void *pElem; bool *pIsContain; } List_Contain;
typedef struct { int nIndex; } List_FindAt;
typedef struct { void *pElem; int *pIndex; } List_FirstIndexOf;
typedef struct { void *pElem; int *pIndex; } List_LastIndexOf;
//遍历
typedef struct { void(*fnProc)(void * /*pElem*/); } List_Foreach;
typedef struct { void *pElem; void **ppNext; } List_Next;
typedef struct { void *pElem; void **ppPrev; } List_Prev;
typedef struct { int *pCount; } List_Count;

#endif // !OOPCORE_H__

