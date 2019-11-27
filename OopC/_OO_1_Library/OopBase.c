
#define OOPBASE_API __declspec(dllexport)
#include "OopBase.h"

#include <string.h>
#include <stdlib.h>


/*****************************************************************/
/************** Data Structure of Inheritance Tree ***************/
/*****************************************************************/

/*
 * type of constructor of class */
typedef void* (*New)();

typedef void (*Clear)(void* pInst);

typedef void (*Method)(void* _pThis, va_list* pvlArgs);
typedef struct MethodRef MethodRef;
struct MethodRef
{
	Method fnMthd;
	char* pMethodName;
};


typedef struct InheritTreeNode InheritTreeNode;
struct InheritTreeNode
{
	InheritTreeNode* pParent;
	size_t szChildNum;
	InheritTreeNode** pChilds;// <== InheritTreeNode* pChilds[k];

	char* pClassName;
	struct __Template* pInst;
	Clear fnClear;
	size_t szMethodNum;
	MethodRef** pMethods;// <== MethodRef* pMethods[k];
};


/*****************************************************************/
/************************* Util Methods **************************/
/*****************************************************************/

static InheritTreeNode* FindNodeByClass(InheritTreeNode* pTree, const char* pClassName)
{
	for (size_t i = 0; i < pTree->szChildNum; i++)
	{
		if (!strcmp(pTree->pChilds[i]->pClassName, pClassName))
		{
			return pTree->pChilds[i];
		}
	}

	for (size_t i = 0; i < pTree->szChildNum; i++)
	{
		InheritTreeNode* pTmp = FindNodeByClass(pTree->pChilds[i], pClassName);
		if (pTmp) { return pTmp; }
	}

	return NULL;
}

static void FindMethodByName(struct __Template** ppInst, MethodRef** ppMthd, InheritTreeNode* pTree, const char* pMethodName)
{
	for (size_t i = 0; i < pTree->szChildNum; i++)
	{
		for (size_t j = 0; j < pTree->szMethodNum; j++)
		{
			if (!strcmp(pTree->pChilds[i]->pMethods[j]->pMethodName, pMethodName))
			{
				*ppInst = pTree->pChilds[i]->pInst;
				*ppMthd = pTree->pChilds[i]->pMethods[j];
				return;
			}
		}
	}

	for (size_t i = 0; i < pTree->szChildNum; i++)
	{
		FindMethodByName(ppInst, ppMthd, pTree->pChilds[i], pMethodName);
		if (*ppInst && *ppMthd) { return; }
	}
}

static void FindMethodByName2(struct __Template** ppInst, MethodRef** ppMthd, InheritTreeNode* pTree, const char* pMethodName)
{
	for (size_t i = 0; i < pTree->szMethodNum; i++)
	{
		if (!strcmp(pTree->pMethods[i]->pMethodName, pMethodName))
		{
			*ppInst = pTree->pInst;
			*ppMthd = pTree->pMethods[i];
			break;
		}
	}

	if (pTree->pParent)
	{
		FindMethodByName2(ppInst, ppMthd, pTree->pParent, pMethodName);
	}
}

static struct __Template* AsRoot(struct __Template* pInst)
{
	InheritTreeNode* pTree = pInst->Ext;
	return pTree->pParent ? AsRoot(pTree->pParent->pInst) : pTree->pInst;
}


/*****************************************************************/
/*************************** Call ********************************/
/*****************************************************************/

static bool DispatchCall(bool bSprOnly, struct __Template* pInst, const char* pMethodName, va_list* pvlArgs)
{
	InheritTreeNode* pTree = pInst->Ext;

	struct __Template* pInstFound = NULL;
	MethodRef* pMthdFound = NULL;
	FindMethodByName(&pInstFound, &pMthdFound, pTree, pMethodName);

	if (bSprOnly)
	{
		if (!pInstFound || !pMthdFound)
		{
			return false;
		}
		else
		{
			pMthdFound->fnMthd(pInstFound, pvlArgs);
			return true;
		}
	}
	else
	{
		for (size_t i = 0; i < pTree->szMethodNum; i++)
		{
			if (!strcmp(pTree->pMethods[i]->pMethodName, pMethodName))
			{
				pInstFound = pTree->pInst;
				pMthdFound = pTree->pMethods[i];
				break;
			}
		}

		if (!pInstFound || !pMthdFound)
		{
			return false;
		}
		else
		{
			if (pTree->pParent)
			{
				FindMethodByName2(&pInstFound, &pMthdFound, pTree->pParent, pMethodName);
			}
			pMthdFound->fnMthd(pInstFound, pvlArgs);
			return true;
		}
	}
}

