/***************************************************************************
                          window_backgrounds.c  -  description
                             -------------------
    begin                : Tue Mar 30 2004
    copyright            : (C) 2004 by Joshua Weage
    email                : weage98@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <curses.h>
#include <string.h>
#include <unistd.h>

#include "window_backgrounds.h"
#include "curses_func.h"
#include "messages.h"
#include "main.h"

/* splashscreen */
void splashscreen(void) {
  
  int x;

  leaveok(stdscr,TRUE); /* try to turn off cursor, and don't move it */

  attrset(COLOR_PAIR(BG_PAIR));  /* setup colors */
  bkgdset(COLOR_PAIR(BG_PAIR));
  erase();    /* erase and color window */

  /* window size */
  getmaxyx(stdscr,LINES,COLS);

  /* print name and author at top */
  x = strlen(name_str) + strlen(author_str);
  x = (COLS - x) / 3;
  mvaddstr(1,x,name_str);  /* write name string */
  mvaddstr(1,2*x+strlen(name_str),author_str); /* write author string */

  x = strlen(info1);
  x = (COLS - x ) / 2;
  mvaddstr(8,x,info1);
  x = strlen(info2);
  x = (COLS - x ) / 2;
  mvaddstr(9,x,info2);
  x = strlen(info3);
  x = (COLS - x ) / 2;
  mvaddstr(10,x,info3);

  x = strlen(gpl1);
  x = (COLS - x ) / 2;
  mvaddstr(15,x,gpl1);
  mvaddstr(16,x,gpl2);
  mvaddstr(17,x,gpl3);
  mvaddstr(18,x,gpl4);

  move(0,COLS-1);

  refresh();
  sleep(3);
  return;
  
}

/* setup and display titlescreen */
void titlewindowbg(void) {
  
  int x;

  leaveok(stdscr,TRUE);	/* try to turn off cursor, and don't move it */

  attrset(COLOR_PAIR(BG_PAIR));  /* setup colors */
  bkgdset(COLOR_PAIR(BG_PAIR));
  erase();    /* erase and color window */

  /* window size */
  getmaxyx(stdscr,LINES,COLS);

  /* print name and author at top */
  x = strlen(name_str) + strlen(author_str);
  x = (COLS - x) / 3;
  mvaddstr(1,x,name_str);		/* write name string */
  mvaddstr(1,2*x+strlen(name_str),author_str); /* write author string */

  /* help line */
  x = (COLS - strlen(usage_str)) / 2;
  mvaddstr(LINES-2,x,usage_str);

  refresh();
  return;
  
}

/* add calculation parameters to background */
void calcwindowbg(void) {
  
int start_x, x;

  /* print title first */
  titlewindowbg();
  x = (COLS - strlen(calc_usage_str)) / 2;
  mvaddstr(LINES-2,x,calc_usage_str);

  if(calcparam.units == ENGLISH) {
    mvprintw(3,5,"Ballistic Coefficient: %5.3f",bullet.bc);
    mvprintw(4,5,"Bullet Weight:   %5.1f [grains]",bullet.weight);
    mvprintw(5,5,"Muzzle Velocity: %5.0f [ft/s]",firearm.v0);
    mvprintw(6,5,"Zero Distance:   %5.0f [yds]",firearm.zero);
    mvprintw(3,45,"Sight-Bore Distance: %4.2f [in]",firearm.height);
    mvprintw(4,45,"Wind Velocity:  %5.1f [ft/s]",wind.z);
    mvprintw(5,45,"Starting Range: %5.0f [yds]",printparam.start);
    mvprintw(6,45,"Ending Range:   %5.0f [yds]",printparam.end);
  }
  else {
    mvprintw(3,5,"Ballistic Coefficient: %5.3f",bullet.bc);
    mvprintw(4,5,"Bullet Weight:   %4.1f [grams]",bullet.weight);
    mvprintw(5,5,"Muzzle Velocity: %5.0f [m/s]",firearm.v0);
    mvprintw(6,5,"Zero Distance:   %5.0f [m]",firearm.zero);
    mvprintw(3,45,"Sight-Bore Distance: %4.3f [m]",firearm.height);
    mvprintw(4,45,"Wind Velocity:  %5.1f [m/s]",wind.z);
    mvprintw(5,45,"Starting Range: %5.0f [m]",printparam.start);
    mvprintw(6,45,"Ending Range:   %5.0f [m]",printparam.end);
  }


  start_x = (COLS - strlen(calc_headings)) / 2;
 
  mvprintw(8,start_x,"%s",calc_headings);
  if(calcparam.units == METRIC)
    mvprintw(9,start_x,"%s",calc_units_m);
  else
    mvprintw(9,start_x,"%s",calc_units_e);

  refresh();
  return;
}

/* standard form background */
void formbg(void) {
  
  int x = 0;

  leaveok(stdscr,TRUE);	/* try to turn off cursor, and don't move it */

  attrset(COLOR_PAIR(BG_PAIR)); /* setup colors */
  bkgdset(COLOR_PAIR(BG_PAIR));
  erase();                      /* erase and color window */

  getmaxyx(stdscr,LINES,COLS);
  x += strlen(name_str) + strlen(author_str);
  x = (COLS - x) / 3;

  mvaddstr(1,x,name_str);		/* write name string */
  mvaddstr(1,2*x+strlen(name_str),author_str);

  x = (COLS - strlen(modusage_str)) / 2;
  mvaddstr(LINES-2,x,modusage_str);

  refresh();
  return;
  
}
