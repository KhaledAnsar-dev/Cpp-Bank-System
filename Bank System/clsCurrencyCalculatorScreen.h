#pragma once
#include"clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
	static clsCurrency _GetCurrency(string Message)
	{
		string Code = "";
		cout << Message << endl;
		Code = clsInputValidate::ReadString();

		while(!clsCurrency::IsCurrencyExist(Code))
		{
			cout << "Can't found currency , try new one : \n";
			Code = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(Code);

		return Currency;

	}

	static void _PrintCurrency(clsCurrency Currency , string Message)
	{
		cout << "\n" << Message << Currency.GetCurrencyCode() << "\n";
		cout << "=======================\n";
		cout << "Country       : " << Currency.GetCountry() << endl;
		cout << "Currency Code : " << Currency.GetCurrencyCode() << endl;
		cout << "Currency Name : " << Currency.GetCurrencyName() << endl;
		cout << "Rate (/1$)    : " << Currency.GetRate() << endl;
		cout << "=======================\n";
	}

	static float _ReadAmount()
	{
		float Amount = 0;
		cout << "\nPlease enter Amount : \n";
		Amount = clsInputValidate::ReadDblNumber();

		return Amount;
	}

	static void _PrintCalculationResult(clsCurrency Currency1 , clsCurrency Currency2 , float Amount)
	{
		float AmountInUsd = 0 , AmountInCurrency2 = 0;

		_PrintCurrency(Currency1 , "Convert From ");

		cout << "\nConvert to USD : \n";
		AmountInUsd = Currency1.ConvertToUSD(Amount);
		cout << "\n" << Amount << " " << Currency1.GetCurrencyCode() << " = " << AmountInUsd << " " << "USD\n";

		if (Currency2.GetCurrencyCode() == "USD")
			return;


		_PrintCurrency(Currency2 , "Convert from USD To ");
		 AmountInCurrency2 = Currency1.ConvertToOtherCurrencies(Amount, Currency2);

		cout << "\n" << Amount << " " << Currency1.GetCurrencyCode() << " = " << AmountInCurrency2 << " " << Currency2.GetCurrencyCode();
	}

public:

	static void ShowCurrencyCalculator()
	{
		_DrawHeaderScreen("\t   Currency Calculator Screen");

		char Answer = 'Y';

		while(toupper(Answer) == 'Y')
		{


			clsCurrency Currency1 = _GetCurrency("Please enter a currency1 code\n");
			clsCurrency Currency2 = _GetCurrency("Please enter a currency2 code\n");

			float Amount = _ReadAmount();

			
			_PrintCalculationResult(Currency1, Currency2, Amount);

			cout << "\nDo you want to do more Calculations ?\n";
			cin >> Answer;
			system("cls");

		}


		

		
                 
		

	}

};

