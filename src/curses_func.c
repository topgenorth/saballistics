/***************************************************************************
                          curses_func.c  -  description
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curses.h>
#include <menu.h>
#include <form.h>

#include "curses_func.h"
#include "menu_handlers.h"
#include "form_handlers.h"
#include "modify_parameters.h"
#include "window_backgrounds.h"
#include "results_pad.h"
#include "messages.h"
#include "main.h"
#include "configuration.h"
#include "calc_bc.h"
#include "bullet_select.h"

/* global curses related variables defined here */
WINDOW *sub_window;
ITEM **my_menu_items;
MENU *menu_ptr;
int done_field;
FIELD *field_items_ptr[FORM_FIELDS];
FORM *form_ptr;

/* app initialization */
void init_curses(void) {

  /* initialize curses */
  if (!(initscr())) {
    fprintf(stderr,"initscr(): %s\n\n",initstring);
    exit(EXIT_FAILURE);
  }

  /* setup terminal */
  keypad(stdscr,TRUE);  /* enable keypad */
  nonl();                             
  cbreak();
  noecho();     /* don't echo keypresses */
  timeout(-1);
  mousemask(BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED |
    BUTTON1_TRIPLE_CLICKED, NULL);

  refresh(); /* cleanup window */

  /* initialize colors */
  start_color(); /* enable colors in curses */

  if (has_colors()) {             
    init_pair(BG_PAIR,COLOR_GREEN,COLOR_BLACK); /* title, lower windows */
    init_pair(BG_PAIR_RV,COLOR_BLACK,COLOR_GREEN); /* title, lower windows reverse video */
    init_pair(MENU_PAIR,COLOR_BLACK,COLOR_WHITE); /* menus */
    init_pair(MENU_PAIR_RV,COLOR_WHITE,COLOR_RED); /* menus reverse video */
    init_pair(FORM_FIELD_PAIR,COLOR_WHITE,COLOR_BLACK); /* form fields */
  }
  else {
    fprintf(stderr,"%s\n\n",need_color_str);
    endwin();
    exit(EXIT_FAILURE);
  }

  return;
}

/* signal handler and cleanup function */
RETSIGTYPE finish(int sig) {

  /* finalize curses and exit */
  endwin();
  exit(EXIT_SUCCESS);
}
