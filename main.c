#include "defs.h"

int main(){

    initRace();
    
    raceLoop();

    for (int i = 0; i< race->numRunners;i++){
        pthread_join(race->runners[i]->ent.thr,NULL);
    }

    for (int i = 0; i< race->numDorcs;i++){
        pthread_cancel(race->dorcs[i]->thr);
    }

    printOutcome();

    cleanupNcurses(START_POS + 2);

    return 0;
}
