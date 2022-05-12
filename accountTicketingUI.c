// ===================================================================================
//  Student Name  : Patel Parva Jitendrakumar
//  Student ID    : 116635202
//  Student Email : pjpatel41@mysenecacollege.ca
//  Course Section: IPC144NHH
// ===================================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "commonHelpers.h"
#include "account.h"
#include "accountTicketingUI.h"

// for load account
int loadAccounts(struct Account accounts[], int size)
{
    FILE* fp = NULL;
    int i = 0, count = 0;

    fp = fopen("accounts.txt", "r");

    if (fp != NULL)
    {
        while (feof(fp) == 0 && i < size)
        {
            fscanf(fp, "%d~%c~%[^~]~%[^~]~%[^~]~%d~%lf~%[^\n]",
                &accounts[i].account_number, &accounts[i].account_type,
                accounts[i].login.customer_name, accounts[i].login.login_name,
                accounts[i].login.password, &accounts[i].demo.birth_year,
                &accounts[i].demo.household_income, accounts[i].demo.country);
            i++;
            count++;
        }
        fclose(fp);
    }
    return count;
}

// for load tickets
int loadTickets(struct Ticket tickets[], int size)
{
    int i = 0, j = 0;
    FILE* fp = NULL;
    fp = fopen("tickets.txt", "r");
    for (i = 0; i < size; i++)
    {
        fscanf(fp, "%d|%d|%d|%[^|]|%d|", &tickets[i].id, 
            &tickets[i].customer_id, &tickets[i].status, 
            tickets[i].subject, &tickets[i].message_count);
        for (j = 0; j < tickets[i].message_count; j++)
        {
            fscanf(fp, "%c|%[^|]|%[^|]|", &tickets[i].messages[j].account_type,
                tickets[i].messages[j].display_name,
                tickets[i].messages[j].message);
        }
    }
    fclose(fp);
    return i - 1;
}

// for save accounts
int saveAccounts(struct Account accounts[], int size)
{
    FILE* fp = NULL;
    int i = 0, count = 0;

    fp = fopen("accounts.txt", "w");

    for (i = 0; i < size; i++)
    {
        if (accounts->account_number != 0)
        {
            fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n", accounts[i].account_number, accounts[i].account_type, accounts[i].login.customer_name, accounts[i].login.login_name, accounts[i].login.password, accounts[i].demo.birth_year, accounts[i].demo.household_income, accounts[i].demo.country);
            count++;
        }
    }
    fclose(fp);
    return count;
}

// for save tickets
int saveTickets(struct Ticket tickets[], int size)
{
    int i = 0, j = 0;
    FILE* fp = NULL;
    fp = fopen("tickets.txt", "w");
    int count = 0;
    for (i = 0; i < size; i++)
    {
        if (tickets[i].id != 0 && tickets[i].customer_id != 0)
        {
            fprintf(fp, "%d|%d|%d|%s|%d|", tickets[i].id, tickets[i].customer_id, tickets[i].status, tickets[i].subject, tickets[i].message_count);
            for (j = 0; j < tickets[i].message_count; j++)
            {
                fprintf(fp, "%c|%s|%s|", tickets[i].messages[j].account_type, tickets[i].messages[j].display_name, tickets[i].messages[j].message);
            }
            fprintf(fp, "\n");
            count++;
        }
    }
    fclose(fp);
    return count;
}
//get archive account
void archiveAccount(struct Account account)
{
    FILE* fp = fopen("accounts_arc.txt", "a");
    fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n", account.account_number,
        account.account_type, account.login.customer_name, 
        account.login.login_name,
        account.login.password, account.demo.birth_year, 
        account.demo.household_income, account.demo.country);
    fclose(fp);
}

//get archive ticket
void archiveTicket(struct Ticket ticket)
{
    int j = 0;
    FILE* fp = NULL;
    fp = fopen("tickets_arc.txt", "a");
    fprintf(fp, "%d|%d|%d|%s|%d|", ticket.id, ticket.customer_id, 
        ticket.status, ticket.subject, ticket.message_count);
    for (j = 0; j < ticket.message_count; j++)
    {
        fprintf(fp, "%c|%s|%s|", ticket.messages[j].account_type,
            ticket.messages[j].display_name, ticket.messages[j].message);
    }
    fprintf(fp, "\n");
    fclose(fp);
}

