#pragma once
#include"clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card : \n";
		cout << "=======================\n";
		cout << "Country       : " << Currency.GetCountry() << endl;
		cout << "Currency Code : " << Currency.GetCurrencyCode() << endl;
		cout << "Currency Name : " << Currency.GetCurrencyName() << endl;
		cout << "Rate (/1$)    : " << Currency.GetRate() << endl;
		cout << "=======================\n";
	}

	static void _ShowResult(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			_PrintCurrency(Currency);
		}
		else
			cout << "\nCan't found currency\n";

	}

public:
	static void ShowFindCurrencyScreen()
	{
		_DrawHeaderScreen("\t   Find Currency Screen");

		cout << "Find by : \n";
		cout << "\t 1 - Country\n";
		cout << "\t 2 - Code\n";

		short Answer;
		Answer = clsInputValidate::ReadShortNumberBetween(1, 2);
		
		if (Answer == 1)
		{
			cout << "Please enter a country : \n";
			string Country = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResult(Currency);
		}
		else
		{
			cout << "Please enter a currency code : \n";
			string Country = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCode(Country);
			_ShowResult(Currency);
		}
	}


};

