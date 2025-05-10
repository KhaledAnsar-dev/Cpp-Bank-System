#pragma once
#include <iostream>
#include"clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClient.h"
#include "clsFindClientScreen.h"
#include"clsTransactionScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeScreen.h"


class clsMainScreen : protected clsScreen
{
private:

    static short _ReadMainMenueOption()
    {
        short Number = 0;
        cout << setw(37) << left << "" << "Please enter a number : ";
        Number = clsInputValidate::ReadShortNumberBetween(1, 10);
        return Number;
    }

    enum enMainOptions
    {
        eShowClients = 1, eAddClients = 2, eDeleteClints = 3,
        eUpdateClients = 4, eFindClints = 5, eTransactions = 6,
        eManageUsers = 7 , eLoginRegister = 8 , eCurrencyExchange = 9,
        eLogOut = 10
    };

    static void _GoBackToMainMenue()
    {
        cout << "\nPress any key to go back" << endl;
        system("pause>0");
        ShowMainMenu();
    }

    static void _ShowAllClientsScreen()
    {
        //cout << "Client list screen will be here...\n";
        clsClientListScreen::ShowClientList();
  
    }

    static void _ShowAddClientsScreen()
    {
        //cout << "Add client screen will be here...\n";
        clsAddNewClientScreen::ShowAddNewClient();        
    }
    
    static void _ShowDeleteClientsScreen()
    {
        //cout << "Delete client screen will be here...\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }
    
    static void _ShowUpdateClientsScreen()
    {
        //cout << "Update client screen will be here...\n";
        clsUpdateClient::ShowUpdateClientScreen();
    }
    
    static void _ShowFindClientsScreen()
    {
        //cout << "Find client screen will be here...\n";
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenu()
    {
        //cout << "Transaction screen will be here...\n";
        clsTransactionScreen::ShowTransactionsMenu();
    }

    static void _ShowManageUsersMenu()
    {
        //cout << "Manage screen will be here...\n";
        clsManageUsersScreen::ShowManageUsersMenuScreen();
    }

    static void _ShowCurrencyExchangeMenu()
    {
        clsCurrencyExchangeScreen::ShowCurrencyExchangeMenu();
    }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");
    }

    static void _ShowLoginRegisterScreen()
    {
        //cout << "Login Register screen will be here...\n";
        clsLoginRegisterScreen::ShowRegisterLoginList();
        
    }

    
    static void _PerformMainMenuOptions(enMainOptions Option)
    {
        switch (Option)
        {
        case enMainOptions::eShowClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainOptions::eAddClients:
        {
            system("cls");
            _ShowAddClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainOptions::eDeleteClints:
        {
            system("cls");
            _ShowDeleteClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainOptions::eUpdateClients:
        {
            system("cls");
            _ShowUpdateClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainOptions::eFindClints:
        {
            system("cls");
            _ShowFindClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainOptions::eTransactions:
        {
            system("cls");
            _ShowTransactionsMenu();
            _GoBackToMainMenue();
            break;
        }
        case enMainOptions::eManageUsers:
        {
            system("cls");
            _ShowManageUsersMenu();
            _GoBackToMainMenue();
            break;
        }
        case enMainOptions::eLoginRegister:
        {
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainOptions::eCurrencyExchange:
        {
            system("cls");
            _ShowCurrencyExchangeMenu();
            _GoBackToMainMenue();
            break;
        }
        case enMainOptions::eLogOut:
        {
            system("cls");
            _Logout();
            break;
        }

        }

    }

public:

    static void ShowMainMenu()
    {
        system("cls");
        _DrawHeaderScreen("\t\tMain Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] CurrencyExchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformMainMenuOptions((enMainOptions)_ReadMainMenueOption());


    }
};

