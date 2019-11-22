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

struct FactorySkinSpring_Fld
{
    CHAINDECLARE;
};

////////////////////////////////////////////////////////////////////////
//

OVERRIDE static void CreateButton(void *_pThis, va_list vlArgs)
{
    FactorySkinSpring *pThis = _pThis;

    ICtrlButton **ppButton = va_arg(vlArgs, ICtrlButton **);

    CtrlButtonSpring *pButton = NEW(CtrlButtonSpring);
    *ppButton = SWITCH(pButton, ICtrlButton);
}

OVERRIDE static void CreateTextField(void *_pThis, va_list vlArgs)
{
    FactorySkinSpring *pThis = _pThis;

    ICtrlTextField **ppTextField = va_arg(vlArgs, ICtrlTextField **);

    CtrlTextFieldSpring *pTextField = NEW(CtrlTextFieldSpring);
    *ppTextField = SWITCH(pTextField, ICtrlTextField);
}

OVERRIDE static void CreateComboBox(void *_pThis, va_list vlArgs)
{
    FactorySkinSpring *pThis = _pThis;

    ICtrlComboBox **ppComboBox = va_arg(vlArgs, ICtrlComboBox **);

    CtrlComboBoxSpring *pComboBox = NEW(CtrlComboBoxSpring);
    *ppComboBox = SWITCH(pComboBox, ICtrlComboBox);
}

////////////////////////////////////////////////////////////////////////
//

static bool __CALL(FactorySkinSpring)(FactorySkinSpring *pSelf, const char *pMethodName, ...)
{
    DOCALL(pSelf, pMethodName);
}

static void *__EXTEND(FactorySkinSpring)(FactorySkinSpring *pSelf)
{
    DOEXTEND(pSelf);
}

void __DEL(FactorySkinSpring)(FactorySkinSpring *pSelf)
{
    DODEL(pSelf, IFactorySkin);
}

FactorySkinSpring *__NEW(FactorySkinSpring)()
{
    DONEW(pNew, FactorySkinSpring, IFactorySkin, NULL,
        METHOD(CreateButton)
        METHOD(CreateTextField)
        METHOD(CreateComboBox));

    return pNew;
}
