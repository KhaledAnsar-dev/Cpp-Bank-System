#pragma once
#include <iostream>
#include <iomanip>
#include"clsScreen.h"
#include"clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionScreen : protected clsScreen
{
private:
    static short _ReadTransactionMenueOption()
    {
        short Number = 0;
        cout << setw(37) << left << "" << "Please enter a number : ";
        Number = clsInputValidate::ReadShortNumberBetween(1, 6);
        return Number;
    }

    enum enTransactionsOptions
    {
        Deposit = 1, WithDraw = 2,
        TotalBalance = 3, Transfer = 4, 
        TransferLog = 5, MainMenu = 6
    };

    static void _BackToTransactionsScreen()
    {
        cout << "\nPress any key to go back" << endl;
        system("pause>0");
        ShowTransactionsMenu();
    }
    

    static void _ShowDepositScreen()
    {
        //cout << "Deposit Screen will be here\n";
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithDrawScreen()
    {
        //cout << "Withdraw Screen will be here\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalanceScreen()
    {
        //cout << "Total balance Screen will be here\n";
        clsTotalBalanceScreen::ShowTotalBalanceList();
    }

    static void _ShowTransferScreen()
    {
        //cout << "Transfer Screen will be here\n";
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen()
    {
        //cout << "Transfer Screen will be here\n";
        clsTransferLogScreen::ShowTransferLoginList();
    }



    static void _PerformTransactionsOptions(enTransactionsOptions Option)
    {
        switch (Option)
        {
        case enTransactionsOptions::Deposit:
        {
            system("cls");
            _ShowDepositScreen();
            _BackToTransactionsScreen();
            break;
        }
        case enTransactionsOptions::WithDraw:
        {
            system("cls");
            _ShowWithDrawScreen();
            _BackToTransactionsScreen();
            break;
        }
        case enTransactionsOptions::TotalBalance:
        {
            system("cls");
            _ShowTotalBalanceScreen();
            _BackToTransactionsScreen();
            break;
        }
        case enTransactionsOptions::Transfer:
        {
            system("cls");
            _ShowTransferScreen();
            _BackToTransactionsScreen();
            break;
        }
        case enTransactionsOptions::TransferLog:
        {
            system("cls");
            _ShowTransferLogScreen();
            _BackToTransactionsScreen();
            break;
        }
        case enTransactionsOptions::MainMenu:
        {
            // Do nothing here the main menu screen will handle it
        }
        }
    }

public:
    static void ShowTransactionsMenu()
    {
        if (!_CheckAccessRigths(clsUser::enMainMenuPermissions::Transactions_))
        {
            return;
        }

        system("cls");

        _DrawHeaderScreen("\t   Transaction Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t      Transactions Menue Screen\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] WithDraw.\n";
        cout << setw(37) << left << "" << "\t[3] TotalBAlance.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformTransactionsOptions((enTransactionsOptions)_ReadTransactionMenueOption());
    }
};

