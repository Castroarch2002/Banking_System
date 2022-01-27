/* Hugo Castro Banking System */
/* BankingMain.cpp */
#include <iostream>
#include <vector>                   /* Including IOSTREAM (Input and Output), Vectors (Used as sequence containers to store elements, Specifically with Dynamic data), BankAccount.h (Includes the header file for the information */
#include "BankAccount.h"

using std::cout;
using std::cin;         /* Using Standards */
using std::endl;
using std::vector;

int main() {
    int choice = 0;
    int* const choice_ptr = &choice;
    cout << "\nWelcome to Hugo Castro's Banking System" << endl;                   /* This is the Main Function to the Left*/
    while (*choice_ptr != 8) {
        cout << "\nPlease select from the following options: "
            << "\n\n1. Open A Bank Account"
            << "\n\n2. Check An Existing Bank Acccount"                                   
            << "\n\n3. Deposit Funds"
            << "\n\n4. Withdraw Funds"
            << "\n\n5. Close A Bank Account"
            << "\n\n6. Show All Bank Accounts"
            << "\n\n7. Loan Calculator"
            << "\n\n8. Quit Application" << endl;
        cin >> *choice_ptr;
        switch (*choice_ptr) {                              /* This is the Switch Statement.  It takes a variable value and will seek the matching value among the case values*/
        case 1:
            BankAccount::accountOpen();
            break;
        case 2:
            BankAccount::accountExisting();
            break;
        case 3:
            BankAccount::accountDeposit();
            break;
        case 4:
            BankAccount::accountWithdraw();
            break;
        case 5:
            BankAccount::accountClose();
            break;
        case 6:
            BankAccount::accountShowAll();
            break;
        case 7:
            BankAccount::loanCalculator();
            break;
        case 8: {
            BankAccount::accountLedgerDump();

            vector<BankAccount*>::iterator itr;                                                     /* This will delete the vector pointers */
            for (itr = BankAccount::v_list.begin(); itr != BankAccount::v_list.end(); itr++) {
                delete* itr;
            }
            cout << "Thanks for using my Banking System, This application will now close" << endl;
            break;
        }
        default:
            cout << "*Please enter a valid option (1-8)*" << endl;
            break;
        }
    }
    return 0;
}