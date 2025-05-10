#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;
class clsCurrency : public clsScreen
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1};

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	double _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string LineOfRecord, string Delim = "#//#")
	{

		vector <string> vData;
		vData = clsString::Split(LineOfRecord, Delim);

		return clsCurrency(enMode::UpdateMode , vData[0], vData[1], vData[2], stod(vData[3]));

	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Data, string Seperator = "#//#")
	{
		string RecordLine = "";
		RecordLine += Data._Country + Seperator;
		RecordLine += Data._CurrencyCode + Seperator;
		RecordLine += Data._CurrencyName + Seperator;
		RecordLine += to_string(Data._Rate) + Seperator;


		return RecordLine;
	}

	static vector <clsCurrency> _LoadCurrencyDataFromFile()
	{
		vector <clsCurrency> vData;
		fstream ClientsRecord;

		ClientsRecord.open("Currencies.txt", ios::in);
		if (ClientsRecord.is_open())
		{
			string LineRecord;

			while (getline(ClientsRecord, LineRecord))
			{
				clsCurrency Data = _ConvertLineToCurrencyObject(LineRecord);
				vData.push_back(Data);
			}
			ClientsRecord.close();
		}

		return vData;
	}

	static void _SaveDataFromVectorToFile(vector <clsCurrency> vData)
	{
		fstream MyFile;
		string RecordLine = "";

		MyFile.open("Currencies.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsCurrency& ClassData : vData)
			{
					RecordLine = _ConvertCurrencyObjectToLine(ClassData);
					MyFile << RecordLine << endl;
			}
			MyFile.close();
		}
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode , "", "", "", 1);
	}

	void _Update()
	{
		vector <clsCurrency> vCurrency;

		vCurrency = _LoadCurrencyDataFromFile();

		for (clsCurrency& Currency : vCurrency)
		{
			if (Currency.GetCountry() == _Country)
			{
				Currency = *this;
				break;
			}
		}

		_SaveDataFromVectorToFile(vCurrency);
	}


public:

	clsCurrency(enMode Mode , string Country, string CurrencyCode, string CurrencyName, double Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	// Property Set-Get
	// Read Only

	string GetCountry()
	{
		return _Country;
	}

	string GetCurrencyCode()
	{
		return _CurrencyCode;
	}

	string GetCurrencyName()
	{
		return _CurrencyName;
	}

	double GetRate()
	{
		return _Rate;
	}


	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	// static Methodes 

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);


		vector <clsCurrency> vData;
		fstream ClientsRecord;

		ClientsRecord.open("Currencies.txt", ios::in);
		if (ClientsRecord.is_open())
		{
			string LineRecord = "";

			while (getline(ClientsRecord, LineRecord))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(LineRecord);
				if (clsString::UpperAllString(Currency.GetCountry()) == Country)
				{
					ClientsRecord.close();
					return Currency;
				}

				vData.push_back(Currency);
			}
			ClientsRecord.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		vector <clsCurrency> vData;
		fstream ClientsRecord;

		ClientsRecord.open("Currencies.txt", ios::in);
		if (ClientsRecord.is_open())
		{
			string LineRecord = "";

			while (getline(ClientsRecord, LineRecord))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(LineRecord);
				if (Currency.GetCurrencyCode() == CurrencyCode)
				{
					ClientsRecord.close();
					return Currency;
				}

				vData.push_back(Currency);
			}
			ClientsRecord.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string Code)
	{
		clsCurrency Currency = clsCurrency::FindByCode(Code);
		return (!Currency.IsEmpty());
	}

	static vector <clsCurrency> GetCurrencyList()
	{
		return _LoadCurrencyDataFromFile();
	}

	void UpdateRate(double NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	static clsCurrency GetUSDCurrency()
	{
		vector <clsCurrency> vCurrency = _LoadCurrencyDataFromFile();

		for (clsCurrency& Currency : vCurrency)
		{
			if (clsString::UpperAllString(Currency.GetCurrencyCode()) == "USD")
			{
				return Currency;
			}
		}
	}

	float ConvertToUSD(float Amount)
	{
		return Amount / GetRate();
	}

	float ConvertToOtherCurrencies(float Amount, clsCurrency To)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (clsString::UpperAllString(To.GetCurrencyCode()) == "USD")
		{
			return AmountInUSD;
		}

		return AmountInUSD * To.GetRate();
	}

};