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

#ifndef MYVEHLOOKUP
TODO(USING THE SOLUTION vehlookup.c NOT MY CODE)
#else

/*
 * vehiclelookup
 *          look for vehicle in the database
 *          vehicle must match both plate and state strings
 * args
 *  plate   plate id string to be found
 *  state   state id string to be found
 *
 * returns  pointer to vehicle if found NULL otherwise
 */

struct vehicle *
vehiclelookup(char *plate, char *state)
{
    uint32_t hashval;
    struct vehicle *chain;
    hashval = hash(plate) % tabsz;
    chain = *(htable + hashval);
    while (chain != NULL) {
        if ((strcmp(plate, chain->plate) == 0) && (strcmp(state, chain->state) == 0)) {
	    return chain;
	}
	chain = chain->next;
    }
    return NULL;

    /* your code here */

}
#endif
