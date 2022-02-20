#include "defs.h"

/*
    Function  : goRunner
    Purpose   : thread for a runner
    in        : pointer to a runner void
*/
void *goRunner(void *runner)
{
    //3.5.1
    RunnerType* r = runner;
    
    //3.5.2
    int d_pos;      // change of position
    int newPos;     // new position
    while (r->dead == C_FALSE && r->ent.currPos > END_POS){

        //3.5.2.a
        int rand10 = randm(10);

        if (rand10 < 7){
            int rand4 = randm(4) + 1;
            d_pos = rand4;

            if (r->health >= d_pos){
                r->health -= d_pos;
            } else {
                d_pos = 0;
                r->health = 0;
                r->dead = C_TRUE;
            }
        } else {
            int rand3 = randm(3) + 1;
            d_pos = (rand3)* (-1);
        }

        newPos = r->ent.currPos - d_pos;
        
        //set position to border position if the runner passes the border.
        if (newPos > START_POS){
            newPos = START_POS;
        }
        if (newPos < END_POS){
            newPos = END_POS;
        }

        //3.5.2.b
        lockSem();                      //i

        for (int i = 0; i <race->numDorcs; i++){         //ii
            if ((race->dorcs[i]->currPos == r->ent.currPos) && (race->dorcs[i]->path == r->ent.path)){
                char prt[MAX_BUF];
                sprintf(prt,"STATUS:  collision between %s and dorc",r->name);
                scrPrt(prt,race->statusRow,STATUS_COL);
                race->statusRow++;

                if (r->health > 2){     //iii.
                    r->health -= 3;
                } else {
                    r->health = 0;
                }
            }
        }
        unloSem();                      //iv

        lockSem();

        //3.5.2.c
        if (r->health <= 0){
            strcpy(r->ent.avatar, "+");
            r->dead = C_TRUE;
            char prt[MAX_BUF];
            sprintf(prt,"STATUS:  %s is dead",r->name);
            scrPrt(prt,race->statusRow,STATUS_COL);
            (race->statusRow)++;
        }

        unloSem();

        //3.5.2.d
        lockSem();

        moveRunner(r,newPos);
        char hp[MAX_BUF];
        sprintf(hp,"%2d",r->health);
        scrPrt(hp,HEALTH_ROW + 2,HEALTH_COL+r->ent.path);

        unloSem();

        r->ent.currPos = newPos;
        usleep(250000);

    }
    //3.5.3
    if (r->dead == C_FALSE && strcmp(race->winner,"") == 0){
        strcpy(race->winner,r->name);
    }
    //3.5.4
    lockSem();
    scrPrt(r->ent.avatar,r->ent.currPos,r->ent.path);
    unloSem();
}


/*
    Function  : goDorc
    Purpose   : thread for a dorc
    in        : pointer to a dorc void
*/
void *goDorc(void *dorc)
{
    //3.6.1
    EntityType* d = dorc;

    //3.6.2
    int newRow, newCol;
    while (d->currPos < START_POS){

        //3.6.2.a
        int rand5 = randm(5) + 1;
        newRow = d->currPos + rand5;

        if (newRow > START_POS){
            newRow = START_POS;
        }

        int rand3 = randm(3);

        if (rand3 == 0){    //go left 2
            if (d->path != PATH_1){
                newCol = d->path - 2;
            } else { 
                newCol = d->path;
            }
        } else if (rand3 == 1){
            newCol = d->path;
        } else {
            if (d->path != PATH_2){
                newCol = d->path + 2;
            } else {
                newCol = d->path;
            }
        }

        //3.6.2.b
        lockSem();
        
        moveDorc(d,newRow,newCol);

        unloSem();

        //3.6.2.c
        d->currPos = newRow;
        d->path = newCol;

        //3.6.2.d
        usleep(700000);
    }
    scrPrt(" ",d->currPos,d->path);

}

/*
    Function  : addRunner
    Purpose   : add a runner to the race
    in        : double pointer to a runner
*/
void addRunner(RunnerType **runner){
    if(race->numRunners != MAX_RUNNERS){
        race->runners[race->numRunners] = *runner;
    } else {
        printf("can not add no more runners.");
    }
    race->numRunners++;
}
/*
    Function  : addDorc
    Purpose   : add a dorc to the race
    in        : double pointer to a dorc
*/
void addDorc(EntityType **dorc){
    if(race->numDorcs != MAX_DORCS){
        race->dorcs[race->numDorcs] = *dorc;
    } else {
        printf("can not add no more dorcs.");
    }
}

/*
    Function  : moveRunner
    Purpose   : move and print the runner into a new postion, fill the last position with blank.
    in        : pointer to a runner
    in        : row of the new position
*/
void moveRunner(RunnerType* r, int newPos){
    scrPrt(" ", r->ent.currPos,r->ent.path);
    scrPrt(r->ent.avatar, newPos, r->ent.path);
}

/*
    Function  : moveDorc
    Purpose   : move and print the dorc into a new postion, fill the last position with blank.
    in        : pointer to a dorc
    in        : row of the new position
    in        : column of the new position
*/
void moveDorc(EntityType* d, int newRow, int newCol){
    scrPrt(" ",d->currPos,d->path);
    scrPrt(d->avatar,newRow,newCol);
}