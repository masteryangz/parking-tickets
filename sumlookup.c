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

#ifndef MYSUMLOOKUP
TODO(USING THE SOLUTION sumlookup.c NOT MY CODE)
#else

/*
 * summlookup
 *     find the vehicle with a specified summons number
 * Input:
 *      summ: string of summons number
 * returns:   a pointer to the vehicle
 */
struct vehicle *
sumlookup(char *summ)
{
    unsigned long long summid;
    if (strtosumid(summ, &summid) != 0) {
	fprintf(stderr, "%s:sumlookup bad summons number:%s\n", argv0, summ);
	return NULL;
    }
    struct vehicle **ptr = htable;
    struct vehicle **endptr = htable + tabsz;
    struct vehicle *vptr;
    struct ticket *tptr;
    while (ptr < endptr) {
	vptr = *ptr;
	while (vptr != NULL) {
            tptr = vptr->head;
	    while (tptr != NULL) {
	        if ((tptr->summons) == summid) {
	            return vptr;
	        }
	        tptr = tptr->next;
	    }
	    vptr = vptr->next;
	}
	ptr++;
    }
    return NULL;
}
#endif