static bool Call(void* pSelf, const char* pMethodName, ...)
{
	va_list vlArgs;
	va_start(vlArgs, pMethodName);
	bool bRet = DispatchCall(false, pSelf, pMethodName, &vlArgs);
	va_end(vlArgs);
	return bRet;
}

bool __Spr(void* pSelf, const char* pMethodName, ...)
{
	va_list vlArgs;
	va_start(vlArgs, pMethodName);
	bool bRet = DispatchCall(true, pSelf, pMethodName, &vlArgs);
	va_end(vlArgs);
	return bRet;
}


/*****************************************************************/
/*************************** Destroy *****************************/
/*****************************************************************/

static void DestroyTree(InheritTreeNode* pTree)
{
	for (size_t i = 0; i < pTree->szChildNum; i++)
	{
		DestroyTree(pTree->pChilds[i]);
	}

	free(pTree->pChilds);
	free(pTree->pClassName);

	if (pTree->fnClear) { pTree->fnClear(pTree->pInst); }
	free(pTree->pInst->Fld);
	free(pTree->pInst);

	for (size_t i = 0; i < pTree->szMethodNum; i++)
	{
		free(pTree->pMethods[i]->pMethodName);
		free(pTree->pMethods[i]);
	}
	free(pTree->pMethods);
	free(pTree);
}

static void Destroy(void* pInst)
{
	DestroyTree(AsRoot(pInst)->Ext);
}


/*****************************************************************/
/**************************** Construct **************************/
/*****************************************************************/

static void* ConstructMethods(size_t szMthdNum, MethodRef** pMethods, va_list* pvlArgs)
{
	if (szMthdNum)
	{
		for (size_t i = 0; i < szMthdNum; i++)
		{
			pMethods[i] = malloc(sizeof(MethodRef));
			//failed to alloc mem
			if (!pMethods[i]) { for (int j = i - 1; j >= 0; j--) free(pMethods[j]); return NULL; }
		}

		char** pNames = malloc(sizeof(char*) * szMthdNum);
		//failed to alloc mem
		if (!pNames) { for (size_t i = 0; i < szMthdNum; i++) free(pMethods[i]); return NULL; }
		for (size_t i = 0; i < szMthdNum; i++)
		{
			pNames[i] = va_arg(*pvlArgs, char*);
			pMethods[i]->fnMthd = va_arg(*pvlArgs, Method);
		}

		for (size_t i = 0; i < szMthdNum - 1; i++)
		{
			for (size_t j = i + 1; j < szMthdNum; j++)
			{
				//same methods
				if (!strcmp(pNames[i], pNames[j]))
				{
					for (size_t k = 0; k < szMthdNum; k++)
					{
						free(pMethods[i]);
					}
					free(pNames);
					return NULL;
				}
			}
		}

		for (size_t i = 0; i < szMthdNum; i++)
		{
			size_t szTmp = strlen(pNames[i]) + 1;
			pMethods[i]->pMethodName = malloc(szTmp);
			//failed to alloc mem
			if (!pMethods[i]->pMethodName) { for (int j = i - 1; j >= 0; j--) free(pMethods[j]->pMethodName);  free(pNames); for (size_t k = 0; k < szMthdNum; k++) free(pMethods[k]); return NULL; }

			memcpy(pMethods[i]->pMethodName, pNames[i], szTmp);
		}

		free(pNames);

		return pMethods;
	}
	else
	{
		return NULL;
	}
}

static void* ConstructBase(size_t szBaseNum, InheritTreeNode** pChilds, va_list* pvlArgs)
{
	if (szBaseNum)
	{
		New* pfnNew = malloc(sizeof(New) * szBaseNum);
		//failed to alloc mem
		if (!pfnNew) { return NULL; }
		for (size_t i = 0; i < szBaseNum; i++)
		{
			pfnNew[i] = va_arg(*pvlArgs, New);
		}

		for (size_t i = 0; i < szBaseNum - 1; i++)
		{
			for (size_t j = i + 1; j < szBaseNum; j++)
			{
				//same superclass
				if (pfnNew[i] == pfnNew[j]) { free(pfnNew); return NULL; }
			}
		}

		for (size_t i = 0; i < szBaseNum; i++)
		{
			struct __Template* pTmp = pfnNew[i]();
			//failed to create super
			if (!pTmp) { for (int j = i - 1; j >= 0; j--) pChilds[j]->pInst->Destroy(pChilds[j]->pInst); return NULL; }
			pChilds[i] = pTmp->Ext;
		}

		free(pfnNew);

		return pChilds;
	}
	else
	{
		return NULL;
	}
}

