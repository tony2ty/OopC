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


#include "FactorySkinSummer.h"

#include "CtrlButtonSummer.h"
#include "CtrlTextFieldSummer.h"
#include "CtrlComboBoxSummer.h"

struct FactorySkinSummer_Fld
{
    CHAINDECLARE;
};

////////////////////////////////////////////////////////////////////////
//

OVERRIDE static void CreateButton(ParamIn *pParams)
{
    FactorySkinSummer *pThis = pParams->pThis;
    va_list vlArgs = pParams->vlArgs;

    ICtrlButton **ppButton = va_arg(vlArgs, ICtrlButton **);

    CtrlButtonSummer *pButton = NEW(CtrlButtonSummer);
    *ppButton = SWITCH(pButton, ICtrlButton);
}

OVERRIDE static void CreateTextField(ParamIn *pParams)
{
    FactorySkinSummer *pThis = pParams->pThis;
    va_list vlArgs = pParams->vlArgs;

    ICtrlTextField **ppTextField = va_arg(vlArgs, ICtrlTextField **);

    CtrlTextFieldSummer *pTextField = NEW(CtrlTextFieldSummer);
    *ppTextField = SWITCH(pTextField, ICtrlTextField);
}

OVERRIDE static void CreateComboBox(ParamIn *pParams)
{
    FactorySkinSummer *pThis = pParams->pThis;
    va_list vlArgs = pParams->vlArgs;

    ICtrlComboBox **ppComboBox = va_arg(vlArgs, ICtrlComboBox **);

    CtrlComboBoxSummer *pComboBox = NEW(CtrlComboBoxSummer);
    *ppComboBox = SWITCH(pComboBox, ICtrlComboBox);
}

////////////////////////////////////////////////////////////////////////
//

static bool __CALL(FactorySkinSummer)(FactorySkinSummer *pSelf, const char *pMethodName, ...)
{
    DOCALL(pSelf, pMethodName);
}

static void *__EXTEND(FactorySkinSummer)(FactorySkinSummer *pSelf)
{
    DOEXTEND(pSelf);
}

void __DEL(FactorySkinSummer)(FactorySkinSummer *pSelf)
{
    DODEL(pSelf, IFactorySkin);
}

FactorySkinSummer *__NEW(FactorySkinSummer)()
{
    DONEW(pNew, FactorySkinSummer, IFactorySkin, NULL,
        METHOD(CreateButton)
        METHOD(CreateTextField)
        METHOD(CreateComboBox));

    return pNew;
}