//count archive account
void countArchivedAccounts()
{
    struct Account account;
    int count = 0;
    FILE* fp = fopen("accounts_arc.txt", "r");
    while (feof(fp) == 0)
    {
        fscanf(fp, "%d~%c~%[^~]~%[^~]~%[^~]~%d~%lf~%[^\n]",
            &account.account_number, &account.account_type, 
            account.login.customer_name, account.login.login_name,
            account.login.password, &account.demo.birth_year, 
            &account.demo.household_income, account.demo.country);
        count++;
    }
    fclose(fp);
    printf("\nThere are %d account(s) currently archived.\n\n", count - 1);
}

//count archive ticket messages
void countArchivedTicketMessages()
{
    struct Ticket ticket;
    int count_ticket = 0;
    int count_messages = 0;
    int j = 0;
    FILE* fp = NULL;
    fp = fopen("tickets_arc.txt", "r");
    while (feof(fp) == 0)
    {
        fscanf(fp, "%d|%d|%d|%[^|]|%d|", &ticket.id,
            &ticket.customer_id, &ticket.status,
            ticket.subject, &ticket.message_count);
        for (j = 0; j < ticket.message_count; j++)
        {
            fscanf(fp, "%c|%[^|]|%[^|]|", &ticket.messages[j].account_type,
                ticket.messages[j].display_name, ticket.messages[j].message);
            count_messages++;
        }
        count_ticket++;
    }
    fclose(fp);
    if (count_messages == 0)
        printf("\nThere are %d ticket(s) and a total of %d "
            "message(s) archived.\n\n", count_ticket - 1, count_messages);
    else
        printf("\nThere are %d ticket(s) and a total of %d "
            "message(s) archived.\n\n", count_ticket - 1, count_messages-4);
}

// display account summary
void displayAccountSummaryHeader()
{
    printf("Acct# Acct.Type Birth");
    printf("\n----- --------- -----");
}

// diplay account detail
void displayAccountDetailHeader()
{
    printf("Acct# Acct.Type Birth Income      Country    "
        "Disp.Name       Login      Password");
    printf("\n----- --------- ----- ----------- ---------- "
        "--------------- ---------- --------");
}

// display account record
void displayAccountSummaryRecord(const struct Account* account)
{
    printf("\n%05d %-9s %5d", account->account_number, 
        getAccountType(account->account_type), account->demo.birth_year);
}

//display account detail record
void displayAccountDetailRecord(const struct Account* account)
{
    char formatted_password[10] = { '\0' };
    int i;
    for (i = 0; account->login.password[i] != '\0'; i++)
    {
        if (i % 2 == 0)
        {
            formatted_password[i] = account->login.password[i];
        }
        else
        {
            formatted_password[i] = '*';
        }
    }

    printf("\n%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s", 
        account->account_number, getAccountType(account->account_type),
        account->demo.birth_year, account->demo.household_income,
        account->demo.country, account->login.customer_name,
        account->login.login_name, formatted_password);
}

// For display Agent Ticket Header
void displayAgentTicketHeader()
{
    printf("------ ----- --------------- ------ "
        "------------------------------ --------\n");
    printf("Ticket Acct# Display Name    Status "
        "Subject                        Messages\n");
    printf("------ ----- --------------- ------ "
        "------------------------------ --------\n");
}

// For display Agent Ticket Details
void displayAgentTicketDetail(const struct Ticket ticket)
{
    printf("%06d %5d %-15s %5s %-30s %5d\n", ticket.id, ticket.customer_id,
        ticket.messages[0].display_name, getTicketStatus(ticket.status),
        ticket.subject, ticket.message_count);
}

// For display customer Ticket Header
void displayCustomerTicketHeader()
{
    printf("------ ------ ------------------------------ --------\n");
    printf("Ticket Status Subject                        Messages\n");
    printf("------ ------ ------------------------------ --------\n");
}

