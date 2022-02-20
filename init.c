#include "defs.h"

/*
    Function  : initRace
    Purpose   : initialize the race
*/
void initRace()
{
  RunnerType *r1;
  RunnerType *r2;

  //3.3.1
  race = (RaceInfoType *)malloc(sizeof(RaceInfoType));    //a
  race->numDorcs = 0;
  race->numRunners = 0;
  race->statusRow = STATUS_ROW;


  initRunner(&r1, "Timmy","T",PATH_1);
  //3.3.1.b
  addRunner(&r1);

  initRunner(&r2, "Herald","H",PATH_2);
  //3.3.1.b
  addRunner(&r2);


  //3.3.1.c
  if (sem_init(&(race->mutex), 0, 1) < 0) {
    printf("semaphore initialization error\n");
    exit(1);
  }
  //3.3.1.d
  strcpy(race->winner,"");

  //3.3.1.e
  race->statusRow = STATUS_ROW;

  //3.3.2
  srand((unsigned)time(NULL));

  //3.3.3
  initNcurses();

  scrPrt("------------------------",END_POS-1,0);
  scrPrt("------------------------",START_POS+1,0);

  //3.3.4
  char healthBar[MAX_BUF];
  sprintf(healthBar,"HEALTH:   %2s  %2s",race->runners[0]->ent.avatar, race->runners[1]->ent.avatar);
  scrPrt(healthBar,HEALTH_ROW,HEALTH_COL);

  char health[MAX_BUF];
  sprintf(healthBar,"          %2d  %2d",race->runners[0]->health, race->runners[1]->health);
  scrPrt(healthBar,HEALTH_ROW + 2,HEALTH_COL);

  //3.3.5
  pthread_create(&(r1->ent.thr),NULL, goRunner, r1);
  pthread_create(&(r2->ent.thr),NULL, goRunner, r2);

  
  for (int i = 0; i < race->numRunners; i++){
    scrPrt(race->runners[i]->ent.avatar,race->runners[i]->ent.currPos,race->runners[i]->ent.path);
  }
}

/*
    Function  : initRunner
    Purpose   : initialize a runner
    out       : double pointer to a runner
    in        : runner name
    in        : runner's avatar
    in        : runner's path
*/
void initRunner(RunnerType **runner, char *name, char *avatar, int path)
{
    (*runner) = (RunnerType *)malloc(sizeof(RunnerType));
    EntityType *ent;
    //initEntity(&ent,avatar,START_POS,path);
    strcpy((*runner)->name, name);
    (*runner)->dead = C_FALSE;
    (*runner)->health = MAX_HEALTH;

    strcpy((*runner)->ent.avatar,avatar);
    (*runner)->ent.currPos = START_POS;
    (*runner)->ent.path = path;
    
}

/*
    Function  : initEntity
    Purpose   : initialize an entity
    out       : double pointer to an entity
    in        : runner's avatar
    in        : runner's current position
    in        : runner's path
*/
void initEntity(EntityType **entity, char *avatar, int currPos, int path)
{
    (*entity) = malloc(sizeof(EntityType));
    strcpy((*entity)->avatar,avatar);
    (*entity)->currPos = currPos;
    (*entity)->path = path;
}

