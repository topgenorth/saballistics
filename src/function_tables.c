/***************************************************************************
                          function_tables.c  -  description
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

 #include "function_tables.h"
 #include "messages.h"
 #include "configuration.h"
 #include "bullet_select.h"
 #include "curses_func.h"
 #include "drag_models.h"
 #include "modify_parameters.h"
 #include "results_pad.h"
 #include "calc_bc.h"

 void (*main_menu_table[MAIN_MENU_OPTIONS])() = {
   configuration,
   bullet_database,
   modify_parameters,
   results_pad,
   calc_bc,
   finish };

 double (*drag_table[NUM_DRAG_MODELS])(double) = {
   british,
   ingalls,
   g1,
   g2,
   g5,
   g6,
   g7,
   g8 };

