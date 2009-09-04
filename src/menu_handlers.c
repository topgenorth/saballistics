/***************************************************************************
                          menu_handlers.c  -  description
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

#include "menu_handlers.h"
#include "curses_func.h"
#include "messages.h"
#include "main.h"


/* display current menu */
void display_menu() {
  
  int rows, cols, begin_y, begin_x;

  /* setup menu options */
  menu_opts_off(menu_ptr, O_ROWMAJOR);
  set_menu_fore(menu_ptr, COLOR_PAIR(MENU_PAIR) | A_STANDOUT);
  set_menu_back(menu_ptr, COLOR_PAIR(MENU_PAIR) | A_DIM | A_NORMAL);

  /* setup appropriate windows */
  set_menu_win(menu_ptr, stdscr);
  scale_menu(menu_ptr, &rows, &cols);

  /* locate menu in the center */
  getmaxyx(stdscr,LINES,COLS);
  begin_y = (LINES-rows) / 2;
  begin_x = (COLS-cols) / 2;

  /* create main menu window */
  sub_window = subwin(stdscr, rows, cols, begin_y, begin_x);
  set_menu_sub(menu_ptr, sub_window);

  /* display the menu */
  post_menu(menu_ptr);
  refresh();
  
}

/* delete space for current menu */
void delete_menu(void) {
  
  int i;

  /* unpost the menu */
  unpost_menu(menu_ptr);
  /* free menu space */
  free_menu(menu_ptr);
  
  /* free item space */
  i = 0;
  while(my_menu_items[i] != NULL) {
    free_item(my_menu_items[i]);
    i++;
  }

  free(my_menu_items);
  my_menu_items = NULL;

  /* delete the subwindow */
  delwin(sub_window);
  refresh();
  
}

/* menu handler */
void menu_handler(void) {

  int c;

  keypad(sub_window,TRUE);  /* enable keypad on the menu */
  wtimeout(sub_window,-1);  /* wait for input */

  while((c=wgetch(sub_window))) {
    switch (c) {
      case KEY_MOUSE:
        menu_driver(menu_ptr,KEY_MOUSE);
        break;
      case 9: /* TAB */
      case 'k':
      case KEY_DOWN:
        menu_driver(menu_ptr,REQ_DOWN_ITEM);
        break;
      case 'j':
      case KEY_UP:
        menu_driver(menu_ptr,REQ_UP_ITEM);
        break;
      case 27:  /* ESC */
      case 'q':
        delete_menu();
        finish(0);
        break;
      case 13:
      case KEY_ENTER:
      case KEY_RIGHT:
        func_ptr = item_userptr(current_item(menu_ptr));
        delete_menu();
        return;
      default: break;
    }
  }
  
  return;
}

