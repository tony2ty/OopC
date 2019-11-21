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


#ifndef ACTOR_H__
#define ACTOR_H__

#include <OopBase.h>

CLASS(Actor, Object);
METHODDECLARE(
	/*
	 * pType: ��Ա���ͣ�null��β���ַ���
	 * pRet:  ��ֵ���
	 *
	 * ������Ա���� */
	SetType: const char* pType; bool* pRet;
	/*
	 * ppType: ���ص���Ա�����ַ���ֵ�����ص�*ppTypeΪnull��β���ַ����������*ppTypeָ�������Ӧ�ÿ���ʹ��free�ͷţ�
	 *         ��Ϊ�ڲ�������realloc(*ppType, szLen)
	 * pRet:   ��ֵ���
	 *
	 * ��ȡ��Ա���� */
	GetType: char** ppType; bool* pRet;
	/*
	 * pGender: ��Ա�Ա�null��β�ַ���
	 * pRet:    ��ֵ���
	 *
	 * ������Ա�Ա� */
	SetGender: const char* pGender; bool* pRet;
	/*
	 * ppGender: ������Ա���Ա𣬷��ص�*ppGenderΪnull��β�ַ����������*ppGenderָ�������Ӧ�ÿ���ʹ��free�ͷţ�
	 *           ��Ϊ�ڲ�������realloc(*ppGender, szLen)
	 * pRet:     ��ֵ���
	 *
	 * ��ȡ��Ա���Ա� */
	GetGender: char** ppGender; bool* pRet;
	/*
	 * pFace: ��Ա�ǵ���ò��null��β���ַ���
	 * pRet:  ��ֵ���
	 *
	 * ������Ա����ò */
	SetFace: const char* pFace; bool* pRet;
	/*
	 * ppFace: ������Ա����ò������ʱ*ppFaceΪnull��β���ַ����������*ppFaceָ�������Ӧ�ÿ���ʹ��free�ͷţ�
	 *         ��Ϊ�ڲ�������realloc(*ppFace, szLen)
	 * pRet:   ��ֵ���
	 *
	 * ��ȡ��Ա����ò */
	GetFace: char** ppFace; bool* pRet;
	/*
	 * pCostume: ��Ա��װ�磬null��β���ַ���
	 * pRet:     ��ֵ���
	 *
	 * ��ֵ��Ա��װ�� */
	SetCostume: const char* pCostume; bool* pRet;
	/*
	 * ppCostume: ������Ա��װ�磬����ʱ*ppCostumeΪnull��β���ַ����������*ppCosutmeָ�������Ӧ�ÿ���ʹ��free�ͷţ�
	 *            ��Ϊ�ڲ�������realloc(*ppCostume, szLne)
	 * pRet:      ��ֵ���
	 *
	 * ��ȡ��Ա��װ�� */
	GetCostume: char** ppCostume; bool* pRet;
	/*
	 * pHairStyle: ��Ա�ķ��ͣ�null��β���ַ���
	 * pRet:       ��ֵ���
	 *
	 * ��ֵ��Ա�ķ��� */
	SetHairStyle: const char* pHairStyle; bool* pRet;
	/*
	 * ppHairStyle: ������Ա�ķ��ͣ�����ʱ*ppHairStyleΪnull��β���ַ����������*ppHairStyleָ�������Ӧ�ÿ���ʹ��free�ͷţ�
	 *              ��Ϊ�ڲ�������realloc(*ppHairStyle, szLen)
	 * pRet:        ��ֵ���
	 *
	 * ��ȡ��Ա�ķ��� */
	GetHairStyle: char **ppHairStyle; bool* pRet;)

#endif // !ACTOR_H__
