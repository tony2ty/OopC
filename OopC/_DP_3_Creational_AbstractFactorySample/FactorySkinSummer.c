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

#include <malloc.h>
#include "CtrlButtonSummer.h"
#include "CtrlTextFieldSummer.h"
#include "CtrlComboBoxSummer.h"

struct FactorySkinSummer
{
    CHAINDEF;
};

////////////////////////////////////////////////////////////////////////
//

static void CreateButton(void *pParams)
{
    FactorySkinSummer *pThis = ((ParamIn *)pParams)->pInst;
    FactorySkinSummer_CreateButton *pIn = ((ParamIn *)pParams)->pIn;

    CtrlButtonSummer *pButton = CREATE(CtrlButtonSummer)();
    *pIn->ppButton = SWITCH(pButton, CtrlButtonSummer, ICtrlButton);
}

static void CreateTextField(void *pParams)
{
    FactorySkinSummer *pThis = ((ParamIn *)pParams)->pInst;
    FactorySkinSummer_CreateTextField *pIn = ((ParamIn *)pParams)->pIn;

    CtrlTextFieldSummer *pTextField = CREATE(CtrlTextFieldSummer)();
    *pIn->ppTextField = SWITCH(pTextField, CtrlTextFieldSummer, ICtrlTextField);
}

static void CreateComboBox(void *pParams)
{
    FactorySkinSummer *pThis = ((ParamIn *)pParams)->pInst;
    FactorySkinSummer_CreateComboBox *pIn = ((ParamIn *)pParams)->pIn;

    CtrlComboBoxSummer *pComboBox = CREATE(CtrlComboBoxSummer)();
    *pIn->ppComboBox = SWITCH(pComboBox, CtrlComboBoxSummer, ICtrlComboBox);
}

////////////////////////////////////////////////////////////////////////
//

bool INVOKE(FactorySkinSummer)(FactorySkinSummer *pInst, char *pFuncName, void *pParams)
{
    DOINVOKE(pInst, pFuncName, pParams);
}

void *EXTEND(FactorySkinSummer)(FactorySkinSummer *pInst)
{
    DOEXTEND(pInst);
}

void DELETE(FactorySkinSummer)(FactorySkinSummer **ppInst)
{
    DODELETE(ppInst, FactorySkinSummer, IFactorySkin);
}

FactorySkinSummer *CREATE(FactorySkinSummer)()
{
    DOCREATE(pCreate, FactorySkinSummer, IFactorySkin, NULL,
        METHOD(CreateButton)
        METHOD(CreateTextField)
        METHOD(CreateComboBox));

    return pCreate;
}