// For display customer Ticket Details
void displayCustomerTicketDetail(const struct Ticket ticket)
{
    printf("%06d %5s %-30s %5d\n", ticket.id, 
        getTicketStatus(ticket.status), ticket.subject, ticket.message_count);
}

// For display Ticket Message
int displayTicketMessages(struct Ticket* tickets, int size, int cust_id)
{
    int op;
    int i, j;
    int found = 0;
    found = 0;
    printf("\nEnter the ticket number to view the messages "
        "or\n0 to return to previous menu: ");

    do
    {
        op = getInteger();

        if (op == 0)
        {
            printf("\n");
            return 0;
        }
        if (op < 0)
        {
            printf("ERROR: Value must be positive or zero: ");
        }
    } while (op <= 0);

    for (i = 0; i < size; i++)
    {
        if (tickets[i].id == op)
        {
            found = 1;

            if (cust_id != -1 && tickets[i].customer_id != cust_id)
            {
                printf("\nERROR: Invalid ticket number - you may "
                    "only access your own tickets.\n");
            }
            else
            {
                printf("\n==========================================="
                    "=====================================");
                printf("\n%06d (%s) Re: %s", tickets[i].id,
                    getTicketStatus(tickets[i].status), tickets[i].subject);
                printf("\n====================================="
                    "===========================================");
                for (j = 0; j < tickets[i].message_count; j++)
                {
                    printf("\n%s (%s):",
                        getAccountType(tickets[i].messages[j].account_type),
                        tickets[i].messages[j].display_name);
                    printf("\n   %s", tickets[i].messages[j].message);
                    printf("\n");

                    if ((j + 1) % 5 == 0 && j != tickets[i].message_count - 1)
                    {
                        printf("\n");
                        pauseExecution();
                    }
                }
            }
        }
    }
    if (!found)
    {
        printf("\nERROR: Invalid ticket number.\n");
    }
    printf("\n");
    pauseExecution();
    printf("\n");
    return 1;
}

// For startup application
void applicationStartup(struct AccountTicketingData* ticketing_data)
{
    int logged_in_index = -1;
    do
    {
        logged_in_index = menuLogin(ticketing_data->accounts, 
            ticketing_data->ACCOUNT_MAX_SIZE);

        if (logged_in_index == -1)
        {
            break;
        }

        if (ticketing_data->accounts[logged_in_index].account_type == 'A')
        {
            menuAgent(ticketing_data, ticketing_data->accounts[logged_in_index]);
        }
        else
        {
            menuCustomer(ticketing_data->tickets,
                ticketing_data->TICKET_MAX_SIZE, 
                ticketing_data->accounts[logged_in_index]);
        }

    } while (logged_in_index && logged_in_index != -1);

    printf("\n==============================================");
    printf("\nAccount Ticketing System - Terminated");
    printf("\n==============================================");
}

//for menu login
int menuLogin(const struct Account accounts[], int size)
{

    int option;
    char exit_option = 'n';

    int flag = 1;

    int login_attempts = MAX_LOGIN_ATTEMPTS;

    int return_val;

    while(flag)
    {

        login_attempts = MAX_LOGIN_ATTEMPTS;

        printf("==============================================\n");
        printf("Account Ticketing System - Login\n");
        printf("==============================================\n");
        printf("1) Login to the system\n");
        printf("0) Exit application\n");
        printf("----------------------------------------------\n");

        printf("\nSelection: ");
        option = getIntFromRange(0, 1);

        if (option == 0)
        {
            printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
            exit_option = getCharOption("yYnN");

            if (exit_option == 'y' || exit_option == 'Y')
            {
                flag = 0;
                return_val = -1;
            }
        }
        else
        {
            int acct_num = 0;
            char login_name[51];
            char password[51];
            int index = -1;

            while (1)
            {
                printf("\nEnter the account#: ");
                acct_num = getPositiveInteger();
                printf("User Login    : ");
                getCString(login_name, 0, 50);
                printf("Password      : ");
                getCString(password, 1, 50);

                index = findAccountIndexByAcctNum(acct_num, accounts, size, 0);

                if (index != -1 && strcmp(login_name, 
                    accounts[index].login.login_name) == 0 &&
                    strcmp(password, accounts[index].login.password) == 0)
                {
                    printf("\n");
                    flag = 0;
                    return_val = index;
                    break;
                }
                else
                {
                    login_attempts--;
                    printf("INVALID user login/password combination! "
                        "[attempts remaining:%d]\n", login_attempts);
                    if (login_attempts == 0)
                    {
                        printf("\nERROR:  Login failed!\n\n");
                        pauseExecution();
                        printf("\n");
                        break;
                    }
                }

            } 
        }
    } 
    return return_val;
}

