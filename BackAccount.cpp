/* Hugo Castro Banking System */
/* BankAccount.cpp */
#include "BankAccount.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::endl;
using std::cout;
using std::cin;
using std::ios;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;
using std::ostream;

vector<BankAccount*> BankAccount::v_list = BankAccount::getAll();                         /* This vector retrieves all the account info which is inputted by the user*/
long BankAccount::cumulative_account_number = BankAccount::getLastAccountNumber();        /* This gets the last information which has been inputted into the program */

BankAccount::BankAccount(string account_first_name, string account_last_name, const long& bank_account_amount) :           /* The following shows the list of Constructors */
    account_first_name(std::move(account_first_name)),  
    account_last_name(std::move(account_last_name)),
    bank_account_amount(bank_account_amount),
    bank_account_number(++cumulative_account_number) {
}
BankAccount::BankAccount(const long& bank_account_number, string account_first_name, string account_last_name, const long& bank_account_amount) :
    account_first_name(std::move(account_first_name)),
    account_last_name(std::move(account_last_name)),
    bank_account_amount(bank_account_amount),
    bank_account_number(bank_account_number) {
}
BankAccount::BankAccount(const BankAccount& a) :
    account_first_name(a.getFirstName()),
    account_last_name(a.getLastName()),
    bank_account_amount(a.getAccountAmount()),
    bank_account_number(++cumulative_account_number) {
}
void BankAccount::setFirstName(const string& fn) const {        /* This is the list of Mutators */
    this->account_first_name = fn;
}
void BankAccount::setLastName(const string& ln) const {
    this->account_last_name = ln;
}
void BankAccount::setAccountAmount(const long& account_amt) const {
    this->bank_account_amount = account_amt;
}

const long& BankAccount::getAccountNumber() const {                 /* List of Accessors */
    return bank_account_number;
}                                                                   /* Returns information which has been inputted */
const string& BankAccount::getFirstName() const {
    return account_first_name;
}
const string& BankAccount::getLastName() const {
    return account_last_name;
}
const long& BankAccount::getAccountAmount() const {
    return bank_account_amount;
}

vector<BankAccount*> BankAccount::getAll() {
    vector<BankAccount*> list;
    ifstream ifs;
    ifs.open("Hugo Castro Bank Ledger.txt");                                     /* This will load all account info to a vector of Account class pointers */
    if (!ifs)
        return {};                                                 
    while (!ifs.eof())
        ifs >> list;
    return list;
}

long BankAccount::getLastAccountNumber() {                                                          /* This will return the latest account number in the vector */
    return BankAccount::v_list.empty() ? 0 : (*BankAccount::v_list.back()).getAccountNumber();
}

