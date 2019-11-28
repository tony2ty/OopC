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


#ifndef IBUILDERACTOR_H__
#define IBUILDERACTOR_H__

#include <OopBase.h>

#include "Actor.h"

__CLASS IBuilderActor;
__CONSTRUCTOR(IBuilderActor);
__METHODDECLARE(
	__ABSTRACT BuildType : bool *pRet;
	__ABSTRACT BuildGender : bool* pRet;
	__ABSTRACT BuildFace : bool* pRet;
	__ABSTRACT BuildCostume : bool* pRet;
	__ABSTRACT BuildHairStyle : bool* pRet;
	/*
	 * ppActor: 返回创建好的演员对象 */
	__ABSTRACT CreateActor : Actor **ppActor;)

#endif // !IBUILDERACTOR_H__

