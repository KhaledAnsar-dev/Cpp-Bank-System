#pragma once
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"


class clsCurrencyExchangeScreen : protected clsScreen
{
private:
    static short _ReadCurrencyExchangeMenueOption()
    {
        short Number = 0;
        cout << setw(37) << left << "" << "Please enter a number : ";
        Number = clsInputValidate::ReadShortNumberBetween(1, 5);
        return Number;
    }

    enum enCurrencyExchangeOptions
    {
        eCurrenciesList = 1, eFindCurrency = 2,
        eUpdateRate = 3, eCurrencyCalculator = 4,
        eMainMenu = 5
    };

    static void _BackToCurrencyExchangeScreen()
    {
        cout << "\nPress any key to go back" << endl;
        system("pause>0");
        ShowCurrencyExchangeMenu();
    }

    static void _ShowCurrenciesListScreen()
    {
        //cout << "Currencies List Screen will be here\n";
        clsCurrenciesListScreen::ShowCurrencyList();
    }

    static void _ShowFindCurrencyScreen()
    {
        //cout << "Find Currency Screen will be here\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        //cout << "Update Rate Screen will be here\n";
        clsUpdateRateScreen::ShowUpdateRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        //cout << "CurrencyCalculator Screen will be here\n";
        clsCurrencyCalculatorScreen::ShowCurrencyCalculator();
    }

    static void _PerformCurrencyExchangeOptions(enCurrencyExchangeOptions Option)
    {
        switch (Option)
        {
        case enCurrencyExchangeOptions::eCurrenciesList:
        {
            system("cls");
            _ShowCurrenciesListScreen();
            _BackToCurrencyExchangeScreen();
            break;
        }
        case enCurrencyExchangeOptions::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _BackToCurrencyExchangeScreen();
            break;
        }
        case enCurrencyExchangeOptions::eUpdateRate:
        {
            system("cls");
            _ShowUpdateRateScreen();
            _BackToCurrencyExchangeScreen();
            break;
        }
        case enCurrencyExchangeOptions::eCurrencyCalculator:
        {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _BackToCurrencyExchangeScreen();
            break;
        }
        case enCurrencyExchangeOptions::eMainMenu:
        {
            // Do nothing here the main menu screen will handle it
        }
        }
    }


public:
    static void ShowCurrencyExchangeMenu()
    {
        system("cls");

        _DrawHeaderScreen("\t   Currency Exhange Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t        Currency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Currencies List.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] CurrencyCalculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformCurrencyExchangeOptions((enCurrencyExchangeOptions)_ReadCurrencyExchangeMenueOption());
    }
};

