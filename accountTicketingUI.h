// ===================================================================================
//  Student Name  : Patel Parva Jitendrakumar
//  Student ID    : 116635202
//  Student Email : pjpatel41@mysenecacollege.ca
//  Course Section: IPC144NHH
// ===================================================================================
#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

#include "account.h"
#include "ticket.h"

#define MAX_LOGIN_ATTEMPTS 3

//structur account ticketing data
struct AccountTicketingData
{
    struct Account* accounts;
    const int ACCOUNT_MAX_SIZE;
    struct Ticket* tickets;
    const int TICKET_MAX_SIZE;
};

// for Display summary header
void displayAccountSummaryHeader();

// for Display detail header
void displayAccountDetailHeader();

// for Display summary record
void displayAccountSummaryRecord(const struct Account* account);

// for Display detail record
void displayAccountDetailRecord(const struct Account* account);

// Get applicatin startup
void applicationStartup(struct AccountTicketingData* ticketing_data);

// for menu login
int menuLogin(const struct Account accounts[], int size);

// for menu agent
void menuAgent(struct AccountTicketingData* ticketing_data, 
    const struct Account logged_in_account);

// for menu customer
void menuCustomer(struct Ticket* tickets, int size, 
    const struct Account logged_in_account);

// find iaccount index by account number
int findAccountIndexByAcctNum(int account_number,
    const struct Account accounts[], int size, int prompt);

//display record of all account
void displayAllAccountSummaryRecords(const struct Account accounts[],
    int size);

//dispaly record of detail
void displayAllAccountDetailRecords(const struct Account accounts[],
    int size);

// pauseExecution
void pauseExecution();

// display Agent ticket header
void displayAgentTicketHeader();

// display Agent ticket details
void displayAgentTicketDetail(const struct Ticket ticket);

// display customer ticket header
void displayCustomerTicketHeader();

// display customer ticket detail
void displayCustomerTicketDetail(const struct Ticket ticket);

// display ticket message
int displayTicketMessages(struct Ticket* tickets, int size, int cust_id);

//update agent ticket menu
void updateAgentTicketMenu(struct Ticket* ticket, 
    const struct Account logged_in_account, const struct Account customer);

//update customer ticket menu
void updateCustomerTicketMenu(struct Ticket* ticket,
    const struct Account logged_in_account);

// for load account
int loadAccounts(struct Account accounts[], int size);

// for load tickets
int loadTickets(struct Ticket tickets[], int size);

// for save tickets
int saveTickets(struct Ticket tickets[], int size);

//get archive account
void archiveAccount(struct Account account);

//get archive ticket
void archiveTicket(struct Ticket ticket);

//count archive account
void countArchivedAccounts();

//count archive ticket messages
void countArchivedTicketMessages();
#endif