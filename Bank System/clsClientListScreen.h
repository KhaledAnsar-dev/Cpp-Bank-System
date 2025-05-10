#pragma once
#include"clsScreen.h"
#include "clsBankClient.h"
#include<iomanip>

class clsClientListScreen : protected clsScreen
{
private:
    void static _PrintClientRecordLine(clsBankClient Client)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.GetAccountNumber();
        cout << "| " << setw(20) << left << Client.GetFullName();
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;

    }

public:
    static void ShowClientList()
    {
        if (!_CheckAccessRigths(clsUser::enMainMenuPermissions::ClientList_))
        {
            return;
        }

        vector <clsBankClient> vClass;

        vClass = clsBankClient::GetClientsList();

        string Title = "\t  Clients List Screen";
        string SubTitle = "\t     (" + to_string(vClass.size()) + ") Clients";

        _DrawHeaderScreen(Title ,SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClass.size() == 0)
            cout << "\t\t\t\tNo Clints Available in The System\n";

        for (clsBankClient C : vClass)
        {
            _PrintClientRecordLine(C);
            cout << endl;
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

};

