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


#ifndef OOPUTIL_H__
#define OOPUTIL_H__

#ifdef OOPUTIL_API
#else
    #define OOPUTIL_API __declspec(dllimport)
#endif // OOPUTIL_API

#include <OopBase.h>

/**************************************************/
/****************** IniWrapper ********************/
/**************************************************/

__CLASS IniWrapper;
OOPUTIL_API __CONSTRUCTOR(IniWrapper);
__METHODDECLARE(
	/* 
	 * no file will result in initialization failure. */
	Init:     const char* pIniFileName; bool* pRet;
	/*
	 * Create new section by passing null to pKey; 
	 * Value cannot be set if both section and key are not found;
	 * writing new key to an existing section means creating new key-value; */
	WriteIni: const char* pSection; const char* pKey; const char* pVal; bool *pRet;
	/*
	 * ppRetVal is read-only.
	 * "" will be returned when section or key not found. */
	ReadIni:  const char* pSection; const char *pKey; const char** ppRetVal; bool *pRet;
	/*
	 * null pSaveAs will cause in-place save operation;
	 * if pSaveAs is not null, all ini config will be writed into the file specified by pSaveAs. */
	Save:     const char* pSaveAs; bool *pRet;)

#endif // !OOPUTIL_H__

