// ===================================================================================
//  Student Name  : Patel Parva Jitendrakumar
//  Student ID    : 116635202
//  Student Email : pjpatel41@mysenecacollege.ca
//  Course Section: IPC144NHH
// ===================================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>

#include "account.h"
#include "commonHelpers.h"

//Get account information with structure
void getAccount(const struct Account accounts[], int size, 
    struct Account* account)
{
    //For New record
    account->account_number = getNextAccountNumber(accounts, size);
    printf("\nNew Account Data (Account#:%d)", account->account_number);
    printf("\n----------------------------------------");

    //Get type of account
    printf("\nEnter the account type (A=Agent | C=Customer): ");
    account->account_type = getCharOption("AC");

    getUserLogin(&(account->login));
    getDemographic(&(account->demo));
}

//Get user login with structure
void getUserLogin(struct UserLogin* login)
{
    int flag = 0;
    printf("\nUser Login Data Input");
    printf("\n----------------------------------------\n");

    printf("Enter user login (10 chars max): ");

    do
    {
        getCString(login->login_name, 1, 10);

        if (checkWhiteSpace(login->login_name))
        {
            printf("ERROR:  The user login must NOT contain "
                "whitespace characters.\n");
            printf("Enter user login (10 chars max): ");
        }
        else
        {
            flag = 1;
        }

    } while (!flag);

    printf("Enter the display name (30 chars max): ");
    getCString(login->customer_name, 1, 30);

    printf("Enter the password (must be 8 chars in length): ");

    flag = 0;
    do
    {
        getCString(login->password, 8, 8);
        if (checkPassword(login->password))
        {
            printf("Enter the password (must be 8 chars in length): ");
        }
        else
        {
            flag = 1;
        }
    } while (!flag);
}

//get demographic with structure
void getDemographic(struct Demographic* demo)
{

    int current_year = currentYear();
    int i = 0;

    printf("\nDemographic Data Input");
    printf("\n----------------------------------------\n");

    printf("Enter birth year (current age must be between 18 and 110): ");
    demo->birth_year = getIntFromRange(current_year - 110,
        current_year - 18);
    printf("Enter the household Income: $");
    demo->household_income = getPositiveDouble();
    printf("Enter the country (30 chars max.): ");
    getCString(demo->country, 1, 30);

    for (i = 0; demo->country[i] != '\0'; i++)
    {
        demo->country[i] = toupper(demo->country[i]);
    }
}

// for account update
void updateAccount(struct Account* account)
{
    int option;
    int flag = 1;
    while (flag)
    {
        printf("Account: %d - Update Options", account->account_number);
        printf("\n----------------------------------------");

        printf("\n1) Update account type (current value: %c)",
            account->account_type);
        printf("\n2) Login");
        printf("\n3) Demographics");
        printf("\n0) Done");
        printf("\nSelection: ");

        option = getIntFromRange(0, 3);

        switch (option)
        {
        case 1:
            printf("\nEnter the account type (A=Agent | C=Customer): ");
            account->account_type = getCharOption("AC");
            break;

        case 2:
            updateUserLogin(&(account->login));
            break;

        case 3:
            updateDemographic(&(account->demo));
            break;

        case 0:
            flag = 0;
            break;
        }
    } 
}

// for user login update
void updateUserLogin(struct UserLogin* login)
{
    int option;
    int flag = 1;
    int flag_p = 0;
    while (flag)
    {
        printf("\nUser Login: %s - Update Options", login->login_name);
        printf("\n----------------------------------------");

        printf("\n1) Display name (current value: %s)", login->customer_name);
        printf("\n2) Password");
        printf("\n0) Done");
        printf("\nSelection: ");

        option = getIntFromRange(0, 2);

        switch (option)
        {
        case 1:
            printf("\nEnter the display name (30 chars max): ");
            getCString(login->customer_name, 1, 30);
            break;

        case 2:
            printf("\nEnter the password (must be 8 chars in length): ");
            do
            {
                getCString(login->password, 8, 8);
                if (checkPassword(login->password))
                {
                    printf("Enter the password (must be 8 chars in length): ");
                }
                else
                {
                    flag_p = 1;
                }
            } while (!flag_p);
            break;

        case 0:
            flag = 0;
            printf("\n");
            break;
        }
    } 
}

// for demographic update
void updateDemographic(struct Demographic* demo)
{
    int option;
    int flag = 1;
    int i;

    while (flag)
    {
        printf("\nDemographic Update Options");
        printf("\n----------------------------------------");
        printf("\n1) Household Income (current value: $%.2lf)",
            demo->household_income);
        printf("\n2) Country (current value: %s)", demo->country);
        printf("\n0) Done");
        printf("\nSelection: ");

        option = getIntFromRange(0, 2);

        switch (option)
        {
        case 1:
            printf("\nEnter the household Income: $");
            demo->household_income = getPositiveDouble();
            break;

        case 2:
            printf("\nEnter the country (30 chars max.): ");
            getCString(demo->country, 1, 30);

            for (i = 0; demo->country[i] != '\0'; i++)
            {
                demo->country[i] = toupper(demo->country[i]);
            }
            break;
        case 0:
            flag = 0;
            printf("\n");
            break;
        }
    } 
}

// Get Next Account number
int getNextAccountNumber(const struct Account accounts[], int size)
{
    int new_account_num = accounts[0].account_number;
    int i;
    for (i = 0; i < size; i++)
    {
        if (accounts[i].account_number > new_account_num)
        {
            new_account_num = accounts[i].account_number;
        }
    }

    return new_account_num + 1;
}