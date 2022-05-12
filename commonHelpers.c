// ===================================================================================
//  Student Name  : Patel Parva Jitendrakumar
//  Student ID    : 116635202
//  Student Email : pjpatel41@mysenecacollege.ca
//  Course Section: IPC144NHH
// ===================================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// commanHelpers library
#include "commonHelpers.h"

// For Current year
int currentYear(void)
{
    time_t currentTime = time(NULL);
    return localtime(&currentTime)->tm_year + 1900;
}

// For clear standar tnput buffer
void clearStandardInputBuffer(void)
{
    while (getchar() != '\n')
    {
        ; // On purpose: do nothing
    }
}

// Get A integer
int getInteger()
{
    char newLine = 'x';
    int value;
    while (newLine != '\n')
    {
        scanf("%d%c", &value, &newLine);
        if (newLine != '\n')
        {
            clearStandardInputBuffer();
            printf("ERROR: Value must be an integer: ");
        }
    }
    return value;
}

// Get a positive Integer 
int getPositiveInteger()
{
    char newLine = 'x';
    int value;
    while (newLine != '\n')
    {
        scanf("%d%c", &value, &newLine);
        if (newLine != '\n')
        {
            clearStandardInputBuffer();
            printf("ERROR: Value must be an integer: ");
        }
        else if (newLine == '\n' && value <= 0)
        {
            newLine = 'x';
            printf("ERROR: Value must be a positive integer "
                "greater than zero: ");
        }
    }
    return value;
}

//Get Double integer value
double getDouble()
{
    char newLine = 'x';
    double value;
    while (newLine != '\n')
    {
        scanf("%lf%c", &value, &newLine);
        if (newLine != '\n')
        {
            clearStandardInputBuffer();
            printf("ERROR: Value must be a double floating-point number: ");
        }
    }
    return value;
}

//Get double positive integer value
double getPositiveDouble()
{
    char newLine = 'x';
    double value;
    while (newLine != '\n')
    {
        scanf("%lf%c", &value, &newLine);
        if (newLine != '\n')
        {
            clearStandardInputBuffer();
            printf("ERROR: Value must be a double "
                "floating-point number: ");
        }
        else if (newLine == '\n' && value < 0.0)
        {
            newLine = 'x';
            printf("ERROR: Value must be a positive double "
                "floating-point number: ");
        }
        else if (newLine == '\n' && value == 0.0)
        {
            newLine = 'x';
            printf("ERROR: Value must be a positive double "
                "floating-point number: ");
        }
    }
    return value;
}

//Get integer from range
int getIntFromRange(int lower_bound, int upper_bound)
{
    char newLine = 'x';

    int value = 0;
    while (newLine != '\n')
    {
        scanf("%d%c", &value, &newLine);

        if (newLine == '\n')
        {
            if (value < lower_bound || value > upper_bound)
            {
                newLine = 'x';
                printf("ERROR: Value must be between %d and %d inclusive: ",
                    lower_bound, upper_bound);
            }
            else
            {
                return value;
            }
        }
        else
        {
            clearStandardInputBuffer();
            printf("ERROR: Value must be an integer: ");
        }
    }
    return value;
}

//Get Character option
char getCharOption(const char valid[])
{
    char ch, val = '0', newline = 'x';
    int i, keepgoing = 1;
    while (val != ch)
    {
        scanf(" %c", &ch);
        scanf("%c", &newline);
        if (newline == '\n')
        {
            for (i = 0; valid[i] != '\0' && keepgoing == 1; i++)
            {
                if (ch == valid[i])
                {
                    keepgoing = 0;
                    val = ch;
                }
                else
                {
                    keepgoing = 1;
                }
            }
        }
        if (newline != '\n')
        {
            clearStandardInputBuffer();
        }
        if (val != ch)
        {
            printf("ERROR: Character must be one of [%s]: ", valid);
        }
    } 
    return ch;
}

//Get C string
void getCString(char* cstring, int min_len, int max_len)
{
    char temp_string[200] = { '\0' };
    int i;
    while (1)
    {
        scanf("%[^\n]%*c", temp_string);

        i = strlen(temp_string);
        if (i >= min_len && i <= max_len)
        {
            strcpy(cstring, temp_string);
            return;
        }
        else if (min_len == max_len && i != min_len)
        {
            printf("ERROR: String length must be exactly %d chars: ", min_len);
        }
        else if (i > max_len)
        {
            printf("ERROR: String length must be no more than %d chars: ",
                max_len);
        }
        else if (i < min_len)
        {
            printf("ERROR: String length must be between %d and %d chars: ",
                min_len, max_len);
        }
    }
}

//Get Character Account type
char* getAccountType(const char account_type)
{
    if (account_type == 'A')
    {
        return "AGENT";
    }
    else
    {
        return "CUSTOMER";
    }
}

// Get ticket status
char* getTicketStatus(const int status)
{
    if (status)
    {
        return "ACTIVE";
    }
    return "CLOSED";
}

// For password check
int checkPassword(char* password)
{
    int i = 0;

    int count_digit = 0;
    int count_uppercase = 0;
    int count_lowercase = 0;
    int count_symbol = 0;

    for (i = 0; password[i] != '\0'; i++)
    {
        if (isdigit(password[i]))
        {
            count_digit++;
        }
        else if (isalpha(password[i]))
        {
            if (islower(password[i]))
            {
                count_lowercase++;
            }
            else
            {
                count_uppercase++;
            }
        }
        else if (password[i] == '!' || password[i] == '@' || 
            password[i] == '#' || password[i] == '$' || 
            password[i] == '%' || password[i] == '^' || 
            password[i] == '&' || password[i] == '*')
        {
            count_symbol++;
        }
    }
    if (count_digit != 2 || count_lowercase != 2 || 
        count_uppercase != 2 || count_symbol != 2)
    {
        printf("SECURITY: Password must contain 2 of each:\n");
        printf("          Digit: 0-9\n");
        printf("          UPPERCASE character\n");
        printf("          lowercase character\n");
        printf("          symbol character: %s\n", "!@#$%^&*");

        return 1;
    }
    return 0;
}

// for checking white space
int checkWhiteSpace(char cstring[])
{
    if (strchr(cstring, 32))
    {
        return 1;
    }
    return 0;
}