/* Hugo Castro Banking System */
/* BankAccount.h */
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ostream;

class BankAccount {
private:
    static long cumulative_account_number;
    long bank_account_number;
    mutable string account_first_name;
    mutable string account_last_name;
    mutable long bank_account_amount;

public:
    static vector<BankAccount*> v_list;
    BankAccount(string account_first_name, string account_last_name, const long& bank_account_amt);
    BankAccount(const long& bank_account_number, string account_first_name, string account_last_name, const long& bank_account_amount);         /* Constructors, Mutators and Accessors*/
    BankAccount() : BankAccount(getAccountNumber(), "", "", 0L) {};
    BankAccount(const BankAccount& a);
    void setFirstName(const string& fn) const;
    void setLastName(const string& ln) const;
    void setAccountAmount(const long& bank_account_amount) const;
    const long& getAccountNumber() const;
    const string& getFirstName() const;
    const string& getLastName() const;
    const long& getAccountAmount() const;
    static long getLastAccountNumber(); /* Retrieve account info and get the latest account number */
    static vector<BankAccount*> getAll();
    friend const ifstream& operator>>(ifstream& ifs, vector<BankAccount*>& v_list);                                                /* File Input and Output*/
    friend ostream& operator<<(ostream& out, const BankAccount& a);
    friend const ofstream& operator<<(ofstream& ofs, const BankAccount& a);
    static void accountOpen();
    static bool compareBankAccountNumber(const BankAccount* bank_account_ptr, const long& bank_account_number) {            
        return (*bank_account_ptr).getAccountNumber() == bank_account_number;
    }
    static BankAccount* searchByAccountNumber(const long& bank_account_number);
    static void accountExisting();
    static void accountLedgerDump();
    static void accountDeposit();
    static void accountWithdraw();
    static void accountClose();
    static void loanCalculator();
    static void accountShowAll();

    ~BankAccount();             /* Destructor*/
};



