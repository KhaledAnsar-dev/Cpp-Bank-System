#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{
private: 
    static bool _Login()
    {
        string Username = "", Password = "";
        bool LoginFailed = false;
        short Count = 3;
        do
        {
            if (Count == 1)
            {
                cout << "You are locked after 3 faild trails" << endl;
                return false;
            }

            if (LoginFailed)
            {
                cout << "\nInvalid UserName/PassWord!\n";

                Count--;
                cout << "You have [" << Count << "] trails to login\n";
            }

            


            cout << "Enter a username : \n";
            Username = clsInputValidate::ReadString();

            cout << "Enter a Password : \n";
            Password = clsInputValidate::ReadString();

            CurrentUser = clsUser::Find(Username, Password);


            LoginFailed = CurrentUser.IsEmpty();

        } while (LoginFailed);

        CurrentUser.RegisterLogin();

        clsMainScreen::ShowMainMenu();
        return true;
    }
   
public:
    static bool ShowLogInMenu()
    {
        system("cls");

        _DrawHeaderScreen("\t    Login Menue Screen");
        
        return _Login();
    }

};

