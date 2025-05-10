#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include "clsPerson.h"
#include "clsBankClient.h"
#include"clsString.h"
#include "clsDate.h"
#include "clsUtil.h"

class clsUser : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, NewMode = 2 };
    enMode _Mode;

    string _UserName;
    string _PassWord;
    short _Permissions;
    string _DateAndTime;
    bool _MarkedForDelete = false;

    struct stLoginRegisterRecord;

    static stLoginRegisterRecord _ConvertRegisterLoginLineToRecord(string LineOfRecord, string Delim = "#//#")
    {

        vector <string> LoginRegisterDataLine;
        LoginRegisterDataLine = clsString::Split(LineOfRecord, Delim);

        stLoginRegisterRecord RecordRegister;

        RecordRegister.DateAndTime = LoginRegisterDataLine[0];
        RecordRegister.UserName = LoginRegisterDataLine[1];
        RecordRegister.PassWord = LoginRegisterDataLine[2];
        RecordRegister.Permissions = stoi(LoginRegisterDataLine[3]);



        return RecordRegister;

    }

    static clsUser _ConvertLineToUserObject(string LineOfRecord, string Delim = "#//#")
    {

        vector <string> vData;
        vData = clsString::Split(LineOfRecord, Delim);

        return clsUser(enMode::UpdateMode, vData[0], vData[1], vData[2], vData[3], vData[4], clsUtil::Decrypt(vData[5]), stoi(vData[6]));

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "",1);

    }

    static string _ConvertUserObjectToLine(clsUser Data, string Seperator = "#//#")
    {
        string RecordData = "";
        RecordData += Data.FirstName + Seperator;
        RecordData += Data.LastName + Seperator;
        RecordData += Data.Email + Seperator;
        RecordData += Data.Phone + Seperator;
        RecordData += Data._UserName + Seperator;
        RecordData += clsUtil::Encrypt(Data._PassWord) + Seperator;
        RecordData += to_string(Data._Permissions);


        return RecordData;
    }

    static vector <clsUser> _LoadUserDataFromFile()
    {
        vector <clsUser> vData;
        fstream ClientsRecord;

        ClientsRecord.open("Users.txt", ios::in);
        if (ClientsRecord.is_open())
        {
            string LineRecord;

            while (getline(ClientsRecord, LineRecord))
            {
                clsUser Data = _ConvertLineToUserObject(LineRecord);
                vData.push_back(Data);
            }
            ClientsRecord.close();
        }

        return vData;
    }

    static void _SaveDataFromVectorToFile(vector <clsUser> vData)
    {
        fstream MyFile;
        string RecordLine = "";

        MyFile.open("Users.txt", ios::out);
        if (MyFile.is_open())
        {
            for (clsUser& ClassData : vData)
            {

                if (ClassData._MarkedForDelete != true)
                {
                    RecordLine = _ConvertUserObjectToLine(ClassData);
                    MyFile << RecordLine << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector <clsUser> _vClients;
        _vClients = _LoadUserDataFromFile();

        for (clsUser& Client : _vClients)
        {

            if (Client.GetUserName() == GetUserName())
            {
                Client = *this;
                break;
            }
        }

        _SaveDataFromVectorToFile(_vClients);
    }

    void _AddDataLineToFile(string DataLine)
    {
        fstream ClientsRecord;

        ClientsRecord.open("Users.txt", ios::out | ios::app);
        if (ClientsRecord.is_open())
        {
            ClientsRecord << DataLine << endl;
            ClientsRecord.close();
        }
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    }

    string _PrepareLoginRegister(string Seperator = "#//#")
    {
        string RecordData = "";
        RecordData += clsDate::GetSystemDateTimeString() + Seperator;
        RecordData += UserName + Seperator;
        RecordData += clsUtil::Encrypt(Password) +Seperator;
        RecordData += to_string(Permissions);
        return RecordData;
    }

    string _PrepareTransferLog(double Amount, clsBankClient SourceClient, clsBankClient DestinationClient,string Seperator = "#//#")
    {
        string RecordLine = "";

        RecordLine += clsDate::GetSystemDateTimeString() + Seperator;
        RecordLine += SourceClient.GetAccountNumber() + Seperator;
        RecordLine += DestinationClient.GetAccountNumber() + Seperator;
        RecordLine += to_string(Amount) + Seperator;
        RecordLine += to_string(SourceClient.AccountBalance) + Seperator;
        RecordLine += to_string(DestinationClient.AccountBalance) + Seperator;
        RecordLine += UserName;

        return RecordLine;

    }



public:
    enum enMainMenuPermissions
    {
        AllOptions = -1, ClientList_ = 1, AddClients_ = 2, DeleteClients_ = 4,
        UpdateClients_ = 8, FindClients_ = 16, Transactions_ = 32,
        ManageUsers_ = 64 , LoginRegister_ = 128
    };

    
    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string PassWord, short Permissions) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _PassWord = PassWord;
        _Permissions = Permissions;
    }

    struct stLoginRegisterRecord
    {
        string DateAndTime;
        string UserName;
        string PassWord;
        short Permissions;

    };

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }


    // Property Set and Get
    
    // AccountNumber (Read Only)
    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    // PinCode
    void SetPassword(string Password)
    {
        _PassWord = Password;
    }

    string GetPassword()
    {
        return _PassWord;
    }

    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    // MarkedForDelete
    bool GetMarkedForDelete()
    {
        return _MarkedForDelete;
    }

    // Permissions

    short GetPermissions()
    {
        return _Permissions;
    }

    void SetPermissions(short Number)
    {
        _Permissions = Number;
    }

    __declspec(property(get = GetPermissions, put = SetPermissions)) short Permissions;


    static clsUser Find(string AccountNumber)
    {
        vector <clsUser> vData;
        fstream ClientsRecord;

        ClientsRecord.open("Users.txt", ios::in);
        if (ClientsRecord.is_open())
        {
            string LineRecord = "";

            while (getline(ClientsRecord, LineRecord))
            {
                clsUser Client = _ConvertLineToUserObject(LineRecord);
                if (Client.GetUserName() == AccountNumber)
                {
                    ClientsRecord.close();
                    return Client;
                }

                vData.push_back(Client);
            }
            ClientsRecord.close();
        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string PinCode)
    {
        vector <clsUser> vData;
        fstream ClientsRecord;

        ClientsRecord.open("Users.txt", ios::in);
        if (ClientsRecord.is_open())
        {
            string LineRecord = "";

            while (getline(ClientsRecord, LineRecord))
            {
                clsUser Client = _ConvertLineToUserObject(LineRecord);
                if (Client.GetUserName() == UserName && Client.Password == PinCode)
                {
                    ClientsRecord.close();
                    return Client;
                }

                vData.push_back(Client);
            }
            ClientsRecord.close();
        }

        return _GetEmptyUserObject();
    }

    static bool IsUserExist(string UserName)
    {
        clsUser Client = clsUser::Find(UserName);
        return (!Client.IsEmpty());
    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::NewMode, "", "", "", "", UserName, "" , 1);
    }

    enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExist = 2 };

    enSaveResult Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
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
            if (IsUserExist(_UserName))
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

    bool Delete()
    {
        vector <clsUser> vData;
        vData = _LoadUserDataFromFile();

        for (clsUser& User : vData)
        {
            if (User.GetUserName() == GetUserName())
            {
                User._MarkedForDelete = true;
                break;
            }

        }
        _SaveDataFromVectorToFile(vData);
        *this = _GetEmptyUserObject();
        return true;
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUserDataFromFile();
    }

    bool CheckUserPermissions(enMainMenuPermissions Permission)
    {
        if (this->Permissions == enMainMenuPermissions::AllOptions)
            return true;
        ((Permission & this->Permissions) == Permission) ? true : false;
    }

    void RegisterLogin()
    {
        string RecordLine = _PrepareLoginRegister();
        fstream ClientsRecord;

        ClientsRecord.open("LoginRegister.txt", ios::out | ios::app);
        if (ClientsRecord.is_open())
        {
            ClientsRecord << RecordLine << endl;
            ClientsRecord.close();
        }
    }

    static vector <stLoginRegisterRecord> GetUsersRegisterList()
    {
        vector <stLoginRegisterRecord> vData;
        fstream ClientsRecord;
        
        ClientsRecord.open("LoginRegister.txt", ios::in);
        if (ClientsRecord.is_open())
        {
            string LineRecord;

            while (getline(ClientsRecord, LineRecord))
            {
                stLoginRegisterRecord Data = _ConvertRegisterLoginLineToRecord(LineRecord);
                vData.push_back(Data);
            }
            ClientsRecord.close();
        }

        return vData;
    }


};

