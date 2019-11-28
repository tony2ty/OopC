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


#include <stdlib.h>

#include "IFactorySkin.h"
#include "FactorySkinSpring.h"
#include "FactorySkinSummer.h"

#include "ICtrlButton.h"
#include "ICtrlTextField.h"
#include "ICtrlComboBox.h"

int main(int argc, char **argv)
{
    {
        IFactorySkin *pFactory = NULL;
        {
            FactorySkinSpring *pFactorySpring = __NEW(FactorySkinSpring);
            pFactory = __Cvt(pFactorySpring, __TYPE(IFactorySkin));
        }

        ICtrlButton *pButton = NULL;
        ICtrlTextField *pTextField = NULL;
        ICtrlComboBox *pComboBox = NULL;

        pFactory->Call(pFactory, "CreateButton", &pButton);
        pFactory->Call(pFactory, "CreateTextField", &pTextField);
        pFactory->Call(pFactory, "CreateComboBox", &pComboBox);

        pButton->Call(pButton, "Display");
        pTextField->Call(pTextField, "Display");
        pComboBox->Call(pComboBox, "Display");

		pButton->Destroy(pButton);
		pTextField->Destroy(pTextField);
		pComboBox->Destroy(pComboBox);

		pFactory->Destroy(pFactory);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    {
        IFactorySkin *pFactory = NULL;
        {
            FactorySkinSummer *pFactorySummer = __NEW(FactorySkinSummer);
            pFactory = __Cvt(pFactorySummer, __TYPE(IFactorySkin));
        }

        ICtrlButton *pButton = NULL;
        ICtrlTextField *pTextField = NULL;
        ICtrlComboBox *pComboBox = NULL;

        pFactory->Call(pFactory, "CreateButton", &pButton);
        pFactory->Call(pFactory, "CreateTextField", &pTextField);
        pFactory->Call(pFactory, "CreateComboBox", &pComboBox);

        pButton->Call(pButton, "Display");
        pTextField->Call(pTextField, "Display");
        pComboBox->Call(pComboBox, "Display");

		pButton->Destroy(pButton);
		pTextField->Destroy(pTextField);
		pComboBox->Destroy(pComboBox);

		pFactory->Destroy(pFactory);
    }

    return 0;
}