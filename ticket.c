// ===================================================================================
//  Student Name  : Patel Parva Jitendrakumar
//  Student ID    : 116635202
//  Student Email : pjpatel41@mysenecacollege.ca
//  Course Section: IPC144NHH
// ===================================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "ticket.h"

// get next ticket number
int getNextTicketNumber(const struct Ticket tickets[], int size)
{

    int new_ticket_num = tickets[0].id;

    int i;
    for (i = 0; i < size; i++)
    {
        if (tickets[i].id > new_ticket_num)
        {
            new_ticket_num = tickets[i].id;
        }
    }

    return new_ticket_num + 1;
}