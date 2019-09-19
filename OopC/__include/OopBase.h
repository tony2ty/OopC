
#ifndef OOPBASE_H__
#define OOPBASE_H__

#ifdef OOPLIB_API
#else
	#define OOPLIB_API __declspec(dllimport)
#endif // !OOPLIB_API


#include <stdbool.h>
#include <stdarg.h>

////OopBase//////////////////////////////////////////////////////////////////////////////
//

//��ȡ���������ַ���
#define   TYPE(type) #type

//���캯��������
#define CREATE(type) Create_ ## type   
//ʵ���������ð�����
#define INVOKE(type) Invoke_ ## type   
//�̳а�����
#define EXTEND(type) Extend_ ## type   
//����������
#define DELETE(type) Delete_ ## type   

//����ת�������꣬�ú꽫ʵ���ӵ�ǰ������ת����ָ��������
//��ò�Ҫ���ϵ��ã�SWITCH((...some expr...), ..., ...)
#define SWITCH(pInst, theclass, superclass) AsBaseByType(EXTEND(theclass)(pInst), pInst, TYPE(superclass))

//���øú�ʵ�������Ĺ��ܣ�������������pParams��ͨ��ʵ��pInst������ΪpFuncName�ķ���
//��ò�Ҫ���ϵ��ã�DOINVOKE((...some expr...), ..., ...)
#define DOINVOKE(pInst, pFuncName, pParams) Invoke(pInst->pChain, pInst, pFuncName, &(ParamIn){ AsBaseByFunc(pInst->pChain, pInst, pFuncName), pParams })

//���øú�ʵ�������Ĺ��ܣ�������������pParams(...)��ͨ��ʵ��pInst������ΪpFuncName�ķ��������õ�ʱ��ֻ�����ʵ�����ϲ���Ҳ����ֻ����ü̳еõ��ķ���
//��ò�Ҫ���ϵ��ã�DOINVOKESUPER((...some expr...), ..., ...)
#define DOINVOKESUPER(pInst, pFuncName, ...) InvokeSuper(pInst->pChain, pInst, pFuncName, &(ParamIn){ AsBaseByFuncUpward(pInst->pChain, pInst, pFuncName), __VA_ARGS__ })

//�ඨ������꣬
//����ʱ�������������������û��Ĭ���޲ι��캯������
//��֮��û�и������������������Ĭ�Ϲ��캯������
#define CLASSDEF(theclass, ...)                                                    \
	typedef struct theclass theclass;                                              \
	theclass* CREATE(theclass)(__VA_ARGS__);                                       \
	void      INVOKE(theclass)(theclass*   pInst, char* pFuncName, void* pParams); \
	void*     EXTEND(theclass)(theclass*   pInst);                                 \
	void      DELETE(theclass)(theclass** ppInst);                                 \

//��׼ʵ��������
#define CHAINDEF InstanceChain *pChain 

//��Ա������׼����
typedef void (*Transit)(void*);
//��Ա��������νṹ�壬
//����ת�����ã�
typedef struct { void* pInst; void* pIn; } ParamIn;
//��Ա�����Ŀղ����ṹ�壬
//�����ⲿ����
typedef struct { void* pVd; } ParamNull;

//////////////////////////////////////////////////////////////////////////////////
//

typedef void (*ExtraMemClear)(void*);
typedef struct ExtraMemRef ExtraMemRef;

OOPLIB_API ExtraMemRef* GenerateExtraMemRef(ExtraMemClear fnExec, void* pToClear);

//////////////////////////////////////////////////////////////////////////////////
//

typedef struct Method Method;
typedef struct MethodRing MethodRing;

OOPLIB_API Method*     GenerateMethod(Transit pAddr, char* pName);
OOPLIB_API MethodRing* GenerateMethodRing();
OOPLIB_API MethodRing*   InsertMethod(MethodRing *pMethods, int nMethodNum, ...);

//////////////////////////////////////////////////////////////////////////////////
//

typedef struct Instance Instance;
typedef struct InstanceChain InstanceChain;

OOPLIB_API Instance*      GenerateInstance(void* pFields, char* pName, ExtraMemRef *pExtRef, MethodRing* pMethods);
OOPLIB_API InstanceChain* GenerateInstanceChain();
OOPLIB_API InstanceChain*   InsertInstance(InstanceChain* pChain, Instance* pInstance);

//////////////////////////////////////////////////////////////////////////////////
//

//�ú�����Ŀ������ͨ��ʵ��ָ��pInst������ΪpFuncName�ĺ���������ΪpParams��
//��ָ�����Ƶĺ���������pInstʵ���Ӹ����м̳еõ��ģ�
//�����Ҫʵ���������Բ��Һ�����
//��ʵ�����в��ҵ�ʱ���������²��ң�Ȼ�����ϲ���
OOPLIB_API void  Invoke(InstanceChain* pChain, void* pInst, char* pFuncName, void* pParams);

//�ú�����Ŀ������ͨ��ʵ��ָ��pInst������ΪpFuncName�ĺ���������ΪpParams��
//ʵ����pChain���ڲ��Һ�����
//����ʱ��ֻ�����ϲ���
OOPLIB_API void  InvokeSuper(InstanceChain* pChain, void* pInst, char* pFuncName, void* pParams);

//�ú�����ʵ����pChain�в��Ҹ�����ʵ��ָ��pInst��Ȼ�����ϲ��ң�ֱ���ҵ��������͵�ʵ��Ϊֹ
OOPLIB_API void* AsBaseByType(InstanceChain* pChain, void* pInst, char* pBaseType);

//���ݺ������ƣ�ȷ��ʵ�������ĸ�ʵ�����ᱻ���ã��������²��ң�Ȼ�����ϲ���
OOPLIB_API void* AsBaseByFunc(InstanceChain* pChain, void* pInst, char* pFuncName);

//���ݺ������ƣ�ȷ��ʵ�������ĸ�ʵ�����ᱻ���ã������ϲ���
OOPLIB_API void* AsBaseByFuncUpward(InstanceChain* pChain, void* pInst, char* pFuncName);

//��ȡ����ʵ����ʵ������ָ��
OOPLIB_API void* AsExactType(InstanceChain* pChain, void* pInst);

OOPLIB_API void  Delete(InstanceChain* pChain);

////Object//////////////////////////////////////////////////////////////////////////////
//

typedef struct Object Object;

OOPLIB_API Object* CREATE(Object)();
OOPLIB_API void    INVOKE(Object)(Object*   pInst, char* pFuncName, void* pParams);
OOPLIB_API void*   EXTEND(Object)(Object*   pInst);
OOPLIB_API void    DELETE(Object)(Object** ppInst);

typedef struct { bool* pRet; void* pToCmpr; } Object_Equal;
typedef ParamNull Object_ToString;

#endif // !OOPBASE_H__