void BankAccount::accountOpen() {                                           /* These are the facilitators */
    string account_first_name;
    string account_last_name;                                                       /* Open Account Facilitator */
    cout << "\nCreate a new Bank Account" << endl;                          /* This will create a new Bank Account. It has been designed to assign a new account number if one is taken  */
    cout << "\nPlease Enter Your First Name: " << endl;                          /* The information is based on the ledger document. It updates when a new account is added */
    cin >> account_first_name;
    cout << "\nPlease Enter Your Last Name: " << endl;
    cin >> account_last_name;
    long acct_amt;
    cout << "\nPlease Enter The Desired Account Amount:" << endl;
    cin >> acct_amt;
    v_list.push_back(new BankAccount("", "", 0));
    v_list.back()->setFirstName(account_first_name);
    v_list.back()->setLastName(account_last_name);
    v_list.back()->setAccountAmount(acct_amt);
    cout << *v_list.back() << endl;                   /* Save to the Hugo Castro Bank Ledger text file */
    ofstream ofs("Hugo Castro Bank Ledger.txt", ios::app);
    ofs << *v_list.back();
    ofs.close();
}
BankAccount* BankAccount::searchByAccountNumber(const long& acct_num) {                             /* Search for Bank Account Number */
    vector<BankAccount*>::iterator itr;
    itr = find_if(v_list.begin(), v_list.end(),
        [&](auto acct_ptr) { return compareBankAccountNumber(acct_ptr, acct_num); });
    if (itr != v_list.end())
        return *itr;
    else {
        BankAccount* ptr = nullptr;
        return ptr;
    }
}
void BankAccount::accountExisting() {                                                               /* Search for existing Bank Account Numbers */
    long balance_account_number;
    cout << "\nView Existing Bank Account" << endl;
    cout << "\nEnter an Existing Bank Account Number: " << endl;
    cin >> balance_account_number;
    BankAccount* balance_ptr = searchByAccountNumber(balance_account_number);
    if (balance_ptr != nullptr)
        cout << *balance_ptr << endl;
    else
        cout << "\nBank Account Not Found. Please enter a valid Bank Account Number." << endl;
}
void BankAccount::accountLedgerDump() {                                                            /* Add to the Bank Account Ledger File*/
    ofstream ofs("Hugo Castro Bank Ledger.txt", ios::trunc);
    for (auto x : v_list)
        ofs << *x;
    ofs.close();
}
void BankAccount::accountDeposit() {                                            
    long deposit_bank_account_number;                                                                    /* Deposit Funds into Account */
    long deposit_amount;
    cout << "\nDeposit Funds" << endl;
    cout << "Enter Bank Account Number: " << endl;
    cin >> deposit_bank_account_number;
    BankAccount* deposit_ptr = searchByAccountNumber(deposit_bank_account_number);
    if (deposit_ptr != nullptr) {
        cout << *deposit_ptr << endl;
        cout << "\nEnter Deposit Amount: " << endl;
        cin >> deposit_amount;
        deposit_ptr->setAccountAmount(deposit_amount + deposit_ptr->getAccountAmount());
        cout << "Total Amount "
            << deposit_amount
            << " has been deposited into Bank Account Number "
            << deposit_bank_account_number
            << endl;                                 
        accountLedgerDump();                                 /* This will update the Account Ledger File Which has been created */
        cout << *deposit_ptr << endl;
    }
    else
        cout << "Bank Account Not Found. Please enter a valid Bank Account Number. "<< endl;
}
void BankAccount::accountWithdraw() {                                                                  /* Withdraw Funds */
    long withdraw_bank_account_number;                                                                 /* Deducts funds from the existing balance */
    long withdraw_amount;
    cout << "\n*Withdraw Funds" << endl;
    cout << "Enter Bank Account Number: " << endl;
    cin >> withdraw_bank_account_number;
    BankAccount* withdraw_ptr = searchByAccountNumber(withdraw_bank_account_number);
    if (withdraw_ptr != nullptr) {
        cout << *withdraw_ptr << endl;
        cout << "\nEnter Withdrawal Amount: " << endl;
        cin >> withdraw_amount;
        withdraw_ptr->setAccountAmount(withdraw_ptr->getAccountAmount() - withdraw_amount);
        cout << "Total Amount "
            << withdraw_amount
            << " has been withdrawn into Account Number "
            << withdraw_bank_account_number
            << endl;

        accountLedgerDump();                                /* Update the Bank Ledger */
        cout << *withdraw_ptr << endl;
    }
    else
        cout << "Bank Account Not Found. Please enter a valid Bank Account Number." << endl;
}
void BankAccount::accountClose() {
    cout << "\nClose a Bank Account" << endl;
    long close_bank_account_number;
    cout << "Enter Bank Account Number: " << endl;
    cin >> close_bank_account_number;
    vector<BankAccount*>::iterator iter;
    for (iter = v_list.begin(); iter != v_list.end(); ++iter) {
          if ((*iter)->getAccountNumber() == close_bank_account_number) {
                cout << **iter << endl;
                v_list.erase(iter);                                                         /* After erasing the account I need to break from the loop since the erasure will invalidate the iterator */
                accountLedgerDump();                                                      /* I made this simply return so you can detect number not found without an inefficient and needless first search */
                cout << "Account Number " << close_bank_account_number << " has been closed." << endl;
                return;
          }
    }

    cout << "Bank Account Not Found. Please enter a valid Bank Account Number." << endl;          /* Once the account is deleted it returns directly from the loop */
}
void BankAccount::loanCalculator() {        
    cout << "\nLoan Calculator" << endl;
    double loan_amount, interest_rate, total_amount, monthly_amount;
    int payback_number_of_years;
    cout << "Enter your desired Loan Amount: " << endl;
    cin >> loan_amount;
    cout << "Enter the interest rate (effective APR): " << endl;
    cin >> interest_rate;

    interest_rate /= 100.0f;        /* This converts the interest rate to decimal */

    cout << "Please enter the number of years to pay it back over: " << endl;
    cin >> payback_number_of_years;

    double interest_amount = 0;                                                      /*Interest is to be calculated over the number of year with payments made each month */                                                                               
    double monthly_interest = (std::pow(1.0 + interest_rate, 1.0/12.0) - 1) ;        /*Convert the annual rate into a monthly rate, and then calculate month by month */
    
    cout << "Monthly interest rate is:" << monthly_interest * 100.0 << "\n";                           /*A monthly payment schedule that evenly spreads the payment across the time */
                                                                                                      /* An annual lower payment equal to loan/payments and an upper equal to loan * monthly^years / payments */
    double upper = loan_amount * std::pow(1.0+interest_rate, payback_number_of_years) / (payback_number_of_years * 12.0);
    double lower = loan_amount / (payback_number_of_years*12.0);
    double middle = 0.0;

    while (upper != lower) {

          middle = (upper + lower) / 2.0;                                       /* Bisects the range each time. */
          if (middle == lower || middle == upper)
              break;
          double loanLeft = loan_amount;                                     /* Calculates the total loan payments made for the middle value */
          for (int i = 0; i < 12*payback_number_of_years; ++i) {
               loanLeft = loanLeft * (monthly_interest + 1.0);
               loanLeft -= middle;
          }
          if (loanLeft > 0.0)                                               /* If left > 0 pick the [middle, upper] range, otherwise [lower, middle] */
               lower = middle;                                              /* This allows to progressively split the range until we find the perfect monthly loan payment */
          else
               upper = middle;
    }
    monthly_amount = std::round(middle * 100.0)/100.0;                  /* I have amde this to round up to the nearest penny */

    total_amount = monthly_amount * payback_number_of_years * 12;     /* Total payment is simply month payments * number of payments */

    cout << "Total amount to be paid: " << total_amount << endl;
    cout << "Total interest: " << total_amount - loan_amount << endl;
    cout << "Monthly amount to be paid: " << monthly_amount << endl;
}
void BankAccount::accountShowAll() {
    cout << "\nShow All Accounts";
    for (auto acct_ptr : v_list)
        cout << *acct_ptr << endl;
}
BankAccount::~BankAccount() = default;                                                    /* These are the destructors */

ifstream const& operator>>(ifstream & ifs, vector<BankAccount*> &v_list) {              /* Friend Functions */
    long bank_account_number;
    string account_first_name;                          
    string account_last_name;
    long account_amount;
    ifs >> bank_account_number >> account_first_name >> account_last_name >> account_amount;
    v_list.push_back(new BankAccount(bank_account_number, account_first_name, account_last_name, account_amount));
    return ifs;
}

ostream& operator<<(ostream & out, const BankAccount & a) {                     
    out << "\nBank Account Number: " << a.getAccountNumber() << endl                            /* Inputs in details */
        << "First Name: " << a.getFirstName() << endl
        << "Last Name: " << a.getLastName() << endl
        << "Bank Account Amount: " << a.getAccountAmount();
    return out;
}

const ofstream& operator<<(ofstream & ofs, const BankAccount & a) {                         /* Prints details */
    ofs << "\n"
        << a.getAccountNumber() << endl
        << a.getFirstName() << endl
        << a.getLastName() << endl
        << a.getAccountAmount();
    return ofs;
}