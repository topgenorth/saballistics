/***************************************************************************
                          modify_parameters.c  -  description
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

#include <curses.h>
#include <menu.h>
#include <form.h>
#include <stdlib.h>
#include <stdio.h>

#include "modify_parameters.h"
#include "messages.h"
#include "curses_func.h"
#include "form_handlers.h"
#include "window_backgrounds.h"
#include "main.h"
#include "main_menu.h"

static void modify_parameters_form_init(FORM *);
static void modify_parameters_form_term(FORM *);

/* setup modify bullet menu */
void modify_parameters(void) {
  
  int i;

  /* set correct handler */
  handler = FORM_HANDLER;

  /* setup background */
  formbg();

  /* set changable field attributes */
  set_field_fore(NULL, COLOR_PAIR(FORM_FIELD_PAIR) | A_NORMAL);
  set_field_back(NULL, COLOR_PAIR(FORM_FIELD_PAIR) | A_REVERSE);

  /* create float form items */
  set_field_type(NULL, TYPE_NUMERIC, 4, 0.0, 0.0);

  /* 10 fields, numbered as follows:
    0. B.C.
    1. bullet weight
    2. wind
    3. muzzle velocity
    4. sight height
    5. zero distance
    6. elevation angle
    7. starting range
    8. ending range
    9. step size */
  for (i=0; i<10; i++)
    field_items_ptr[i] = new_field(1,8,i+1,1,0,0);  /* B.C. */

  /* create field labels */
  set_field_fore(NULL, COLOR_PAIR(BG_PAIR));
  set_field_back(NULL, COLOR_PAIR(BG_PAIR));

  for (i=10; i<20; i++) 
    field_items_ptr[i] = new_field(1,PARAMETERS_WIDTH,i-9,10,0,0);

  /* done button */
  set_field_fore(NULL, COLOR_PAIR(BG_PAIR) | A_REVERSE | A_DIM);
  set_field_back(NULL, COLOR_PAIR(BG_PAIR) | A_REVERSE | A_DIM);

  field_items_ptr[20] = new_field(1,8,12,10,0,0);
  done_field = 20;

  field_items_ptr[21] = NULL;

  /* set input field options */
  for(i=0; i<9; i++)
    field_opts_off(field_items_ptr[i], O_NULLOK);

  /* put labels onto the items */
  if(calcparam.units == ENGLISH) {
    for(i=10; i <= 19; i++) {
      set_field_buffer(field_items_ptr[i],0,calculation_parameters_e[i-10]);
      field_opts_off(field_items_ptr[i], O_ACTIVE | O_EDIT);
    }
  }
  else {
    for(i=10; i <= 19; i++) {
      set_field_buffer(field_items_ptr[i],0,calculation_parameters_m[i-10]);
      field_opts_off(field_items_ptr[i], O_ACTIVE | O_EDIT);
    }
  }

  /* label done button */
  set_field_buffer(field_items_ptr[20],0,done_str);
  field_opts_off(field_items_ptr[20], O_EDIT);

  /* create new form */
  form_ptr = new_form(field_items_ptr);

  /* setup form handler functions */
  set_form_init(form_ptr, modify_parameters_form_init);
  set_form_term(form_ptr, modify_parameters_form_term);

  /* go to main menu when form is done */
  set_form_userptr(form_ptr,create_mainmenu);

}

/* fill in the modify parameters form */
static void modify_parameters_form_init(FORM *myform) {
  
char temp[9];

  sprintf(temp, "%.3f", bullet.bc);
  set_field_buffer(field_items_ptr[0], 0, temp);
  sprintf(temp, "%.3f", bullet.weight);
  set_field_buffer(field_items_ptr[1], 0, temp);
  sprintf(temp, "%.3f", wind.z);
  set_field_buffer(field_items_ptr[2], 0, temp);
  sprintf(temp, "%.3f", firearm.v0);
  set_field_buffer(field_items_ptr[3], 0, temp);
  sprintf(temp, "%.3f", firearm.height);
  set_field_buffer(field_items_ptr[4], 0, temp);
  sprintf(temp, "%.3f", firearm.zero);
  set_field_buffer(field_items_ptr[5], 0, temp);
  sprintf(temp, "%.3f", firearm.angle);
  set_field_buffer(field_items_ptr[6], 0, temp);
  sprintf(temp, "%.3f", printparam.start);
  set_field_buffer(field_items_ptr[7], 0, temp);
  sprintf(temp, "%.3f", printparam.end);
  set_field_buffer(field_items_ptr[8], 0, temp);
  sprintf(temp, "%.3f", printparam.step);
  set_field_buffer(field_items_ptr[9], 0, temp);

}

/* retrieve data from modify parameters form */
static void modify_parameters_form_term(FORM *myform) {
  
char *temp;

  temp = field_buffer(field_items_ptr[0], 0);
  bullet.bc = atof(temp);
  temp = field_buffer(field_items_ptr[1], 0);
  bullet.weight = atof(temp);
  temp = field_buffer(field_items_ptr[2], 0);
  wind.z = atof(temp);
  temp = field_buffer(field_items_ptr[3], 0);
  firearm.v0 = atof(temp);
  temp = field_buffer(field_items_ptr[4], 0);
  firearm.height = atof(temp);
  temp = field_buffer(field_items_ptr[5], 0);
  firearm.zero = atof(temp);
  temp = field_buffer(field_items_ptr[6], 0);
  firearm.angle = atof(temp);
  temp = field_buffer(field_items_ptr[7], 0);
  printparam.start = atof(temp);
  temp = field_buffer(field_items_ptr[8], 0);
  printparam.end = atof(temp);
  temp = field_buffer(field_items_ptr[9], 0);
  printparam.step = atof(temp);

}
