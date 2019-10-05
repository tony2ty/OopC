
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
            FactorySkinSpring *pFactorySpring = CREATE(FactorySkinSpring)();
            pFactory = SWITCH(pFactorySpring, FactorySkinSpring, IFactorySkin);
        }

        ICtrlButton *pButton = NULL;
        ICtrlTextField *pTextField = NULL;
        ICtrlComboBox *pComboBox = NULL;

        INVOKE(IFactorySkin)(pFactory, "CreateButton", &(IFactorySkin_CreateButton){&pButton});
        INVOKE(IFactorySkin)(pFactory, "CreateTextField", &(IFactorySkin_CreateTextField){&pTextField});
        INVOKE(IFactorySkin)(pFactory, "CreateComboBox", &(IFactorySkin_CreateComboBox){&pComboBox});

        INVOKE(ICtrlButton)(pButton, "Display", NULL);
        INVOKE(ICtrlTextField)(pTextField, "Display", NULL);
        INVOKE(ICtrlComboBox)(pComboBox, "Display", NULL);

        DELETE(ICtrlButton)(&pButton);
        DELETE(ICtrlTextField)(&pTextField);
        DELETE(ICtrlComboBox)(&pComboBox);

        DELETE(IFactorySkin)(&pFactory);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    {
        IFactorySkin *pFactory = NULL;
        {
            FactorySkinSummer *pFactorySummer = CREATE(FactorySkinSummer)();
            pFactory = SWITCH(pFactorySummer, FactorySkinSummer, IFactorySkin);
        }

        ICtrlButton *pButton = NULL;
        ICtrlTextField *pTextField = NULL;
        ICtrlComboBox *pComboBox = NULL;

        INVOKE(IFactorySkin)(pFactory, "CreateButton", &(IFactorySkin_CreateButton){ &pButton });
        INVOKE(IFactorySkin)(pFactory, "CreateTextField", &(IFactorySkin_CreateTextField){ &pTextField });
        INVOKE(IFactorySkin)(pFactory, "CreateComboBox", &(IFactorySkin_CreateComboBox){ &pComboBox });

        INVOKE(ICtrlButton)(pButton, "Display", NULL);
        INVOKE(ICtrlTextField)(pTextField, "Display", NULL);
        INVOKE(ICtrlComboBox)(pComboBox, "Display", NULL);

        DELETE(ICtrlButton)(&pButton);
        DELETE(ICtrlTextField)(&pTextField);
        DELETE(ICtrlComboBox)(&pComboBox);

        DELETE(IFactorySkin)(&pFactory);
    }

    system("pause");
    
    return 0;
}