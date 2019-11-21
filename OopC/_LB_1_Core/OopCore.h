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

/*************************************************/
/***************** String ************************/
/*************************************************/

CLASSEXP(OOPCORE_API, String, Object);

//1.字符遍历
/*
 * Example:
 *
 * String *pStr = CREATE(String)("It's amazing.");
 * char *pInner = NULL;
 * INVOKE(String)(pStr, "GetInnerPtr", &(String_GetInnerPtr){&pInner}); */
typedef struct { char **ppInnerPtr; }
               String_GetInnerPtr;
//2.比较
//3.索引
//4.长度
typedef struct { size_t *pszLength; }
               String_GetLength;
//5.连接
//6.复制
//7.格式化
//8.空判断
//9.join
//10.startwith
//11.endwith
//12.查找
//13.插入
//14.删除
//15.替换
//16.分割
//17.字串
//18.大小写
//19.缩空

typedef struct { size_t szCapacity; }
               String_SetCapacity;
typedef struct { size_t *pszCapacity; }
               String_GetCapacity;
typedef struct { size_t *pszAvailCapacity; }
               String_GetAvailCapacity;
/* 
 * Grow String inst to have the specified length.
 * The new growed bytes will be set to zero.
 * if the specified length is smaller than
 * the current length, no operation is performed. */
typedef struct { size_t szByteToIncrease; }
               String_IncreaseCapacityWithInit;
/*
 * Set length of the String inst to that as obtained with strlen(), so
 * considering as content only up to the first null term character.
 *
 * This function is useful when the String inst is hacked manually in some
 * way, like in the following example:
 *
 * String *pStr = CREATE(String)("foobar");
 * char *pInner = NULL;
 * INVOKE(String)(pStr, "InnerPtr", &(String_InnerPtr){&pInner});
 * pInner[2] = '\0';
 * INVOKE(String)(pStr, "UpdateLen", NULL);
 * INVOKE(String)(pStr, "ToString", NULL);
 *
 * The output will be "2", but if we comment out the call to sdsupdatelen()
 * the output will be "6" as the string was modified but the logical length
 * remains 6 bytes. */
typedef ParamNull
               String_TrimSizeToLen;
typedef struct { size_t szIncrease; }
               String_IncreaseLen;
typedef struct { size_t szToSet; }
               String_SetStrLen;
/*
 * The input ref should be null,
 * or this may cause mem leak */
typedef struct { String **ppDuplicated; }
               String_Duplicate;
/*
 * Append the specified binary-safe string pointed
 * by 'pData' of 'szLen' bytes to the end of String inst. */
typedef struct { const void *pData; size_t szLen; }
               String_CatenateByLen;
/* 
 * Append the specified null termianted C string
 * to the String inst. */
typedef struct { const char *pData; }
               String_Catenate;
/*
 * Append the specified String inst to
 * the existing inst. */
typedef struct { String *pToCatenate; }
               String_CatenateAnotherInst;
/* 
 * Destructively modify the String inst to
 * hold the specified binary safe string pointed
 * by 'pData' of length 'szLen' bytes. */
typedef struct { const char *pData; size_t szLen; }
               String_CopyByLen;
/* 
 * Like CopyByLen() but 'pData' must be a null-termined string
 * so that the length of the string is obtained with strlen(). */
typedef struct { const char *pData; }
               String_Copy;
/* 
 * Remove the part of the string from left and from right composed just of
 * contiguous characters found in 'cset', that is a null terminted C string.
 *
 * Example:
 *
 * String *pStr = CREATE(String)("AA...AA.a.aa.aHelloWorld     :::");
 * INVOKE(String)(pStr, "Trim", &(String_Trim){ "Aa. :" });
 * INVOKE(String)(pStr, "ToString", NULL);
 *
 * Output will be just "HelloWorld". */
typedef struct { const char *pCharSet; }
               String_Trim;
/* 
 * Turn the String into a smaller (or equal) string containing only the
 * substring specified by the 'nStartIndex' and 'nEndIndex' indexes.
 *
 * start and end can be negative, where -1 means the last character of the
 * string, -2 the penultimate character, and so forth.
 *
 * The interval is inclusive, so the start and end characters will be part
 * of the resulting string.
 *
 * The string is modified in-place.
 *
 * Example:
 *
 * String *pStr = CREATE(String)("Hello World");
 * INVOKE(String)(pStr, "GetRange", &(String_GetRange){1, -1});
 * INVOKE(String)(pStr, "ToString", NULL);
 *
 * Output will be "ello World"; */
typedef struct { int nStartIndex; int nEndIndex; }
               String_GetRange;
/*
 * Modify the String inst in-place to make it empty (zero length).
 * However all the existing buffer is not discarded but set as free space
 * so that next append operations will not require allocations up to the
 * number of bytes previously available. */
typedef ParamNull
               String_Empty;
/* 
 * Compare two String insts with memcmp().
 *
 * Return value:
 *
 *     positive if this > pToCmpr.
 *     negative if this < pToCmpr.
 *     0 if the both are exactly the same binary string.
 *
 * If two String insts share exactly the same prefix, but one of the two has
 * additional characters, the longer string is considered to be greater than
 * the smaller one. */
typedef struct { int *pRet; String *pToCmpr; }
               String_Compare;


////List////////////////////////////////////////////////////////////////////////////////////
//

//typedef struct List List;
//
//OOPCORE_API List* CREATE(List)();
//OOPCORE_API bool  INVOKE(List)(List*   pInst, char* pFuncName, void* pParams);
//OOPCORE_API void* EXTEND(List)(List*   pInst);
//OOPCORE_API void  DELETE(List)(List** ppInst);
//
////添加，添加时，要么添加值类型，要么添加指针地址
//typedef struct { void *pElem; } List_Append;
//typedef struct { void **ppElems; int nCount; } List_AppendRange;
//typedef struct { void *pElem; int nIndex; } List_InsertAt;
////删除
//typedef struct { void *pElem; void **ppRemoved; } List_Remove;
//typedef struct { int nIndex; void **ppRemoved; } List_RemoveAt;
//typedef struct { int nIndex; int nCount; void ***ppRemovedArr; } List_RemoveRange;
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

#endif // !OOPCORE_H__

