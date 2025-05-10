#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsUtil.h"

class clsTotalBalanceScreen : protected clsScreen
{
private:
    static void PrintBalanceRecordLine(clsBankClient Class)
    {
        cout << setw(25) << left << "" << "| " << left << setw(15) << Class.GetAccountNumber();
        cout << "| " << left << setw(30) << Class.GetFullName();
        cout << "| " << left << setw(15) << Class.AccountBalance << "|" << endl;

    }

public:
    static void ShowTotalBalanceList()
    {
        vector <clsBankClient> vClass;

        vClass = clsBankClient::GetClientsList();
        string Title = "\t   Total Balance Screen";
        string SubTitle = "\tBalance list : (" + to_string(vClass.size()) + ") Clients";
        _DrawHeaderScreen(Title , SubTitle);
        cout << setw(25) << left << "" << "-----------------------------------";
        cout << "--------------------------------\n\n";
        cout << setw(25) << left << "" << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(30) << "Full Name";
        cout << "| " << left << setw(15) << "Account Balance" << "|\n\n";
        cout << setw(25) << left << "" << "-----------------------------------";
        cout << "--------------------------------\n\n";
        if (vClass.size() == 0)
            cout << "\t\t\t\tNo Clints Available in The System\n";

        for (clsBankClient C : vClass)
        {
            PrintBalanceRecordLine(C);
        }

        cout << setw(25) << left << "" << "-----------------------------------";
        cout << "--------------------------------\n\n";

        double TotalBalance = clsBankClient::GetTotalBalance(vClass);

        cout << "Total Balance : " << TotalBalance;

        cout << "\n(" << clsUtil::NumberToText(TotalBalance) << ")" << endl;

    }

};

