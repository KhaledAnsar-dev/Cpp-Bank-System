#pragma once
#include"clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


class clsUpdateClient : protected clsScreen
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

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "Enter a name : \n";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "Enter a last name : \n";
        Client.LastName = clsInputValidate::ReadString();

        cout << "Enter an email : \n";
        Client.Email = clsInputValidate::ReadString();

        cout << "Enter a phone : \n";
        Client.Phone = clsInputValidate::ReadString();

        cout << "Enter a password : \n";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "Enter an account balance : \n";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

public:
    static void ShowUpdateClientScreen() 
    {
        if (!_CheckAccessRigths(clsUser::enMainMenuPermissions::UpdateClients_))
        {
            return;
        }

        string AccountNumber = "";

        _DrawHeaderScreen("\t   Update Client Screen");


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

            cout << "\n Update Data : \n";
            cout << "----------------------\n";

            _ReadClientInfo(Client1);
            clsBankClient::enSaveResult SaveResult;

            SaveResult = Client1.Save();


            switch (SaveResult)
            {
            case clsBankClient::svSucceeded:
            {
                cout << "\nAccount updated Successfully : -)\n";
                _PrintClient(Client1);
                break;
            }
            case clsBankClient::svFaildEmptyObject:
            {
                cout << "\nError , account was not saved because it's empty\n";
                break;
            }
            }
        }

        


    }
};

