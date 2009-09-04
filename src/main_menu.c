/***************************************************************************
                          main_menu.c  -  description
                             -------------------
    begin                : Thu Apr 1 2004
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

#include <assert.h>
#include <stdlib.h>

#include "main.h"
#include "window_backgrounds.h"
#include "curses_func.h"
#include "function_tables.h"
#include "messages.h"


/* setup main menu */
void create_mainmenu(void) {

  int i;

  /* set correct handler */
  handler = MENU_HANDLER;

  /* setup background */
  titlewindowbg();

  /* allocate space for menu items */
  assert(my_menu_items == NULL);

  my_menu_items = malloc((MAIN_MENU_OPTIONS + 1) * sizeof(ITEM *));
  if ( my_menu_items == NULL ) {
    fprintf(stderr,"create_mainmenu(): Out of memory\n");
    finish(0);
  }

  /* add items to menu */  
  for (i = 0; i < MAIN_MENU_OPTIONS; i++)
    my_menu_items[i] = new_item(mainmenu_options[i],mainmenu_help[i]);
    
  my_menu_items[MAIN_MENU_OPTIONS] = NULL;

  /* set handler functions */
  for (i=0; i < MAIN_MENU_OPTIONS; i++ )
    set_item_userptr(my_menu_items[i], main_menu_table[i]);

  /* create menu */
  menu_ptr = new_menu(my_menu_items);
  return;

}

