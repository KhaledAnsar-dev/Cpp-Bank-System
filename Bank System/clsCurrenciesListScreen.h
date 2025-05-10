#pragma once
#include"clsScreen.h"
#include "clsCurrency.h"
#include<iomanip>

class clsCurrenciesListScreen : protected clsScreen
{
private:
    void static _PrintCurrencyRecordLine(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << Currency.GetCountry();
        cout << "| " << setw(20) << left << Currency.GetCurrencyCode();
        cout << "| " << setw(35) << left << Currency.GetCurrencyName();
        cout << "| " << setw(10) << left << Currency.GetRate();
    }

public:
    static void ShowCurrencyList()
    {
        vector <clsCurrency> vCurrency;

        vCurrency = clsCurrency::GetCurrencyList();

        string Title = "\t  Currency List Screen";
        string SubTitle = "\t   (" + to_string(vCurrency.size()) + ") Currencie(s)";

        _DrawHeaderScreen(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Country";
        cout << "| " << left << setw(20) << "Currency Code";
        cout << "| " << left << setw(35) << "Currency Name";
        cout << "| " << left << setw(10) << "Rate";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vCurrency.size() == 0)
            cout << "\t\t\t\tNo Currency Available in The System\n";

        for (clsCurrency Currency : vCurrency)
        {
            _PrintCurrencyRecordLine(Currency);
            cout << endl;
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