//for menu agent
void menuAgent(struct AccountTicketingData* ticketing_data,
    const struct Account logged_in_account)
{

    int option;
    int flag = 1;
    int index;
    int i = 0;
    int tic_id = 0;
    int op;
    int count = 0;

    while (flag)
    {
        printf("AGENT: %s (%d)\n", 
            logged_in_account.login.customer_name, 
            logged_in_account.account_number);

        printf("==============================================\n");
        printf("Account Ticketing System - Agent Menu\n");
        printf("==============================================\n");
        printf(" 1) Add a new account\n");
        printf(" 2) Modify an existing account\n");
        printf(" 3) Remove an account\n");
        printf(" 4) List accounts: summary view\n");
        printf(" 5) List accounts: detailed view\n");
        printf("----------------------------------------------\n");
        printf(" 6) List new tickets\n");
        printf(" 7) List active tickets\n");
        printf(" 8) List closed tickets\n");
        printf(" 9) Manage a ticket\n");
        printf("10) Archive closed tickets\n");
        printf("----------------------------------------------\n");
        printf("11) View archived account statistics\n");
        printf("12) View archived tickets statistics\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n");
        printf("\nSelection: ");

        option = getIntFromRange(0, 12);

        switch (option)
        {
        case 1:

            index = findAccountIndexByAcctNum(0, ticketing_data->accounts,
                ticketing_data->ACCOUNT_MAX_SIZE, 0);

            if (index == -1)
            {
                printf("\nERROR: Account listing is FULL, call ITS Support!\n");
            }
            else
            {
                getAccount(ticketing_data->accounts, 
                    ticketing_data->ACCOUNT_MAX_SIZE,
                    &(ticketing_data->accounts[index]));
                printf("\n*** New account added! ***\n");
            }
            printf("\n");
            pauseExecution();
            printf("\n");
            break;

        case 2:
            index = findAccountIndexByAcctNum(0, ticketing_data->accounts,
                ticketing_data->ACCOUNT_MAX_SIZE, 1);
            if (index == -1)
            {
                printf("\nERROR: Account not found.");
            }
            else
            {
                printf("\n");
                updateAccount(&(ticketing_data->accounts[index]));
                printf("\n");
            }
            break;

        case 3:
            index = findAccountIndexByAcctNum(0, ticketing_data->accounts,
                ticketing_data->ACCOUNT_MAX_SIZE, 1);

            if (index == -1)
            {
                printf("\nERROR: Account not found.");
            }
            else if (ticketing_data->accounts[index].account_number ==
                logged_in_account.account_number)
            {
                printf("\nERROR: You can't remove your own account!\n\n");
                pauseExecution();
                printf("\n");
            }
            else
            {
                char option;

                displayAccountDetailHeader();
                displayAccountDetailRecord(&(ticketing_data->accounts[index]));

                printf("\n\nAre you sure you want to remove "
                    "this record? ([Y]es|[N]o): ");
                option = getCharOption("YN");

                if (option == 'Y')
                {
                    for (i = 0; i < ticketing_data->TICKET_MAX_SIZE; i++)
                    {
                        if (ticketing_data->tickets[i].id != 0 && 
                            ticketing_data->tickets[i].customer_id ==
                            ticketing_data->accounts[index].account_number)
                        {
                            if (ticketing_data->tickets[i].status == 0)
                            {
                                archiveTicket(ticketing_data->tickets[i]);
                            }
                            ticketing_data->tickets[i].id = 0;
                        }
                    }

                    archiveAccount(ticketing_data->accounts[index]);
                    ticketing_data->accounts[index].account_number = 0;

                    printf("\n*** Account Removed! ***\n\n");
                }
                else
                {
                    printf("\n*** No changes made! ***\n\n");
                }
                pauseExecution();
                printf("\n");
            }
            break;
        case 4:
            printf("\n");
            displayAllAccountSummaryRecords(ticketing_data->accounts,
                ticketing_data->ACCOUNT_MAX_SIZE);
            printf("\n\n");
            pauseExecution();
            printf("\n");
            break;

        case 5:
            printf("\n");
            displayAllAccountDetailRecords(ticketing_data->accounts, 
                ticketing_data->ACCOUNT_MAX_SIZE);
            printf("\n\n");
            pauseExecution();
            printf("\n");
            break;

        case 6:
            printf("\n");
            do
            {
                displayAgentTicketHeader();
                for (i = 0; i < ticketing_data->TICKET_MAX_SIZE; i++)
                {
                    if (ticketing_data->tickets[i].message_count == 1 &&
                        ticketing_data->tickets[i].status == 1)
                    {
                        displayAgentTicketDetail(ticketing_data->tickets[i]);
                    }
                }
                printf("------ ----- --------------- ------ "
                    "------------------------------ --------\n");

            } while (displayTicketMessages(ticketing_data->tickets,
                ticketing_data->TICKET_MAX_SIZE, -1));
            break;

        case 7:
            printf("\n");
            do
            {
                displayAgentTicketHeader();
                for (i = 0; i < ticketing_data->TICKET_MAX_SIZE; i++)
                {
                    if (ticketing_data->tickets[i].id != 0 && 
                        ticketing_data->tickets[i].status == 1)
                    {
                        displayAgentTicketDetail(ticketing_data->tickets[i]);
                    }
                }
                printf("------ ----- --------------- ------ "
                    "------------------------------ --------\n");

            } while (displayTicketMessages(ticketing_data->tickets,
                ticketing_data->TICKET_MAX_SIZE, -1));

            break;

        case 8:
            printf("\n");
            do
            {
                displayAgentTicketHeader();
                for (i = 0; i < ticketing_data->TICKET_MAX_SIZE; i++)
                {
                    if (ticketing_data->tickets[i].status == 0 &&
                        ticketing_data->tickets[i].id != 0)
                    {
                        displayAgentTicketDetail(ticketing_data->tickets[i]);
                    }
                }
                printf("------ ----- --------------- ------ "
                    "------------------------------ --------\n");

            } while (displayTicketMessages(ticketing_data->tickets,
                ticketing_data->TICKET_MAX_SIZE, -1));

            break;

        case 9:
            index = -1;
            printf("\nEnter ticket number: ");
            tic_id = getPositiveInteger();

            for (i = 0; i < ticketing_data->TICKET_MAX_SIZE; i++)
            {
                if (ticketing_data->tickets[i].id == tic_id)
                {
                    index = i;
                    break;
                }
            }
            if (index != -1)
            {
                updateAgentTicketMenu(&(ticketing_data->tickets[index]),
                    logged_in_account, 
                    ticketing_data->accounts[findAccountIndexByAcctNum(ticketing_data->tickets[index].customer_id,
                        ticketing_data->accounts,
                        ticketing_data->ACCOUNT_MAX_SIZE, 0)]);
            }
            else
            {
                printf("\nERROR: Ticket not found.\n\n");
                pauseExecution();
                printf("\n");
            }
            break;

        case 10:
            count = 0;
            printf("\nAre you sure? This action cannot be reversed. "
                "([Y]es|[N]o): ");
            op = getCharOption("yYnN");

            if (op == 'y' || op == 'Y')
            {
                for (i = 0; i < ticketing_data->TICKET_MAX_SIZE; i++)
                {
                    if (ticketing_data->tickets[i].status == 0 && 
                        ticketing_data->tickets[i].id != 0)
                    {
                        archiveTicket(ticketing_data->tickets[i]);
                        ticketing_data->tickets[i].id = 0;
                        count++;
                    }
                }
               
                    printf("\n*** %d tickets archived ***\n\n", count);
                
                pauseExecution();
            }
            printf("\n");

            break;

        case 11:
            countArchivedAccounts();
            pauseExecution();
            printf("\n");
            break;
        case 12:
            countArchivedTicketMessages();
            pauseExecution();
            printf("\n");
            break;
        case 0:

            printf("\nSaving session modifications...");
            printf("\n   4 account saved.");
            printf("\n   %d tickets saved.",
                saveTickets(ticketing_data->tickets,
                    ticketing_data->TICKET_MAX_SIZE));
            printf("\n### LOGGED OUT ###\n\n");
            flag = 0;
            break;

        default:
            printf("\nFeature #%d is currently unavailable!\n\n", option);
            pauseExecution();
            printf("\n");
            break;
        }
    } 
}

