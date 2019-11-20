
#include <stdlib.h>

#include "IFactorySkin.h"
#include "FactorySkinSpring.h"
#include "FactorySkinSummer.h"

#include "ICtrlButton.h"
#include "ICtrlTextField.h"
#include "ICtrlComboBox.h"

int main(int argc, char **argv)
{
    RLSLOCALMEMBRA();

    {
        IFactorySkin *pFactory = NULL;
        {
            FactorySkinSpring *pFactorySpring = NEW(FactorySkinSpring); TORLS(DEL(FactorySkinSpring), pFactorySpring);
            pFactory = SWITCH(pFactorySpring, IFactorySkin);
        }

        ICtrlButton *pButton = NULL;
        ICtrlTextField *pTextField = NULL;
        ICtrlComboBox *pComboBox = NULL;

        pFactory->Call(pFactory, "CreateButton", &pButton); TORLS(DEL(ICtrlButton), pButton);
        pFactory->Call(pFactory, "CreateTextField", &pTextField); TORLS(DEL(ICtrlTextField), pTextField);
        pFactory->Call(pFactory, "CreateComboBox", &pComboBox); TORLS(DEL(ICtrlComboBox), pComboBox);

        pButton->Call(pButton, "Display");
        pTextField->Call(pTextField, "Display");
        pComboBox->Call(pComboBox, "Display");
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    {
        IFactorySkin *pFactory = NULL;
        {
            FactorySkinSummer *pFactorySummer = NEW(FactorySkinSummer); TORLS(DEL(FactorySkinSummer), pFactorySummer);
            pFactory = SWITCH(pFactorySummer, IFactorySkin);
        }

        ICtrlButton *pButton = NULL;
        ICtrlTextField *pTextField = NULL;
        ICtrlComboBox *pComboBox = NULL;

        pFactory->Call(pFactory, "CreateButton", &pButton); TORLS(DEL(ICtrlButton), pButton);
        pFactory->Call(pFactory, "CreateTextField", &pTextField); TORLS(DEL(ICtrlTextField), pTextField);
        pFactory->Call(pFactory, "CreateComboBox", &pComboBox); TORLS(DEL(ICtrlComboBox), pComboBox);

        pButton->Call(pButton, "Display");
        pTextField->Call(pTextField, "Display");
        pComboBox->Call(pComboBox, "Display");
    }

    RLSLOCALMEMKET();
    
    return 0;
}