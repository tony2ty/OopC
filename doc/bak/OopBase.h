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


#ifndef OOPBASE_H__
#define OOPBASE_H__

#ifdef OOPLIB_API
#else
	#define OOPLIB_API __declspec(dllimport)
#endif // !OOPLIB_API


#include <stdbool.h>
#include <stdarg.h>
#include <malloc.h>

////OopBase//////////////////////////////////////////////////////////////////////////////
//

//------���������API-------------------------------------------------------------------------------------------------------------//

#define CREATE(type) Create_ ## type

#define INVOKE(type) Invoke_ ## type

#define EXTEND(type) Extend_ ## type

#define DELETE(type) Delete_ ## type

#define DOINVOKE(pInst, pFuncName, pParams)/*����pInst����ΪpFuncName�ķ���������ΪpParams����Ҫ���ϵ��ã�DOINVOKE((...some expr...), ..., ...)*/ \
                return Invoke(pInst->pChain, pInst, pFuncName, &(ParamIn){ ConvertByFunc(pInst->pChain, pInst, pFuncName), pParams })

#define DOEXTEND(pInst) \
                return pInst->pChain

#define DODELETE(pInst, theclass, superclass) \
                superclass *pSuper = SWITCH(pInst, theclass, superclass); DELETE(superclass)(pSuper)

