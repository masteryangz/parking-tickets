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

#ifndef MYFREETICKETS
TODO(USING THE SOLUTION freetickets.c NOT MY CODE)
#else

/*
 * freetickets
 *      tears down the database freeing all allocated memory
 *      count the number of tickets freed in the database and
 *      print it out before returning
 *
 *      unsigned long cnt = 0UL
 *      printf("Total tickets freed: %lu\n", cnt);
 */
void
freetickets(void)
{
    int empty = 1; // set to zero when there is at least one vehicle in the database
    /*
     * walk down each chain
     */
    struct vehicle **ptr = htable;
    struct vehicle *vptr;
    struct vehicle **endptr = htable+tabsz;
    long unsigned int cnt = 0;
    struct ticket *tptr;
    struct ticket *pretptr;
    struct vehicle *prevptr;
    while (ptr < endptr) {
	vptr = *ptr;
	while (vptr != NULL){
	    empty = 0;
            free(vptr->state);
	    free(vptr->plate);
	    tptr = vptr->head;
	    while (tptr != NULL) {
		pretptr = tptr;
	        tptr = tptr->next;
	        cnt++;
	        free(pretptr);
	    }
	    pretptr = NULL;
	    prevptr = vptr;
	    vptr = vptr->next;
	    free(prevptr);
        }
	prevptr = NULL;
	*ptr = NULL;
	ptr++;
    }
    /*
     * remove all the tickets for all vehicles
     * on this chain
     */

    /*
     * free the vehicle
     */

    /*
     * chain is removed, update the htable entry
     */
    if (empty)
        printf("Empty Database\n");
    printf("Total tickets freed: %lu\n", cnt);
    return;
}
#endif
