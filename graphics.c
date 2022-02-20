#include "defs.h"

/*
    Function  : initNcurses
    Purpose   : initialize the ncurses library
*/
void initNcurses()
{
  initscr();
  curs_set(0);
  clear();
}

/*
    Function  : cleanupNcurses
    Purpose   : to clean up the resources used by ncurses
    in:       : last row of the screen to clean
*/
void cleanupNcurses(int row)
{
  move(row, 0);
  addstr("Press any key to continue...");
  getch();
  endwin();
}

/*
    Function  : scrPrt
    Purpose   : output a string to the screen at a specific row and column
    out:      : string to print
    in:       : row of the string
    in:       : column of the string
*/
void scrPrt(char *str, int row, int col)
{
  move(row, col);
  addstr(str);
  refresh();
}

/*
    Function  : randm
    Purpose   : generate and return a random number between 0 and max - 1
    in:       : max number
*/
int randm(int max)
{
  double r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) ); 
  return (int)(r * max);
}

