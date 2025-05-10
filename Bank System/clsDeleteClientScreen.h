#pragma once
#include"clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "Client Card : \n";
        cout << "------------------------\n";
        cout << "\nFirst Name      : " << Client.FirstName;
        cout << "\nLast Name       : " << Client.LastName;
        cout << "\nEmail           : " << Client.Email;
        cout << "\nPhone           : " << Client.Phone;
        cout << "\nAccount Number  : " << Client.GetAccountNumber();
        cout << "\nPassword        : " << Client.PinCode;
        cout << "\nAccount Balance : " << Client.AccountBalance;
        cout << "\n------------------------\n";
    }

public:
    static void ShowDeleteClientScreen()
    {
        if (!_CheckAccessRigths(clsUser::enMainMenuPermissions::DeleteClients_))
        {
            return;
        }

        string AccountNumber = "";

        _DrawHeaderScreen("\t   Delete Client Screen");

        cout << "Please enter client Account Number : \n";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "!!! Account Number ,is NOT found , choose another one : \n";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        _PrintClient(Client1);

        char Answer = -'n';
        cout << "Are you sure you want delete this element : y/n ?\n";
        cin >> Answer;


        if (toupper(Answer) == 'Y')
        {
            if (Client1.Delete())
            {
                cout << "\nClient deleted Successfully : -)\n";

                _PrintClient(Client1);
            }
            else
                cout << "\nError , client was not deleted\n";
        }


    }

};

