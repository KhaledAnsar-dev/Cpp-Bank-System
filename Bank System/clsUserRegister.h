#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include"clsString.h"
#include "clsDate.h"

class clsUserRegister
{
private:
    string _DateAndTime;
    string _UserName;
    string _PassWord;
    short _Permissions;

    static clsUserRegister _ConvertLineToUserObject(string LineOfRecord, string Delim = "#//#")
    {

        vector <string> vData;
        vData = clsString::Split(LineOfRecord, Delim);

        return clsUserRegister(vData[0], vData[1], vData[2], stoi(vData[3]));

    }


    static vector <clsUserRegister> _LoadUserDataFromFile()
    {
        vector <clsUserRegister> vData;
        fstream ClientsRecord;

        ClientsRecord.open("LoginRegister.txt", ios::in);
        if (ClientsRecord.is_open())
        {
            string LineRecord;

            while (getline(ClientsRecord, LineRecord))
            {
                clsUserRegister Data = _ConvertLineToUserObject(LineRecord);
                vData.push_back(Data);
            }
            ClientsRecord.close();
        }

        return vData;
    }


public:
    clsUserRegister(string DateAndTime , string UserName , string PassWord , short Permissions)
    {
        _DateAndTime = DateAndTime;
        _UserName = UserName;
        _PassWord = PassWord;
        _Permissions = Permissions;
    }

    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _PassWord = Password;
    }

    string GetPassword()
    {
        return _PassWord;
    }

    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    short GetPermissions()
    {
        return _Permissions;
    }

    void SetPermissions(short Number)
    {
        _Permissions = Number;
    }

    __declspec(property(get = GetPermissions, put = SetPermissions)) short Permissions;

    string GetDateAndTime()
    {
        return _DateAndTime;
    }

    static vector <clsUserRegister> GetUsersRegisterList()
    {
        return _LoadUserDataFromFile();
    }
};

