#pragma once
#include"clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsTransferLogScreen : protected clsScreen
{
private:
    static void _PrintOpperationRecordLine(clsBankClient::stTransferLogRegister TransferRegister)
    {
        cout << setw(8) << left << "" << "| " << setw(22) << left << TransferRegister.DateAndTime;
        cout << "| " << setw(12) << left << TransferRegister.SourceAccountNumber;
        cout << "| " << setw(12) << left << TransferRegister.DestinationAccountNumber;
        cout << "| " << setw(12) << left << TransferRegister.Amount;
        cout << "| " << setw(12) << left << TransferRegister.SourceAccountBalance;
        cout << "| " << setw(12) << left << TransferRegister.DestinationAccountBalance;
        cout << "| " << setw(12) << left << TransferRegister.UserName;
    }

public:
    static  void ShowTransferLoginList()
    {

        vector <clsBankClient::stTransferLogRegister> vData;
        vData = clsBankClient::GetTransferLogList();

        string Title = "\t    Transfer Loggin List Screen";
        string SubTitle = "\t\t(" + to_string(vData.size()) + ") Users";

        _DrawHeaderScreen(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(22) << "Date and Time";
        cout << "| " << left << setw(12) << "S.Account";
        cout << "| " << left << setw(12) << "D.Account";
        cout << "| " << left << setw(12) << "Amount";
        cout << "| " << left << setw(12) << "S.Balance";
        cout << "| " << left << setw(12) << "D.Balance";
        cout << "| " << left << setw(12) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vData.size() == 0)
            cout << "\t\t\t\tNo Clints Available in The System\n";
        else
        {
            for (clsBankClient::stTransferLogRegister& Record : vData)
            {
                _PrintOpperationRecordLine(Record);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};