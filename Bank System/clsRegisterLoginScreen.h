#pragma once
#include"clsScreen.h"
#include "clsUserRegister.h"
#include "clsInputValidate.h"

class clsRegisterLoginScreen : protected clsScreen
{
private:
    static void _PrintUserRecordLine(clsUserRegister User)
    {
        cout << setw(8) << left << "" << "| " << setw(30) << left << User.GetDateAndTime();
        cout << "| " << setw(15) << left << User.UserName;
        cout << "| " << setw(15) << left << User.Password;
        cout << "| " << setw(15) << left << User.GetPermissions();
    }

public:
    static  void ShowUsersRegisterList()
    {

        vector <clsUserRegister> vData;
        vData = clsUserRegister::GetUsersRegisterList();
        string Title = "\tUsers Register List Screen";
        string SubTitle = "\t\t(" + to_string(vData.size()) + ") Users";

        _DrawHeaderScreen(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Date and Time";
        cout << "| " << left << setw(15) << "Username";
        cout << "| " << left << setw(15) << "Password";
        cout << "| " << left << setw(15) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________\n" << endl;

        if (vData.size() == 0)
            cout << "\t\t\t\tNo Clints Available in The System\n";
        else
        {
            for (clsUserRegister& UserRegister : vData)
            {
                _PrintUserRecordLine(UserRegister);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________\n" << endl;
    }

};
