#pragma once
#include"clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:
    static void _PrintUserRecordLine(clsUser::stLoginRegisterRecord User)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << User.DateAndTime;
        cout << "| " << setw(20) << left << User.UserName;
        cout << "| " << setw(20) << left << User.PassWord;
        cout << "| " << setw(10) << left << User.Permissions;
    }

public:
    static  void ShowRegisterLoginList()
    {
        if (!_CheckAccessRigths(clsUser::enMainMenuPermissions::LoginRegister_))
        {
            return;
        }
        vector <clsUser::stLoginRegisterRecord> vData;
        vData = clsUser::GetUsersRegisterList();

        string Title = "\t    Register Login List Screen";
        string SubTitle = "\t\t(" + to_string(vData.size()) + ") Users";

        _DrawHeaderScreen(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date and Time";
        cout << "| " << left << setw(20) << "Username";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permission";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vData.size() == 0)
            cout << "\t\t\t\tNo Clints Available in The System\n";
        else
        {
            for (clsUser::stLoginRegisterRecord& User : vData)
            {
                _PrintUserRecordLine(User);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};