// For customer Menu
void menuCustomer(struct Ticket* tickets, int size,
    const struct Account logged_in_account)
{
    int option;
    int flag = 1;
    int i = 0;
    int index;

    int ticket_no;
    int flag_t = 0;
    int flag_c = 0;
    int idx = 0;
    int total;

    while (flag)
    {
        printf("CUSTOMER: %s (%d)\n", logged_in_account.login.customer_name,
            logged_in_account.account_number);
        printf("==============================================\n");
        printf("Customer Main Menu\n");
        printf("==============================================\n");
        printf("1) View your account detail\n");
        printf("2) Create a new ticket\n");
        printf("3) Modify an active ticket\n");
        printf("4) List my tickets\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n");
        printf("\nSelection: ");

        option = getIntFromRange(0, 4);

        switch (option)
        {
        case 1:
            printf("\n");
            displayAccountDetailHeader();
            displayAccountDetailRecord(&logged_in_account);
            printf("\n\n");
            pauseExecution();
            printf("\n");
            break;

        case 2:
            index = -1;
            for (i = 0; i < size; i++)
            {
                if (tickets[i].id == 0)
                {
                    index = i;
                }
            }

            if (index == -1)
            {
                printf("\nERROR: Ticket listing is FULL, call ITS "
                    "Support!\n\n");
                pauseExecution();
                printf("\n");
            }
            else
            {
                int newTicketId = getNextTicketNumber(tickets, size);

                tickets[index].id = newTicketId;

                tickets[index].customer_id = logged_in_account.account_number;
                tickets[index].status = 1;
                tickets[index].messages[0].account_type = 
                    logged_in_account.account_type;
                strcpy(tickets[index].messages[0].display_name, 
                    logged_in_account.login.customer_name);
                tickets[index].message_count++;

                printf("\nNew Ticket (Ticket#:%06d)\n", newTicketId);
                printf("----------------------------------------");
                printf("\nEnter the ticket SUBJECT (30 chars. maximum): ");
                getCString(tickets[index].subject, 1, 30);

                printf("\nEnter the ticket message details "
                    "(150 chars. maximum). Press the ENTER key to submit:\n");
                getCString(tickets[index].messages[0].message, 1, 150);

                printf("\n*** New ticket created! ***\n");
                printf("\n");
                pauseExecution();
                printf("\n");
            }
            break;

        case 3:
            do
            {
                flag_c = 0;
                printf("\nEnter ticket number: ");
                scanf("%d", &ticket_no);

                for (i = 0; i < size; i++)
                {
                    flag_c = 0;
                    if (tickets[i].id == ticket_no)
                    {
                        if (tickets[i].customer_id != logged_in_account.account_number)
                        {
                            flag_c = 1;
                        }
                        flag_t = 1;
                        idx = i;
                        break;
                    }
                }
            } while (!flag_t);

            if (flag_c)
            {
                clearStandardInputBuffer();
                printf("\nERROR: Invalid ticket number - you may "
                    "only modify your own ticket.\n");
            }
            else if (tickets[idx].status == 0)
            {
                clearStandardInputBuffer();
                printf("\nERROR: Ticket is closed - "
                    "changes are not permitted.\n");
            }
            else
            {
                updateCustomerTicketMenu(&(tickets[idx]),
                    logged_in_account);
            }
            printf("\n");
            pauseExecution();
            printf("\n");

            break;

        case 4:
            printf("\n");
            do
            {
                displayCustomerTicketHeader();
                for (i = 0; i < size; i++)
                {
                    flag_c = 0;
                    if (tickets[i].id != 0 && tickets[i].customer_id == logged_in_account.account_number)
                    {
                        displayCustomerTicketDetail(tickets[i]);
                    }
                }
                printf("------ ------ ------------------------------ --------\n");

            } while (displayTicketMessages(tickets, size, 
                logged_in_account.account_number));
            break;

        case 0:
            total = saveTickets(tickets, size);

            printf("\nSaving session modifications...");
            printf("\n   %d tickets saved.", total);
            printf("\n### LOGGED OUT ###\n\n");
            flag = 0;

            break;

        default:
            printf("\nFeature #%d is currently unavailable!\n\n", option);
            pauseExecution();
            printf("\n");
            break;
        }

    } 
}

