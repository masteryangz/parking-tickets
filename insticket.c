#include <limits.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "parking.h"
#include "hashdb.h"

#ifndef MYINSTICKET
TODO(USING THE SOLUTION insticket.c NOT MY CODE)
#else
/*
 * function insertticket()
 *
 * Operation: insert a ticket with parameters provided to the end of the ticket list of the vehicle specified
 * If the vehicle is not in the hash table, then insert a new vehicle at the start of the chain
 * If there is a duplicate ticket, return -1 
 * params: summ, plate, state, date, code
 * returns: 0 if ticket inserted successful, -1 otherwise
 */
int
insertticket(char *summ, char *plate, char *state, char *date, int code)
{
    unsigned long long summid;               /* summons in unsigned long long form */
    time_t dateval;                          /* date in time_t form */
    uint32_t hashval;                        /* hash value to search for the chains in hash table */              
    struct vehicle *first;                   /* the first vehicle in the disired chain */        
    hashval = hash(plate) % tabsz;
    struct vehicle *new_vehicle = NULL;      /* the new vehicle if the desired vehicle is not in hash table */
    first = *(htable + hashval);
    struct ticket *new_ticket = NULL;        /* the ticket that needs to be inserted */
    struct ticket *tptr;                     /* ticket pointer */
    struct ticket *pretptr;                  /* previous pointer */
    if (strtosumid(summ, &summid) != 0)
	return -1;
    if (strtoDate(date, &dateval) != 0)
	return -1;
    /*
     * desired vehicle not found
     */
    new_vehicle = vehiclelookup(plate, state);
    if (new_vehicle == NULL) {
        if ((new_vehicle = malloc(sizeof(struct vehicle))) == NULL) {
	    fprintf(stderr, "%s: unable to allocate vehicle for summons %s\n", argv0, summ);
	    return -1;
        }
        new_vehicle->plate = strdup(plate);
        new_vehicle->state = strdup(state);
	new_vehicle->tot_fine = fineTab[code].fine;
	new_vehicle->cnt_ticket = 1;
	*(htable+hashval) = new_vehicle;
	new_vehicle->next = first;
	if ((new_ticket = malloc(sizeof(struct ticket))) == NULL) {
	    fprintf(stderr, "%s: unable to allocate ticket for summons %s\n", argv0, summ);
	    return -1;
	}
	new_ticket->summons = summid;
	new_ticket->date = dateval;
	new_ticket->code = code;
	new_vehicle->head = new_ticket;
	new_ticket->next = NULL;
    }
    /* the vehicle is found
     */
    else {
        /*
         * loop through the ticket list of the desired vehicle to determine whether there is a duplicate ticket
         */
	pretptr = NULL;
	tptr = new_vehicle->head;
        while (tptr != NULL) {
	    if (summid == tptr->summons) {
	        fprintf(stderr, "%s: duplicate summons %llu\n", argv0, summid);
	        return -1;
	    }
	    pretptr = tptr;
            tptr = tptr->next;
        }
	if ((new_ticket= malloc(sizeof(struct ticket))) == NULL) {
	    fprintf(stderr, "%s: unable to allocate ticket for summons %s\n", argv0, summ);
	    return -1;
	}
	if (pretptr == NULL)
	    new_vehicle->head = new_ticket;
	else
	    pretptr->next = new_ticket;
	new_vehicle->tot_fine += fineTab[code].fine;
	new_vehicle->cnt_ticket += 1;
        new_ticket->summons = summid;
        new_ticket->date = dateval;
        new_ticket->code = code;
	new_ticket->next = NULL;
    }
    new_ticket = NULL;
    new_vehicle = NULL;
    return 0;
}
#endif
