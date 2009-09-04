/***************************************************************************
                          form_handlers.c  -  description
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
#include <ctype.h>
#include <stdio.h>

#include "form_handlers.h"
#include "curses_func.h"
#include "main.h"

/* display current form */
void display_form() {
  
  int rows, cols, begin_y, begin_x;

  /* setup appropriate windows */
  set_form_win(form_ptr, stdscr);
  scale_form(form_ptr, &rows, &cols);

  /* locate menu in the center */
  getmaxyx(stdscr,LINES,COLS);
  begin_y = (LINES-rows) / 2;
  begin_x = (COLS-cols) / 2;

  /* create form window */
  sub_window = subwin(stdscr, rows, cols, begin_y, begin_x);
  keypad(sub_window,TRUE); /* enable keypad */
  wtimeout(sub_window,-1); /* wait for user input */

  /* set subwindow attributes */
  wattrset(sub_window,COLOR_PAIR(BG_PAIR));
  wbkgdset(sub_window,COLOR_PAIR(BG_PAIR));
  werase(sub_window);

  set_form_sub(form_ptr, sub_window);

  /* display the menu */
  post_form(form_ptr);
  refresh();
  
}

/* delete space for form */
void delete_form(void) {
  
  int i;

  /* unpost the form */
  unpost_form(form_ptr);
  /* free menu space */
  free_form(form_ptr);
  
  /* free item space */
  i = 0;
  while(field_items_ptr[i] != NULL) {
    free_field(field_items_ptr[i]);
    i++;
  }
  
  /* delete the subwindow */
  delwin(sub_window);
  refresh();
  
}

/* form handler */
void form_handler(void) {

  int c;
  int temp;

  while((c=wgetch(sub_window))) {
    switch (c) {
      case KEY_MOUSE:
        form_driver(form_ptr,KEY_MOUSE);
        break;
      case 9:
      case KEY_DOWN:
        form_driver(form_ptr,REQ_NEXT_FIELD);
        break;
      case KEY_UP:
        form_driver(form_ptr,REQ_PREV_FIELD);
        break;
      case KEY_LEFT:
        form_driver(form_ptr,REQ_PREV_CHAR);
        break;
      case KEY_RIGHT:
        temp = field_index(current_field(form_ptr));
        if (temp == done_field) {
          func_ptr = form_userptr(form_ptr);
          delete_form();
          return;
        }
        form_driver(form_ptr,REQ_NEXT_CHAR);
        break;
      case KEY_BACKSPACE:
        form_driver(form_ptr,REQ_DEL_PREV);
        break;
      case 111:
      case KEY_DC:
        form_driver(form_ptr,REQ_DEL_CHAR);
        break;
      case 'q':
      case 27:	/* ESC */
        func_ptr = form_userptr(form_ptr);
        delete_form();
        return;
      case 13:	/* CR */
      case KEY_ENTER:
        temp = field_index(current_field(form_ptr));
        if (temp == done_field) {
          func_ptr = form_userptr(form_ptr);
          delete_form();
          return;
        }
        form_driver(form_ptr,REQ_BEG_FIELD);
        break;
      default:
        form_driver(form_ptr,c);
        break;
    }
  }
  
  return;
}
