
//实现文件.c包含头文件.h
#define OOPLIB_API __declspec(dllexport)
#include "Object.h"

//继承，包含头文件

//实现所需头文件
#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////////////
//

struct Object
{
	InstanceChain* pChain;
};

static void Equal(void* pParams)
{
	Object_Equal* pIn = pParams;
	*pIn->pRet = pIn->pInst == pIn->pToCmpr;
}

static void ToString(void* pParams)
{
	Object_ToString* pIn = pParams;

	*pIn->pRet = true;
	printf("%p", pIn->pInst);
}

//////////////////////////////////////////////////////////////////////////////////////
//

void  Invoke_Object(Object* pInst, char* pFuncName, void* pParams)
{
	Invoke(pInst->pChain, pInst, pFuncName, pParams);
}

void* Extend_Object(Object* pInst)
{
	return pInst->pChain;
}

void  Delete_Object(Object** ppInst)
{
	//释放当前类数据域中动态分配的内存

	Delete((*ppInst)->pChain);
}

Object* Make_Object()
{
	Object* pMake = NULL;

	MethodRing* pMethods = NULL;
	pMake = malloc(sizeof(Object));
	pMethods = GenerateMethodRing();
	pMethods =
		InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(Equal, "Equal"))
		->InsertMethod(&(MethodUtil) { pMethods, InsertMethod }, GenerateMethod(ToString, "ToString"))
		->pRing;
	pMake->pChain = InsertInstance(GenerateInstanceChain(), GenerateInstance(pMake, "Object", pMethods));

	return pMake;
}
