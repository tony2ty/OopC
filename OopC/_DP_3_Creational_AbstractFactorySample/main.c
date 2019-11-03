
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
            FactorySkinSpring *pFactorySpring = CREATE(FactorySkinSpring)(); TORLS(DELETE(FactorySkinSpring), pFactorySpring);
            pFactory = SWITCH(pFactorySpring, FactorySkinSpring, IFactorySkin);
        }

        ICtrlButton *pButton = NULL;
        ICtrlTextField *pTextField = NULL;
        ICtrlComboBox *pComboBox = NULL;

        INVOKE(IFactorySkin)(pFactory, "CreateButton", &(IFactorySkin_CreateButton){&pButton}); TORLS(DELETE(ICtrlButton), pButton);
        INVOKE(IFactorySkin)(pFactory, "CreateTextField", &(IFactorySkin_CreateTextField){&pTextField}); TORLS(DELETE(ICtrlTextField), pTextField);
        INVOKE(IFactorySkin)(pFactory, "CreateComboBox", &(IFactorySkin_CreateComboBox){&pComboBox}); TORLS(DELETE(ICtrlComboBox), pComboBox);

        INVOKE(ICtrlButton)(pButton, "Display", NULL);
        INVOKE(ICtrlTextField)(pTextField, "Display", NULL);
        INVOKE(ICtrlComboBox)(pComboBox, "Display", NULL);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    {
        IFactorySkin *pFactory = NULL;
        {
            FactorySkinSummer *pFactorySummer = CREATE(FactorySkinSummer)(); TORLS(DELETE(FactorySkinSummer), pFactorySummer);
            pFactory = SWITCH(pFactorySummer, FactorySkinSummer, IFactorySkin);
        }

        ICtrlButton *pButton = NULL;
        ICtrlTextField *pTextField = NULL;
        ICtrlComboBox *pComboBox = NULL;

        INVOKE(IFactorySkin)(pFactory, "CreateButton", &(IFactorySkin_CreateButton){ &pButton }); TORLS(DELETE(ICtrlButton), pButton);
        INVOKE(IFactorySkin)(pFactory, "CreateTextField", &(IFactorySkin_CreateTextField){ &pTextField }); TORLS(DELETE(ICtrlTextField), pTextField);
        INVOKE(IFactorySkin)(pFactory, "CreateComboBox", &(IFactorySkin_CreateComboBox){ &pComboBox }); TORLS(DELETE(ICtrlComboBox), pComboBox);

        INVOKE(ICtrlButton)(pButton, "Display", NULL);
        INVOKE(ICtrlTextField)(pTextField, "Display", NULL);
        INVOKE(ICtrlComboBox)(pComboBox, "Display", NULL);
    }

    system("pause");

    RLSLOCALMEMKET();
    
    return 0;
}