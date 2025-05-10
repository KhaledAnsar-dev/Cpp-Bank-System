#pragma once
#include"clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen
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

    static void _ReadUserInfo(clsUser& User)
    {
        bool GiveFullAccess = false;

        cout << "Enter a first name : \n";
        User.FirstName = clsInputValidate::ReadString();

        cout << "Enter a last name : \n";
        User.LastName = clsInputValidate::ReadString();

        cout << "Enter an email : \n";
        User.Email = clsInputValidate::ReadString();

        cout << "Enter a phone : \n";
        User.Phone = clsInputValidate::ReadString();

        cout << "Enter a password : \n";
        User.Password = clsInputValidate::ReadString();

        User.Permissions = _ReadPermissions();
    }

    static short _ReadPermissions()
    {
        char Answer = 'Y';

        short Permissions = 0;
        cout << "Do you want to give full access?\n";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
            return -1;

        else
        {
            cout << "Give Access to :?\n";

            cout << "Show Clients List?\n";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permissions += clsUser::enMainMenuPermissions::ClientList_;

            cout << "Add Clients?\n";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permissions += clsUser::enMainMenuPermissions::AddClients_;

            cout << "Delete Clients?\n";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permissions += clsUser::enMainMenuPermissions::DeleteClients_;

            cout << "Update Clients?\n";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permissions += clsUser::enMainMenuPermissions::UpdateClients_;

            cout << "Find Clients?\n";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permissions += clsUser::enMainMenuPermissions::FindClients_;

            cout << "Transactions Clients?\n";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permissions += clsUser::enMainMenuPermissions::Transactions_;

            cout << "Manage Users?\n";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permissions += clsUser::enMainMenuPermissions::ManageUsers_;

            cout << "Login Register?\n";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
                Permissions += clsUser::enMainMenuPermissions::LoginRegister_;


            return Permissions;
        }
    }
public:
    static void ShowUpdateUser()
    {
        string AccountNumber = "";

        _DrawHeaderScreen("\t   Update User Screen");


        cout << "Please enter UserName : \n";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(AccountNumber))
        {
            cout << "!!! UserName,is NOT found , choose another one : \n";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsUser Client1 = clsUser::Find(AccountNumber);

        _PrintUser(Client1);

        char Answer = -'n';
        cout << "Are you sure you want update this element : y/n ?\n";
        cin >> Answer;


        if (toupper(Answer) == 'Y')
        {

            cout << "\n Update Data : \n";
            cout << "----------------------\n";

            _ReadUserInfo(Client1);
            clsUser::enSaveResult SaveResult;

            SaveResult = Client1.Save();


            switch (SaveResult)
            {
            case clsUser::svSucceeded:
            {
                cout << "\nAccount updated Successfully : -)\n";
                _PrintUser(Client1);
                break;
            }
            case clsUser::svFaildEmptyObject:
            {
                cout << "\nError , account was not saved because it's empty\n";
                break;
            }
            }
        }




    }
};

