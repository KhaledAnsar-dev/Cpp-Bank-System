#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include "clsPerson.h"
#include"clsString.h"
#include "clsDate.h"

using namespace std;

class clsBankClient : public clsPerson
{

private:
    enum enMode{EmptyMode = 0 , UpdateMode = 1 , NewMode = 2};
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkForDelete = false;

    struct stTransferLogRegister;

    static stTransferLogRegister _ConvertLineToTransferLogRecord(string LineOfRecord, string Delim = "#//#")
    {

        vector <string> vData;
        vData = clsString::Split(LineOfRecord, Delim);

        stTransferLogRegister DataRecord;

        DataRecord.DateAndTime = vData[0];
        DataRecord.SourceAccountNumber = vData[1];
        DataRecord.DestinationAccountNumber = vData[2];
        DataRecord.Amount = stod(vData[3]);
        DataRecord.SourceAccountBalance = stod(vData[4]);
        DataRecord.DestinationAccountBalance = stod(vData[5]);
        DataRecord.UserName = vData[6];

        return DataRecord;
    }

    static clsBankClient _ConvertLineToClientObject(string LineOfRecord, string Delim = "#//#")
    {

        vector <string> vData ;
        vData = clsString::Split(LineOfRecord, Delim);

        return clsBankClient(enMode::UpdateMode , vData[0], vData[1], vData[2], vData[3], vData[4], vData[5], stod(vData[6]));

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);

    }

    static string _ConvertClientObjectToLine(clsBankClient Data, string Seperator = "#//#")
    {
        string RecordData = "";
        RecordData += Data.FirstName + Seperator;
        RecordData += Data.LastName + Seperator;
        RecordData += Data.Email + Seperator;
        RecordData += Data.Phone + Seperator;
        RecordData += Data._AccountNumber + Seperator;
        RecordData += Data._PinCode + Seperator;
        RecordData += to_string(Data._AccountBalance);

        return RecordData;
    }

    static vector <clsBankClient> _LoadClientsDataFromFile()
    {
        vector <clsBankClient> vData;
        fstream ClientsRecord;

        ClientsRecord.open("Clients.txt", ios::in);
        if (ClientsRecord.is_open())
        {
            string LineRecord;
            
            while (getline(ClientsRecord, LineRecord))
            {
                clsBankClient Data = _ConvertLineToClientObject(LineRecord);
                vData.push_back(Data);
            }
            ClientsRecord.close();
        }

        return vData;
    }

    static void _SaveDataFromVectorToFile(vector <clsBankClient> vData)
    {
        fstream MyFile;
        string RecordLine = "";

        MyFile.open("Clients.txt", ios::out);
        if (MyFile.is_open())
        {
            for (clsBankClient& ClassData : vData)
            {
                if(ClassData._MarkForDelete != true)
                {
                    RecordLine = _ConvertClientObjectToLine(ClassData);
                    MyFile << RecordLine << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& Client : _vClients)
        {
            if (Client.GetAccountNumber() == GetAccountNumber())
            {
                Client = *this;
                break;
            }
        }

        _SaveDataFromVectorToFile(_vClients);
    }

    void _AddDataLineToFile( string DataLine)
    {
        fstream ClientsRecord;

        ClientsRecord.open("Clients.txt", ios::out | ios::app);
        if (ClientsRecord.is_open())
        {
            ClientsRecord << DataLine << endl;
            ClientsRecord.close();
        }
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    string _PrepareTransferLog(double Amount, clsBankClient DestinationClient, string UserName ,  string Seperator = "#//#")
    {
        string TransferLogRecord = "";

        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += GetAccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.GetAccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        TransferLogRecord += UserName;

        return TransferLogRecord;

    }

    void _RegisterTransferLog(double Amount, clsBankClient DestinationClient , string UserName)
    {
        string RecordLine = _PrepareTransferLog(Amount, DestinationClient , UserName);
        fstream ClientsRecord;

        ClientsRecord.open("TransferLog.txt", ios::out | ios::app);
        if (ClientsRecord.is_open())
        {
            ClientsRecord << RecordLine << endl;
            ClientsRecord.close();
        }
    }

    
public:


    clsBankClient(enMode Mode , string FirstName,string LastName, string Email, string Phone , string AccountNumber, string PinCode, float AccountBalance) : clsPerson(FirstName , LastName , Email , Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    struct stTransferLogRegister
    {
        string DateAndTime = "";
        string SourceAccountNumber = "";
        string DestinationAccountNumber = "";
        double Amount = 0;
        double SourceAccountBalance = 0;
        double DestinationAccountBalance = 0;
        string UserName = "";
    };

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    //Property set/get

    // AccountNumber (Read Only)
    string GetAccountNumber()
    {
        return _AccountNumber;
    }
   

    // PinCode
    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }

    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;


    // AccountBalance
    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }

    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    
    // No UI Related Code Inside Object

    /*void Print()
    {
        cout << "Client Card : \n";
        cout << "------------------------\n";
        cout << "\nFirst Name      : " << FirstName;
        cout << "\nLast Name       : " << LastName;
        cout << "\nEmail           : " << Email;
        cout << "\nPhone           : " << Phone;
        cout << "\nAccount Number  : " << _AccountNumber;
        cout << "\nPassword        : " << _PinCode;
        cout << "\nAccount Balance : " << _AccountBalance;
        cout << "\n------------------------\n";
    }*/

    static clsBankClient Find(string AccountNumber)
    {
        vector <clsBankClient> vData;
        fstream ClientsRecord;

        ClientsRecord.open("Clients.txt", ios::in);
        if (ClientsRecord.is_open())
        {
            string LineRecord= "";
            
            while (getline(ClientsRecord, LineRecord))
            {
                clsBankClient Client = _ConvertLineToClientObject(LineRecord);
                if (Client._AccountNumber == AccountNumber)
                {
                    ClientsRecord.close();
                    return Client;
                }

                vData.push_back(Client);
            }
            ClientsRecord.close();
        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        vector <clsBankClient> vData;
        fstream ClientsRecord;

        ClientsRecord.open("Clients.txt", ios::in);
        if (ClientsRecord.is_open())
        {
            string LineRecord = "";

            while (getline(ClientsRecord, LineRecord))
            {
                clsBankClient Client = _ConvertLineToClientObject(LineRecord);
                if (Client._AccountNumber == AccountNumber && Client.PinCode == PinCode)
                {
                    ClientsRecord.close();
                    return Client;
                }

                vData.push_back(Client);
            }
            ClientsRecord.close();
        }

        return _GetEmptyClientObject();
    }

    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        return (!Client.IsEmpty());
    }

    enum enSaveResult {svFaildEmptyObject = 0 , svSucceeded = 1 , svFaildAccountNumberExist = 2 };

    enSaveResult Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if(IsEmpty())
            {
                return enSaveResult::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResult::svSucceeded;
        }

        case enMode::NewMode:
        {
            if (IsClientExist(_AccountNumber))
                return enSaveResult::svFaildAccountNumberExist;
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResult::svSucceeded;
            }
        }
        
        }

    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::NewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete()
    {
        vector <clsBankClient> vData;
        vData = _LoadClientsDataFromFile();

        for (clsBankClient& Client : vData)
        {
            if (Client.GetAccountNumber() == GetAccountNumber())
            {
                Client._MarkForDelete = true;
                break;
            }

        }
        _SaveDataFromVectorToFile(vData);
        *this = _GetEmptyClientObject();
        return true;
    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static float GetTotalBalance(vector <clsBankClient> vClass)
    {
        double TotalBalance = 0;

        for (clsBankClient Object : vClass)
        {
            TotalBalance += Object.AccountBalance;
        }
        return TotalBalance;
    }

    void Deposit(double Amount)
    {

        _AccountBalance += Amount;
        Save();
    }

    bool WithDraw(double Amount)
    {

        if(Amount > AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
    }

    bool Transfer(double Amount, clsBankClient& DestinationClient , string UserName)
    {
        if (Amount > AccountBalance)
            return false;
        else
        {
            this->WithDraw(Amount);
            DestinationClient.Deposit(Amount);

            // Logging
            _RegisterTransferLog(Amount, DestinationClient, UserName);

            return true;
        }
    }

    static vector <stTransferLogRegister> GetTransferLogList()
    {
        vector <stTransferLogRegister> vData;
        fstream ClientsRecord;

        ClientsRecord.open("TransferLog.txt", ios::in);
        if (ClientsRecord.is_open())
        {
            string LineRecord;

            while (getline(ClientsRecord, LineRecord))
            {
                stTransferLogRegister DataRecord = _ConvertLineToTransferLogRecord(LineRecord);
                vData.push_back(DataRecord);
            }
            ClientsRecord.close();
        }

        return vData;
    }

};