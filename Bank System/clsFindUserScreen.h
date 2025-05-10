#pragma once
#include"clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "User Card : \n";
        cout << "------------------------\n";
        cout << "\nFirst Name   : " << User.FirstName;
        cout << "\nLast Name    : " << User.LastName;
        cout << "\nEmail        : " << User.Email;
        cout << "\nPhone        : " << User.Phone;
        cout << "\nUserName     : " << User.GetUserName();
        cout << "\nPassword      : " << User.GetPassword();
        cout << "\nPermissions  : " << User.GetPermissions();
        cout << "\n------------------------\n";
    }

public:
    static void ShowFindUserScreen()
    {

        _DrawHeaderScreen("\t\tFind User Screen");

        cout << "Please enter UserName : \n";

        string AccountNumber = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(AccountNumber))
        {
            cout << "!!! UserName ,is NOT found , choose another one : \n";
            AccountNumber = clsInputValidate::ReadString();
        }


        clsUser User1 = clsUser::Find(AccountNumber);

        if (!User1.IsEmpty())
            cout << "\nUserName found\n\n";

        else
            cout << "\nUserName Not found\n\n";

        _PrintUser(User1);

    }
};

