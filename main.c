#include "defs.h"

int main(){

    //3.3
    initRace();
    
    //3.4
    raceLoop();

    //3.4.3
    for (int i = 0; i< race->numRunners;i++){
        pthread_join(race->runners[i]->ent.thr,NULL);
    }

    //3.4.4
    for (int i = 0; i< race->numDorcs;i++){
        pthread_cancel(race->dorcs[i]->thr);
    }

    //3.4.5
    printOutcome();

    //3.4.6
    cleanupNcurses(START_POS + 2);

    return 0;
}