void* __New(const char* pClassName, size_t szFld, void(*fnClear)(void*), size_t szMthdNum, size_t szBaseNum, ...)
{
	if (!pClassName || !*pClassName)
	{
		//null class name
		return NULL;
	}

	InheritTreeNode* pTree = NULL;
	{
		pTree = malloc(sizeof(InheritTreeNode));
		//failed to alloc mem
		if (!pTree) { return NULL; }
	}

	pTree->pParent = NULL;

	pTree->pChilds = NULL;
	pTree->szChildNum = 0;
	{
		if (szBaseNum)
		{
			pTree->pChilds = malloc(sizeof(InheritTreeNode*) * szBaseNum);
			//failed to alloc mem
			if (!pTree->pChilds) { free(pTree); return NULL; }
			pTree->szChildNum = szBaseNum;
		}
	}

	//pTree->pClassName = NULL;
	{
		size_t szLen = strlen(pClassName) + 1;
		pTree->pClassName = malloc(szLen);
		//failed to alloc mem
		if (!pTree->pClassName) { free(pTree->pChilds); free(pTree); return NULL; }
		memcpy(pTree->pClassName, pClassName, szLen);
	}

	//pTree->pInst = NULL;
	{
		pTree->pInst = malloc(sizeof(struct __Template));
		//failed to alloc mem
		if (!pTree->pInst) { free(pTree->pClassName); free(pTree->pChilds); free(pTree); return NULL; }

		pTree->pInst->Fld = NULL;
		{
			if (szFld)
			{
				pTree->pInst->Fld = calloc(szFld, 1);
				//failed to alloc mem
				if (!pTree->pInst->Fld) { free(pTree->pInst); free(pTree->pClassName); free(pTree->pChilds); free(pTree); return NULL; }
			}
		}
		pTree->pInst->Ext = pTree;
		pTree->pInst->Call = Call;
		pTree->pInst->Destroy = Destroy;
	}

	pTree->fnClear = fnClear;

	pTree->pMethods = NULL;
	pTree->szMethodNum = 0;
	{
		if (szMthdNum)
		{
			pTree->pMethods = malloc(sizeof(MethodRef*) * szMthdNum);
			//failed to alloc mem
			if (!pTree->pMethods) { free(pTree->pInst->Fld); free(pTree->pInst); free(pTree->pClassName); free(pTree->pChilds); free(pTree); return NULL; }
			pTree->szMethodNum = szMthdNum;
		}
	}

	va_list vlArgs;
	va_start(vlArgs, szBaseNum);
	void* pTmp = NULL;
	pTmp = ConstructMethods(szMthdNum, pTree->pMethods, &vlArgs);
	if (!pTmp && szMthdNum) { free(pTree->pMethods); free(pTree->pInst->Fld); free(pTree->pInst); free(pTree->pClassName); free(pTree->pChilds); free(pTree); va_end(vlArgs); return NULL; }
	pTmp = ConstructBase(szBaseNum, pTree->pChilds, &vlArgs);
	if (!pTmp && szBaseNum) { free(pTree->pMethods); free(pTree->pInst->Fld); free(pTree->pInst); free(pTree->pClassName); free(pTree->pChilds); free(pTree); va_end(vlArgs); return NULL; }
	va_end(vlArgs);

	for (size_t i = 0; i < szBaseNum; i++)
	{
		pTree->pChilds[i]->pParent = pTree;
	}

	return pTree->pInst;
}


/*****************************************************************/
/************************** Conversion ***************************/
/*****************************************************************/

void* __Cvt(void* pSelf, const char* pClassName)
{
	InheritTreeNode* pTree = AsRoot(pSelf)->Ext;
	return  !strcmp(pTree->pClassName, pClassName) ? pTree->pInst : FindNodeByClass(pTree, pClassName)->pInst;
}
