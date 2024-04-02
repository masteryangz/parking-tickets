#include <limits.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "parking.h"

#ifndef MYLARGEST
TODO(USING THE SOLUTION largest.c NOT MY CODE)
#else

/*
 * largest
 *     find the vehicle with the largest number of
 *     tickets and largest fine in database
 *     and print it
 */
void
largest(void)
{
    struct vehicle *count = NULL; // vehicle with largest number of tickets
    struct vehicle *fine = NULL;  // vehicle with largest total fine

/* your code here */
    unsigned int largestfine = 0;
    unsigned int greatestvehicle = 0;
    struct vehicle **ptr = htable;
    struct vehicle **endptr = htable + tabsz;
    struct vehicle *vptr;
    while (ptr < endptr) {
	vptr = *ptr;
        while (vptr != NULL) {
	    if (vptr->cnt_ticket >= greatestvehicle) {
	        count = vptr;
		greatestvehicle = count->cnt_ticket;
	    }
	    if (vptr->tot_fine >= largestfine) {
	        fine = vptr;
		largestfine = fine->tot_fine;
	    }
	    vptr = vptr->next;
	}
	ptr++;
    }

    if ((count == NULL) || (fine == NULL)) {
        printf("Empty database\n");
        return;
    }
    printf("Most tickets Plate: %s, State: %s tickets: %u, total fine: $%u\n",
            count->plate, count->state, count->cnt_ticket, count->tot_fine);
    printf("Largest fine Plate: %s, State: %s tickets: %u, total fine: $%u\n",
            fine->plate, fine->state, fine->cnt_ticket, fine->tot_fine);
    return;
}
#endif
