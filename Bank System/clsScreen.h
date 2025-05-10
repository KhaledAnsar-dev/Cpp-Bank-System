#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
using namespace std;
class clsScreen
{
protected:

	static void _DrawHeaderScreen(string Title , string SubTitle="")
	{
		cout << "\t\t\t\t\t" << "----------------------------------------";
		cout << "\n\n\t\t\t\t\t" << Title;
		if(SubTitle != "")
		{
			cout << "\n\t\t\t\t\t" << SubTitle;
		}
		cout << "\n\n\t\t\t\t\t----------------------------------------\n\n";

		cout << "\t\t\t\t\t" << "User : " << CurrentUser.UserName << "\n";
		cout << "\n\t\t\t\t\t" << "Date : " << clsDate::DateToString(clsDate()) << "\n\n";
	}

	static bool _CheckAccessRigths(clsUser::enMainMenuPermissions Permission)
	{
		if (!CurrentUser.CheckUserPermissions(Permission))
		{
			cout << "\t\t\t\t\t" << "----------------------------------------\n";
			cout << "\n\t\t\t\t\tAccess Denied, Please Conact Your Admin.";
			cout << "\n\n\t\t\t\t\t----------------------------------------\n\n";
			return false;
		}
		else
			return true;
	}
};

