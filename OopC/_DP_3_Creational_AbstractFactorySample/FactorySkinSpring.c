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

struct FactorySkinSpring
{
    CHAINDEF;
};

////////////////////////////////////////////////////////////////////////
//

static void CreateButton(void *pParams)
{
    FactorySkinSpring *pThis = ((ParamIn *)pParams)->pInst;
    FactorySkinSpring_CreateButton *pIn = ((ParamIn *)pParams)->pIn;

    CtrlButtonSpring *pButton = CREATE(CtrlButtonSpring)();
    *pIn->ppButton = SWITCH(pButton, CtrlButtonSpring, ICtrlButton);
}

static void CreateTextField(void *pParams)
{
    FactorySkinSpring *pThis = ((ParamIn *)pParams)->pInst;
    FactorySkinSpring_CreateTextField *pIn = ((ParamIn *)pParams)->pIn;

    CtrlTextFieldSpring *pTextField = CREATE(CtrlTextFieldSpring)();
    *pIn->ppTextField = SWITCH(pTextField, CtrlTextFieldSpring, ICtrlTextField);
}

static void CreateComboBox(void *pParams)
{
    FactorySkinSpring *pThis = ((ParamIn *)pParams)->pInst;
    FactorySkinSpring_CreateComboBox *pIn = ((ParamIn *)pParams)->pIn;

    CtrlComboBoxSpring *pComboBox = CREATE(CtrlComboBoxSpring)();
    *pIn->ppComboBox = SWITCH(pComboBox, CtrlComboBoxSpring, ICtrlComboBox);
}

////////////////////////////////////////////////////////////////////////
//

bool INVOKE(FactorySkinSpring)(FactorySkinSpring *pInst, char *pFuncName, void *pParams)
{
    DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(FactorySkinSpring)(FactorySkinSpring *pInst)
{
    DOEXTEND(pInst);
}

void DELETE(FactorySkinSpring)(FactorySkinSpring *pInst)
{
    DODELETE(pInst, FactorySkinSpring, IFactorySkin);
}

FactorySkinSpring *CREATE(FactorySkinSpring)()
{
    DOCREATE(pCreate, FactorySkinSpring, IFactorySkin, NULL,
        METHOD(CreateButton)
        METHOD(CreateTextField)
        METHOD(CreateComboBox));

    return pCreate;
}