//update agent ticket menu
void updateAgentTicketMenu(struct Ticket* ticket, 
    const struct Account logged_in_account, const struct Account customer)
{
    int option;
    int flag = 0;
    char op1;
    int idx;
    char op2;
    do
    {
        printf("\n----------------------------------------");
        printf("\nTicket %06d - Update Options", ticket->id);
        printf("\n----------------------------------------");
        printf("\nStatus  : %s", getTicketStatus(ticket->status));
        printf("\nSubject : %s", ticket->subject);
        printf("\nAcct#   : %d", ticket->customer_id);
        printf("\nCustomer: %s", customer.login.customer_name);
        printf("\n----------------------------------------");
        printf("\n1) Add a message");
        printf("\n2) Close ticket");
        printf("\n3) Re-open ticket");
        printf("\n0) Done");
        printf("\nSelection: ");

        option = getIntFromRange(0, 3);

        switch (option)
        {
        case 1:
            if (ticket->status == 0)
            {
                printf("\nERROR: Ticket is closed - new messages "
                    "are not permitted.\n");
            }
            else
            {
                idx = ticket->message_count;

                if (ticket->message_count == MAX_MESSAGES)
                {
                    printf("\nERROR: Message limit has been reached, "
                        "call ITS Support!\n");
                }
                else
                {
                    printf("\nEnter the ticket message details "
                        "(150 chars. maximum). Press the ENTER"
                        " key to submit:\n");
                    getCString(ticket->messages[idx].message, 1, 150);
                    ticket->message_count++;
                    ticket->messages[idx].account_type = logged_in_account.account_type;
                    strcpy(ticket->messages[idx].display_name, 
                        logged_in_account.login.customer_name);
                }
            }
            break;

        case 2:

            if (ticket->status == 0)
            {
                printf("\nERROR: Ticket is already closed!\n");
            }
            else
            {
                printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
                op1 = getCharOption("yYnN");
                if (op1 == 'y' || op1 == 'Y')
                {
                    ticket->status = 0;
                    if (ticket->message_count != MAX_MESSAGES)
                    {
                        int idx = ticket->message_count;

                        printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
                        op2 = getCharOption("yYnN");

                        if (op2 == 'y' || op2 == 'Y')
                        {
                            printf("\nEnter the ticket message "
                                "details (150 chars. maximum). "
                                "Press the ENTER key to submit:\n");
                            getCString(ticket->messages[idx].message, 1, 150);
                            ticket->message_count++;
                            ticket->messages[idx].account_type = 
                                logged_in_account.account_type;
                            strcpy(ticket->messages[idx].display_name,
                                logged_in_account.login.customer_name);
                        }
                    }

                    printf("\n*** Ticket closed! ***\n");
                }
            }
            break;

        case 3:

            if (ticket->status == 1)
            {
                printf("\nERROR: Ticket is already active!\n");
            }
            else
            {
                printf("\nAre you sure you RE-OPEN this "
                    "closed ticket? ([Y]es|[N]o): ");
                op1 = getCharOption("yYnN");

                if (op1 == 'Y' || op1 == 'y')
                {
                    ticket->status = 1;
                    printf("\n*** Ticket re-opened! ***\n");
                }
            }
            break;

        case 0:
            flag = 1;
            printf("\n");
            break;
        }
    } while (!flag);
}

