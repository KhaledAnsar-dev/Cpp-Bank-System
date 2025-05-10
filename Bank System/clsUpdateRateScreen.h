#pragma once
#include"clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateRateScreen : protected clsScreen
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

	static double _ReadRate()
	{
		cout << "Please enter new rate : \n";
		double NewRate = 0;
		NewRate = clsInputValidate::ReadDblNumber();

		return NewRate;
	}


public:
	static void ShowUpdateRateScreen()
	{
		_DrawHeaderScreen("\t   Update Rate Screen");

		cout << "Please enter a currency code : \n";

		string Code = "";

		Code = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(Code))
		{
			cout << "Please enter another currency code : \n";

			Code = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(Code);

		_PrintCurrency(Currency);

		char Answer;

		cout << "Are you sure you want to update currency rate y/ n\n";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{

			cout << "Update Rate :\n";
			cout << "=============\n";
			
			Currency.UpdateRate(_ReadRate());

			cout << "\n=============\n";


			cout << "\nCurrency rate updated successfully\n";

			_PrintCurrency(Currency);
		}

	}
};