#define DOCREATE(pInst, theclass, superclass, pRlsRef, ...)/*����ʵ������������ʼ��ʵ����������*/ \
                theclass *pInst = malloc(sizeof(theclass));                 \
                if (!pInst) { return NULL; }                                \
                void *pMethods = GenerateMethodRing();                      \
                if (!pMethods) { return NULL; };                            \
                __VA_ARGS__                                                 \
                pInst->pChain = InsertInstance(                             \
                    EXTEND(superclass)(CREATE(superclass)()),               \
                    GenerateInstance(pInst, #theclass, pRlsRef, pMethods))  \

#define CLASSDEF(theclass, superclass, ...)/*�ඨ��꣬����ʱ�������������������û��Ĭ���޲ι��캯����������֮������*/ \
	            typedef struct theclass theclass;                                            \
	            theclass* CREATE(theclass)(__VA_ARGS__);                                     \
	            bool      INVOKE(theclass)(theclass* pInst, char* pFuncName, void* pParams); \
	            void*     EXTEND(theclass)(theclass* pInst);                                 \
	            void      DELETE(theclass)(theclass* pInst)                                  \

//-----ʵ����������һЩ��Ҫ�ĺ궨��--------------------------------------------------------------------------------------------------------------//

#define      ABSTRACT/*���󷽷�ע�ͷ���*/

#define      CHAINDEF/*��׼ʵ��������*/ \
                     void *pChain

#define        METHOD(name)/*��ӷ���*/ \
                     InsertMethod(pMethods, 1, GenerateMethod(name, #name));

#define       AMETHOD(name)/*��ӳ��󷽷���Aǰ׺��ʾAbstract*/ \
                     InsertMethod(pMethods, 1, GenerateMethod(NULL, #name));

#define        SWITCH(pInst, theclass, superclass)/*��ʵ��ת����ָ�������͡���Ҫ���ϵ��ã�SWITCH((...some expr...), ..., ...)*/ \
                     ConvertByType(EXTEND(theclass)(pInst), pInst, #superclass)

#define DOINVOKESUPER(pInst, pFuncName, ...)/*����pInst�ĸ���pFuncName��������Ҫ���ϵ��ã�DOINVOKESUPER((...some expr...), ..., ...)*/ \
                     InvokeSuper(pInst->pChain, pInst, pFuncName, &(ParamIn){ ConvertByFuncInherited(pInst->pChain, pInst, pFuncName), __VA_ARGS__ })

//��Ա�����Ŀղ����ṹ��
typedef struct { void* pNull; } ParamNull;
//��Ա���������
typedef struct { void* pInst; void* pIn; } ParamIn;

//-----������Ϣ--------------------------------------------------------------------------------------------------------------//

//���ú���ִ��ʧ��ʱ����ȡʧ�ܵ���Ϣ
OOPLIB_API char *GetErrorInfo(char* pMemIn);

//-----�ڴ��ͷ�--------------------------------------------------------------------------------------------------------------//

#define RLSLOCALMEMBRA()/*�ֲ���̬�ڴ��ͷŻ�������ʼ�ꡣRelease local memory bra*/ \
                      void *pLocalMemRefList = GenerateReleaserRefList()

#define RLSLOCALMEMKET()/*�ֲ���̬�ڴ��ͷŻ����������ꡣRelease local memory ket*/ \
                      CallReleaser(pLocalMemRefList)

#define          TORLS(fnRelease, pToClear)/*�ֲ���̬�ڴ��ͷű�ǺꡣTo Release*/ \
                      InsertReleaserRef(pLocalMemRefList, GenerateReleaserRef(fnRelease, pToClear))

OOPLIB_API void* GenerateReleaserRef(void* pfnRelease, void* pToClear);
OOPLIB_API void* GenerateReleaserRefList();
OOPLIB_API void*   InsertReleaserRef(void *pVdList, void *pVdRlsRef);
OOPLIB_API void      CallReleaser(void *pVdList);


//-----ʵ����������--------------------------------------------------------------------------------------------------------------//

OOPLIB_API void* GenerateMethod(void(*pAddr)(void *), char* pName);
OOPLIB_API void* GenerateMethodRing();
OOPLIB_API void*   InsertMethod(void *pVdMethods, int nMethodNum, ...);

//-----ʵ������ʵ��--------------------------------------------------------------------------------------------------------------//

OOPLIB_API void* GenerateInstance(void* pFields, char* pName, void *pRlsRef, void* pVdMethods);
OOPLIB_API void* GenerateInstanceChain();
OOPLIB_API void*   InsertInstance(void* pVdChain, void* pVdInstance);

//-----֧���������Ĺ���--------------------------------------------------------------------------------------------------------------//

//�ú�����Ŀ������ͨ��ʵ��ָ��pInst������ΪpFuncName�ĺ���������ΪpParams��
//��ָ�����Ƶĺ���������pInstʵ���Ӹ����м̳еõ��ģ�
//�����Ҫʵ���������Բ��Һ�����
//��ʵ�����в��ҵ�ʱ���������²��ң�Ȼ�����ϲ���
OOPLIB_API bool  Invoke                (void* pVdChain, void* pInst, char* pFuncName, void* pParams);

//�ú�����Ŀ������ͨ��ʵ��ָ��pInst������ΪpFuncName�ĺ���������ΪpParams��
//ʵ����pChain���ڲ��Һ�����
//����ʱ��ֻ�����ϲ���
OOPLIB_API bool  InvokeSuper           (void* pVdChain, void* pInst, char* pFuncName, void* pParams);

//�ú�����ʵ����pChain�в��Ҹ�����ʵ��ָ��pInst��Ȼ�����ϲ��ң�ֱ���ҵ��������͵�ʵ��Ϊֹ
OOPLIB_API void* ConvertByType         (void* pVdChain, void* pInst, char* pBaseType);

//���ݺ������ƣ�ȷ��ʵ�������ĸ�ʵ�����ᱻ���ã��������²��ң�Ȼ�����ϲ���
OOPLIB_API void* ConvertByFunc         (void* pVdChain, void* pInst, char* pFuncName);

//���ݺ������ƣ�ȷ��ʵ�������ĸ�ʵ�����ᱻ���ã������ϲ���
OOPLIB_API void* ConvertByFuncInherited(void* pVdChain, void* pInst, char* pFuncName);

////Object//////////////////////////////////////////////////////////////////////////////
//

typedef struct Object Object;

OOPLIB_API Object* CREATE(Object)();
OOPLIB_API bool    INVOKE(Object)(Object* pInst, char* pFuncName, void* pParams);
OOPLIB_API void*   EXTEND(Object)(Object* pInst);
OOPLIB_API void    DELETE(Object)(Object* pInst);

typedef struct { bool* pRet; void* pToCmpr; } Object_Equal;
typedef ParamNull Object_ToString;

#endif // !OOPBASE_H__


