#include "defs.h"

/*
    Function  : printOutcome
    Purpose   : print the outcome of the race on the screen
*/
void printOutcome(){
    //3.4.5
    for (int i = 0; i < race->numRunners; i++){
        if (strcmp(race->runners[i]->name, race->winner) == 0){
            char out[MAX_BUF]= "OUTCOME: The winner is ";
            strcat(out,race->winner);
            scrPrt(out,race->statusRow,STATUS_COL);
            break;
        }
    }

    int all_rip = 1;
    for (int i = 0; i < race->numRunners; i++){
        if (race->runners[i]->dead == C_FALSE){
            all_rip = 0;
            break;
        }
    }
    if (all_rip == 1){
        scrPrt("OUTCOME: all runners are dead",race->statusRow,STATUS_COL);
    }
}