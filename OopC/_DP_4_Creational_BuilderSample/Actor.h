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
	 * pType: 演员类型，null结尾的字符串
	 * pRet:  设值情况
	 *
	 * 设置演员类型 */
	SetType: const char* pType; bool* pRet;
	/*
	 * ppType: 返回的演员类型字符串值，返回的*ppType为null结尾的字符串，输入的*ppType指向的区域应该可以使用free释放，
	 *         因为内部将调用realloc(*ppType, szLen)
	 * pRet:   读值情况
	 *
	 * 获取演员类型 */
	GetType: char** ppType; bool* pRet;
	/*
	 * pGender: 演员性别，null结尾字符串
	 * pRet:    设值情况
	 *
	 * 设置演员性别 */
	SetGender: const char* pGender; bool* pRet;
	/*
	 * ppGender: 返回演员的性别，返回的*ppGender为null结尾字符串，输入的*ppGender指向的区域应该可以使用free释放，
	 *           因为内部将调用realloc(*ppGender, szLen)
	 * pRet:     读值情况
	 *
	 * 获取演员的性别 */
	GetGender: char** ppGender; bool* pRet;
	/*
	 * pFace: 演员们的容貌，null结尾的字符串
	 * pRet:  设值情况
	 *
	 * 设置演员的容貌 */
	SetFace: const char* pFace; bool* pRet;
	/*
	 * ppFace: 返回演员的容貌，返回时*ppFace为null结尾的字符串，输入的*ppFace指向的区域应该可以使用free释放，
	 *         因为内部将调用realloc(*ppFace, szLen)
	 * pRet:   设值情况
	 *
	 * 获取演员的容貌 */
	GetFace: char** ppFace; bool* pRet;
	/*
	 * pCostume: 演员的装扮，null结尾的字符串
	 * pRet:     设值情况
	 *
	 * 设值演员的装扮 */
	SetCostume: const char* pCostume; bool* pRet;
	/*
	 * ppCostume: 返回演员的装扮，返回时*ppCostume为null结尾的字符串，输入的*ppCosutme指向的区域应该可以使用free释放，
	 *            因为内部将调用realloc(*ppCostume, szLne)
	 * pRet:      读值情况
	 *
	 * 获取演员的装扮 */
	GetCostume: char** ppCostume; bool* pRet;
	/*
	 * pHairStyle: 演员的发型，null结尾的字符串
	 * pRet:       设值情况
	 *
	 * 设值演员的发型 */
	SetHairStyle: const char* pHairStyle; bool* pRet;
	/*
	 * ppHairStyle: 返回演员的发型，返回时*ppHairStyle为null结尾的字符串，输入的*ppHairStyle指向的区域应该可以使用free释放，
	 *              因为内部将调用realloc(*ppHairStyle, szLen)
	 * pRet:        读值情况
	 *
	 * 获取演员的发型 */
	GetHairStyle: char **ppHairStyle; bool* pRet;)

#endif // !ACTOR_H__
