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

#ifndef MYDELTICKET
TODO(USING THE SOLUTION delticket.c NOT MY CODE)
#else

/*
 * delticket
 *      remove ticket (summons) from the database
 *      look up the summons for a vehicle and pay it (remove the ticket) 
 *
 *      Find the vehicle by the state and plate. if not found return -1
 *
 *      convert the summ string to a long long int using
 *      using strtosumid. This long long int is how the summons number
 *      is stored in the database in struct ticket.
 *      After being converted you can use it find a summons id match
 *      in the linked list of tickets attached to the strcut vehicle.      
 *
 *      After you have the vehicle, find the summons on the ticket chain
 *      that matches the converted summons string (summid in the example)
 *      example:
 *        unsigned long long summid
 *        if (strtosumid(summ, &summid) != 0)
 *           return -1;
 *        now search the ticket chain to find that summons
 *        struct ticket *tptr;
 *        if (tptr->summons == summid)
 *          found it
 *           
 *      If found, delete it from the ticket chain. If the vehicle
 *      no longer has any tickets, then remove the vehicle from the hash chain
 *      Otherwise you must update the tot_fine and cnt_tickets fields in
 *      the struct vehicle so the are accurate after removing the summons
 *      Make sure to delete all space that malloc()'d 
 *
 * Inputs:
 *  plate   plate id string to be found
 *  state   state id string to be found
 *  summ    summon id string to be found
 *
 * returns 0 if ok -1 if not found or error
 */

int
delticket(char *plate, char *state, char *summ)
{
    unsigned long long summid;    /* unsigned long long form of summons */

    /*
     * convert the summons string to a number
     */
    if (strtosumid(summ, &summid) != 0)
        return -1;
    uint32_t hashval;             /* hash value */
    struct vehicle *chain;        /* desired chain */
    hashval = hash(plate) % tabsz;
    chain = *(htable + hashval);
    struct ticket *tptr;          /* ticket pointer */
    struct ticket *pretptr;       /* previous ticket pointer */
    struct vehicle *prevptr;      /* previous vehicle pointer */
    if (vehiclelookup(plate, state) == NULL) {
        return -1;
    } else {
	prevptr = chain;
	while (chain != NULL) {
	    if ((strcmp(chain->state, state) == 0) && (strcmp(chain->plate, plate) == 0))
		break;
	    prevptr = chain;
	    chain = chain->next;
	}
    }
    if (chain == NULL)
	return -1;
    tptr = chain->head;
    pretptr = tptr;
    while (tptr != NULL) {
	if (tptr->summons == summid) {
	    break;
	}
        pretptr = tptr;
	tptr = tptr->next;
    }
    if (tptr == NULL) {
        return -1;
    }
    if (tptr == chain->head) {
        chain->head = tptr->next;
    } else {
        pretptr->next = tptr->next;
    }
    chain->tot_fine -= fineTab[tptr->code].fine;
    chain->cnt_ticket--;
    free(tptr);
    if ((chain->cnt_ticket == 0) && (chain->tot_fine == 0)) {
        if (chain == *(htable+hashval))
	    *(htable+hashval) = chain->next;
	else
	    prevptr->next = chain->next;
	free(chain->state);
	free(chain->plate);
	free(chain);
    }
    return 0;
}
#endif