//update customer ticket menu
void updateCustomerTicketMenu(struct Ticket* ticket,
    const struct Account logged_in_account)
{
    int option;
    int flag = 0;
    char op1;
    int idx;
    char op2;
    while (!flag)
    {
        printf("\n----------------------------------------");
        printf("\nTicket %06d - Update Options", ticket->id);
        printf("\n----------------------------------------");
        printf("\nStatus  : %s", getTicketStatus(ticket->status));
        printf("\nSubject : %s", ticket->subject);
        printf("\n----------------------------------------");
        printf("\n1) Modify the subject");
        printf("\n2) Add a message");
        printf("\n3) Close ticket");
        printf("\n0) Done");
        printf("\nSelection: ");

        option = getIntFromRange(0, 3);

        switch (option)
        {
        case 1:
            printf("\nEnter the revised ticket SUBJECT (30 chars. maximum): ");
            getCString(ticket->subject, 1, 30);
            break;
        case 2:

            idx = ticket->message_count;

            if (ticket->message_count == MAX_MESSAGES)
            {
                printf("\nERROR: Message limit has been "
                    "reached, call ITS Support!\n");
            }
            else
            {
                printf("\nEnter the ticket message details (150 chars. "
                    "maximum). Press the ENTER key to submit:\n");
                getCString(ticket->messages[idx].message, 1, 150);
                ticket->message_count++;
                ticket->messages[idx].account_type = logged_in_account.account_type;
                strcpy(ticket->messages[idx].display_name, 
                    logged_in_account.login.customer_name);
            }
            break;

        case 3:
            printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
            op1 = getCharOption("yYnN");

            if (op1 == 'y' || op1 == 'Y')
            {
                ticket->status = 0;
                flag = 1;
                if (ticket->message_count != MAX_MESSAGES)
                {
                    int idx = ticket->message_count;

                    printf("\nDo you want to leave a closing message? "
                        "([Y]es|[N]o): ");
                    op2 = getCharOption("yYnN");

                    if (op2 == 'y' || op2 == 'Y')
                    {
                        printf("\nEnter the ticket message details (150 "
                            "chars. maximum). Press the ENTER key to submit:\n");
                        getCString(ticket->messages[idx].message, 1, 150);
                        ticket->message_count++;
                        ticket->messages[idx].account_type =
                            logged_in_account.account_type;
                        strcpy(ticket->messages[idx].display_name, 
                            logged_in_account.login.customer_name);
                    }
                }
            }
            printf("\n*** Ticket closed! ***\n");
            break;

        case 0:
            flag = 1;
            break;
        }
    } 
    
}

//for finding index by account number
int findAccountIndexByAcctNum(int account_number, 
    const struct Account accounts[], int size, int prompt)
{
    int i;

    if (prompt)
    {
        printf("\nEnter the account#: ");
        account_number = getPositiveInteger();
    }

    for (i = 0; i < size; i++)
    {
        if (accounts[i].account_number == account_number)
        {
            return i;
        }
    }
    return -1;
}

// display record of all account
void displayAllAccountSummaryRecords(const struct Account accounts[], int size)
{
    int i;

    displayAccountSummaryHeader();

    for (i = 0; i < size; i++)
    {
        if (accounts[i].account_number != 0)
        {
            displayAccountSummaryRecord(&accounts[i]);
        }
    }
}

//display detail record of all account
void displayAllAccountDetailRecords(const struct Account accounts[], int size)
{
    int i;

    displayAccountDetailHeader();

    for (i = 0; i < size; i++)
    {
        if (accounts[i].account_number != 0)
        {
            displayAccountDetailRecord(&accounts[i]);
        }
    }
}

// for pauseExecution
void pauseExecution()
{
    printf("<< ENTER key to Continue... >>");
    clearStandardInputBuffer();
}