#pragma once
#pragma once
#include"clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsFindClientScreen : protected clsScreen
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
	static void ShowFindClientScreen()
	{
        if (!_CheckAccessRigths(clsUser::enMainMenuPermissions::FindClients_))
        {
            return;
        }

        _DrawHeaderScreen("\t\tFind Client Screen");

        cout << "Please enter client Account Number : \n";

        string AccountNumber = clsInputValidate::ReadString();
        
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "!!! Account Number ,is NOT found , choose another one : \n";
            AccountNumber = clsInputValidate::ReadString();
        }

        		
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        if (!Client1.IsEmpty())
            cout << "\nClient found\n\n";

        else
            cout << "\nClient Not found\n\n";

        _PrintClient(Client1);

	}
};

