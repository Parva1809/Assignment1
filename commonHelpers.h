// ===================================================================================
//  Student Name  : Patel Parva Jitendrakumar
//  Student ID    : 116635202
//  Student Email : pjpatel41@mysenecacollege.ca
//  Course Section: IPC144NHH
// ===================================================================================
#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

int currentYear(void);
void clearStandardInputBuffer(void);

// Get A integer
int getInteger(void);

// Get a positive Integer 
int getPositiveInteger(void);

//Get Double integer value
double getDouble(void);

//Get double positive integer value
double getPositiveDouble(void);

//Get integer from range
int getIntFromRange(int lower_bound, int upper_bound);

//Get Character option
char getCharOption(const char cstring[]);

//Get C string
void getCString(char* cstring, int min_len, int max_len);

//Get Character Account type
char* getAccountType(const char account_type);

// Get character ticket statu
char* getTicketStatus(const int status);

// For checking white space
int checkWhiteSpace(char cstring[]);

// For Check password
int checkPassword(char* password);

#endif