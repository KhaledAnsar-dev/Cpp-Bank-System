#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsDepositScreen  : protected clsScreen
{
private:
    static string _ReadAccountNumber(string Message)
    {
        string Account = "";
        cout << Message << endl;
        getline(cin >> ws, Account);
        return Account;
    }

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
    static void ShowDepositScreen()
    {

        _DrawHeaderScreen("\t     Deposit screen");

        string AccountNumber = _ReadAccountNumber("Please enter Account Number");
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "!!! Account Number ,is NOT found , choose another one : \n";
            AccountNumber = _ReadAccountNumber("Please enter Account Number");
        }
        clsBankClient Clients = clsBankClient::Find(AccountNumber);

       
        _PrintClient(Clients);

        double Amount = 0;
        cout << "Please Enter Deposit Amount\n";
        Amount = clsInputValidate::ReadDblNumber();

        char Answer = -'n';
        cout << "Are you sure you want delete this element : y/n ?\n";
        cin >> Answer;


        if (toupper(Answer) == 'Y')
        {
            Clients.Deposit(Amount);

            cout << "Balance updated successfully\n";
            cout << "New Balance is : " << Clients.AccountBalance << endl;

        }

        else
            cout << "Opperation was cancelled\n";

    }

};

