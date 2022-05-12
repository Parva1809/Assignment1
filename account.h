// ===================================================================================
//  Student Name  : Patel Parva Jitendrakumar
//  Student ID    : 116635202
//  Student Email : pjpatel41@mysenecacollege.ca
//  Course Section: IPC144NHH
// ===================================================================================
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

//Create Demographic Structure
struct Demographic
{
    int birth_year;
    double household_income;
    char country[31];
};

//Create UserLogin Structure
struct UserLogin
{
    char customer_name[31];
    char login_name[11];
    char password[9];
};

//Create Account Structure
struct Account
{
    int account_number;
    char account_type;
    struct UserLogin login;
    struct Demographic demo;
};

// Get account with structure 
void getAccount(const struct Account accounts[], int size, 
    struct Account* account);

// Get user login with structure 
void getUserLogin(struct UserLogin* login);

// Get demographic with structure 
void getDemographic(struct Demographic* demo);

// for account update
void updateAccount(struct Account* account);

// for user login update
void updateUserLogin(struct UserLogin* login);

//for demographic update
void updateDemographic(struct Demographic* demo);

// Get next accountnumber
int getNextAccountNumber(const struct Account accounts[], int size);

#endif