#pragma once
#include"clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUsersListScreen : protected clsScreen
{
private:
    static void _PrintUserRecordLine(clsUser User)
    {
        cout << setw(8) << left << "" << "| " << setw(12) << left << User.GetUserName();
        cout << "| " << setw(25) << left << User.GetFullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.GetPermissions();
    }

public:
	static  void ShowUsersList()
    {

        vector <clsUser> vData;
        vData = clsUser::GetUsersList();
        string Title = "\t    Users List Screen";
        string SubTitle = "\t\t(" + to_string(vData.size()) + ") Users";

        _DrawHeaderScreen(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vData.size() == 0)
            cout << "\t\t\t\tNo Clints Available in The System\n";
        else
        {
            for (clsUser& User : vData)
            {
                _PrintUserRecordLine(User);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};

