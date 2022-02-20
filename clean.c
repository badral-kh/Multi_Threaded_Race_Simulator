#include "defs.h"

/*
    Function  : clean
    Purpose   : free the dynamically allocated memories.
*/
void clean()
{
    for(int i = 0; i < race->numDorcs; i++){
        free(race->dorcs[i]);
    }

    for(int i = 0; i < race->numRunners; i++){
        free(race->runners[i]);
    }

    free(race);
}