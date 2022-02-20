#include "defs.h"

/*
    Function  : raceLoop
    Purpose   : start and iterate the race loop
*/
void raceLoop(){
    //3.4
    while (strcmp(race->winner,"") == 0)
    {   
        int alldead = C_FALSE;
        for (int i = 0; i<race->numRunners; i++){
            if (race->runners[i]->dead == C_FALSE){
                alldead = C_FALSE;
                break;
            }
            else {
                alldead = C_TRUE;
            }
        }

        if (alldead == C_TRUE) {
            break;
        }

        //3.4.1
        if (race->numDorcs < MAX_DORCS)
        {
            if (randm(10) > 6){

                EntityType *newDorc;

                int path;
                int lane = randm(9);
                if (lane < 3){
                    path = PATH_1;
                } else if (lane < 6){
                    path = PATH_2;
                } else {
                    path = (PATH_1+PATH_2)/2;
                }

                initEntity(&newDorc,"d",END_POS,path);

                race->dorcs[race->numDorcs] = newDorc;
                race->numDorcs++;

                pthread_create(&(newDorc->thr), NULL, goDorc, newDorc);
            }          
        }

        //3.4.2
        usleep(250000);

    }
}

/*
    Function  : lockSem
    Purpose   : lock the race’s semaphore
*/
void lockSem(){
    if (sem_wait(&(race->mutex)) < 0) {
        printf("semaphore wait error\n");
        exit(1);
    }
}

/*
    Function  : unloSem
    Purpose   : unlock the race’s semaphore
*/
void unloSem(){
    if (sem_post(&race->mutex) < 0) {
        printf("semaphore post error\n");
        exit(1);
    }
}