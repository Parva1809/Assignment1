// ===================================================================================
//  Student Name  : Patel Parva Jitendrakumar
//  Student ID    : 116635202
//  Student Email : pjpatel41@mysenecacollege.ca
//  Course Section: IPC144NHH
// ===================================================================================
#ifndef TICKET_H_
#define TICKET_H_

#define MAX_MESSAGES 20

// Create structure message
struct Message
{
    char account_type;
    char display_name[31];
    char message[151];
};

//Create Structure Ticket
struct Ticket
{
    int id;
    int customer_id;
    int status;
    char subject[31];
    int message_count;
    struct Message messages[20];
};

//get next ticket number
int getNextTicketNumber(const struct Ticket tickets[], int size);
#endif