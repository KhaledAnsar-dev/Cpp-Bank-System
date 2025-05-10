#pragma once
#include"clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen
{
private:
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


    static void _PrintUser(clsUser User)
    {
        cout << "User Card : \n";
        cout << "------------------------\n";
        cout << "\nFirst Name      : " << User.FirstName;
        cout << "\nLast Name       : " << User.LastName;
        cout << "\nEmail           : " << User.Email;
        cout << "\nPhone           : " << User.Phone;
        cout << "\nUserName        : " << User.UserName;
        cout << "\nPassword        : " << User.Password;
        cout << "\nPermissions     : " << User.GetPermissions();
        cout << "\n------------------------\n";
    }

public:
    static void ShowAddNewUser()
    {
        string UserName = "";

        _DrawHeaderScreen("\t   New User Screen");

        cout << "Please enter UserName : \n";
        UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(UserName))
        {
            cout << "!!! User Exist ,try another one : \n";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(User1);

        clsUser::enSaveResult SaveResult;

        SaveResult = User1.Save();


        switch (SaveResult)
        {
        case clsUser::svSucceeded:
        {
            cout << "\nAccount added Successfully : -)\n";
            _PrintUser(User1);
            break;
        }
        case clsUser::svFaildAccountNumberExist:
        {
            cout << "\nError , account was not saved because it's exist\n";
            break;
        }
        }




    }
};

