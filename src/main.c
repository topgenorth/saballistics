/***************************************************************************
                          main.c  -  description
                             -------------------
    begin                : Tue Mar 30 10:42:09 EST 2004
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
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>

#include <curses.h>
#include <menu.h>
#include <form.h>

#include "main.h"
#include "curses_func.h"
#include "menu_handlers.h"
#include "form_handlers.h"
#include "messages.h"
#include "drag_models.h"
#include "trajectory_funcs.h"
#include "window_backgrounds.h"
#include "main_menu.h"

/* global variables */
bullet_t bullet = { 1.0, 1.0, 7000.0, g1};
wind_t wind = {0.0, 0.0, 0.0};
firearm_t firearm = {1000.0, 0.0, 0.0, 100.0};
calcparam_t calcparam = {MAXTIME, METRIC, 0, POINTSPERSEC, 0.0, 0.0, 0.0, 0.0};
printparam_t printparam = {0.0, 1000.0, 50.0};
void (*func_ptr)(void);
unsigned int handler;


int main(int argc, char *argv[])
{

  /* catch term signals and reset terminal */
  signal(SIGINT, finish);
  signal(SIGFPE, finish);

  /* start up the app window */
  init_curses();

  /* start the interface */
  splashscreen();

  handler = MENU_HANDLER;
  create_mainmenu();
  
  while(TRUE) {
    if (handler==MENU_HANDLER) {
      display_menu();
      menu_handler();
    }
    else {
      display_form();
      form_handler();
    }
    func_ptr();
  }

  return EXIT_SUCCESS;
}
