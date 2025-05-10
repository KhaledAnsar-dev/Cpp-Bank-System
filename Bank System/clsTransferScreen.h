#pragma once
#include <iostream>
#include <iomanip>
#include"clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsTransferScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card : \n";
        cout << "------------------------";
        cout << "\nFirst Name      : " << Client.GetFullName();
        cout << "\nAccount Number  : " << Client.GetAccountNumber();
        cout << "\nAccount Balance : " << Client.AccountBalance;
        cout << "\n------------------------\n";
    }

    static string _ReadAccountNumber(string Message)
    {
        string AccountNumber = "";

        //cout << "Please enter account number to transfer from : ";
        cout << Message;
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "!!! Client Doesn't Exist ,try another one : \n";
            AccountNumber = clsInputValidate::ReadString();
        }

        return AccountNumber;
    }

    static double _ReadAmount(double AccountBalance)
    {
        double Amount = 0;
        cout << "Enter Transfer Amount :\n";
        Amount = clsInputValidate::ReadDblNumber();

        while(Amount > AccountBalance)
        {
            cout << "Cannot withdraw ,Insuffecient balance , Max is " << AccountBalance << endl;
            cout << "Enter new transfer amount : ";
            Amount = clsInputValidate::ReadDblNumber();
        }

        return Amount;
    }

public:
    static void ShowTransferScreen()
    {

        _DrawHeaderScreen("\t   Transfer Screen");

        // Sender
        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("Please enter account number to transfer from : "));
        
        _PrintClient(SourceClient);


        // Receiver
        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("Please enter account number to transfer to : "));

        _PrintClient(DestinationClient);

        // Amount

        double Amount = _ReadAmount(SourceClient.AccountBalance);
        char Answer = -'n';
        cout << "Are you sure you want to perform this transaction : y/n ?\n";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            if(SourceClient.Transfer(Amount, DestinationClient , CurrentUser.UserName))
            {
                cout << "Transfer done successfully\n";
            }
            else
                cout << "Transfer Faild\n";
        }
        

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);



    }
};