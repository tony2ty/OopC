
#ifndef OBJECT_H__
#define OBJECT_H__

#include "OopBase.h"

typedef struct Object Object;

OOPLIB_API Object* Make_Object();
OOPLIB_API void  Invoke_Object(Object* pInst, char* pFuncName, void* pParams);
OOPLIB_API void* Extend_Object(Object* pInst);
OOPLIB_API void  Delete_Object(Object** ppInst);

typedef struct { bool* pRet; char* const pInfo; Object* pInst; Object* pToCmpr; } Object_Equal;
typedef struct { bool* pRet; char* const pInfo; Object* pInst; char* const pOut; } Object_ToString;

#endif // !OBJECT_H__
