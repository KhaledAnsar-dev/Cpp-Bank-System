#pragma once
#include <iostream>
#include"clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{
private:

    static short _ReadManageUserMenueOption()
    {
        short Number = 0;
        cout << setw(38) << left << "" << "Please enter a number : ";
        Number = clsInputValidate::ReadShortNumberBetween(1, 6);
        return Number;
    }

    enum enManageUsersOptions
    {
        ListUsers = 1, AddUsers = 2, DeleteUsers = 3,
        UpdateUsers = 4, FindUsers = 5, UserMenuToMainMenu = 6
    };

    static void _BackToManageUsersScreen()
    {
        cout << "\nPress any key to go back" << endl;
        system("pause>0");
        ShowManageUsersMenuScreen();
    }

    static void _ShowAllUsersScreen()
    {
        //cout << "All users screen will be here\n";
        clsUsersListScreen::ShowUsersList();
    }

    static void _ShowAddUsersScreen()
    {
        //cout << "Add user screen will be here\n";
        clsAddNewUserScreen::ShowAddNewUser();
    }

    static void _ShowDeleteUsersScreen()
    {
        //cout << "Delete user screen will be here\n";
        clsDeleteUserScreen::ShowDeleteUser();
    }

    static void _ShowUpdateUsersScreen()
    {
        //cout << "Update user screen will be here\n";
        clsUpdateUserScreen::ShowUpdateUser();
    }

    static void _ShowFindUsersScreen()
    {
        //cout << "Find user screen will be here\n";
        clsFindUserScreen::ShowFindUserScreen();
    }


    static void _PerformManageUsersOptions(enManageUsersOptions Options)
    {
        switch (Options)
        {
        case enManageUsersOptions::ListUsers:
        {
            system("cls");
            _ShowAllUsersScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersOptions::AddUsers:
        {
            system("cls");
            _ShowAddUsersScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersOptions::DeleteUsers:
        {
            system("cls");
            _ShowDeleteUsersScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersOptions::UpdateUsers:
        {
            system("cls");
            _ShowUpdateUsersScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersOptions::FindUsers:
        {
            system("cls");
            _ShowFindUsersScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersOptions::UserMenuToMainMenu:
        {
            
        }
        }
    }


public:

    static void ShowManageUsersMenuScreen()
    {

        if (!_CheckAccessRigths(clsUser::enMainMenuPermissions::ManageUsers_))
        {
            return;
        }

        system("cls");

        _DrawHeaderScreen("\t    Manage Users Screen");
        cout << setw(38) << left << "" << "===========================================\n";
        cout << setw(38) << left << "" << "\t\tManageUsers Menue Screen\n";
        cout << setw(38) << left << "" << "===========================================\n";
        cout << setw(38) << left << "" << "\t[1] List Users.\n";
        cout << setw(38) << left << "" << "\t[2] Add New Users.\n";
        cout << setw(38) << left << "" << "\t[3] Delete Users.\n";
        cout << setw(38) << left << "" << "\t[4] Update Users Info.\n";
        cout << setw(38) << left << "" << "\t[5] Find Users.\n";
        cout << setw(38) << left << "" << "\t[6] MainMenu.\n";
        cout << setw(38) << left << "" << "===========================================\n";
        _PerformManageUsersOptions((enManageUsersOptions)_ReadManageUserMenueOption());


    }

};

