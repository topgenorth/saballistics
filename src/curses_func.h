/***************************************************************************
                          curses_func.h  -  description
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
#include <menu.h>
#include <form.h>

/* Color Pairs */
#define BG_PAIR 1
#define BG_PAIR_RV 2
#define MENU_PAIR 3
#define MENU_PAIR_RV 4
#define FORM_FIELD_PAIR 5

/* global curses related variables */
extern WINDOW *sub_window;
extern ITEM **my_menu_items;
extern MENU *menu_ptr;
extern int done_field;            /* set to "complete" button field */
extern FIELD *field_items_ptr[];
extern FORM *form_ptr;

/* functions */
extern void init_curses(void);
extern RETSIGTYPE finish(int);

