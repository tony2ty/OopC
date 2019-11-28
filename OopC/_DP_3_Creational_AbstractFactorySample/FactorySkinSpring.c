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


#include "FactorySkinSpring.h"

#include "CtrlButtonSpring.h"
#include "CtrlTextFieldSpring.h"
#include "CtrlComboBoxSpring.h"


__OVERRIDE static void CreateButton(void *_pThis, va_list* pvlArgs)
{
    FactorySkinSpring *pThis = _pThis;

    ICtrlButton **ppButton = va_arg(*pvlArgs, ICtrlButton **);

    CtrlButtonSpring *pButton = __NEW(CtrlButtonSpring);
    *ppButton = __Cvt(pButton, __TYPE(ICtrlButton));
}

__OVERRIDE static void CreateTextField(void *_pThis, va_list* pvlArgs)
{
    FactorySkinSpring *pThis = _pThis;

    ICtrlTextField **ppTextField = va_arg(*pvlArgs, ICtrlTextField **);

    CtrlTextFieldSpring *pTextField = __NEW(CtrlTextFieldSpring);
    *ppTextField = __Cvt(pTextField, __TYPE(ICtrlTextField));
}

__OVERRIDE static void CreateComboBox(void *_pThis, va_list* pvlArgs)
{
    FactorySkinSpring *pThis = _pThis;

    ICtrlComboBox **ppComboBox = va_arg(*pvlArgs, ICtrlComboBox **);

    CtrlComboBoxSpring *pComboBox = __NEW(CtrlComboBoxSpring);
    *ppComboBox = __Cvt(pComboBox, __TYPE(ICtrlComboBox));
}

__CONSTRUCTOR(FactorySkinSpring)
{
	return __New(__TYPE(FactorySkinSpring), 0, NULL, 3, 1,
		__METHOD(CreateButton),
		__METHOD(CreateTextField),
		__METHOD(CreateComboBox),
		__INHERIT(IFactorySkin));
}
