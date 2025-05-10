#pragma once
#include"clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
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
    static void ShowDeleteUser()
    {
        string AccountNumber = "";

        _DrawHeaderScreen("\t   Delete User Screen");

        cout << "Please enter UserName : \n";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(AccountNumber))
        {
            cout << "!!! UserName ,is NOT found , choose another one : \n";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(AccountNumber);

        _PrintUser(User1);

        char Answer = -'n';
        cout << "Are you sure you want delete this element : y/n ?\n";
        cin >> Answer;


        if (toupper(Answer) == 'Y')
        {
            if (User1.Delete())
            {
                cout << "\nUser deleted Successfully : -)\n";

                _PrintUser(User1);
            }
            else
                cout << "\nError , user was not deleted\n";
        }


    }

};

