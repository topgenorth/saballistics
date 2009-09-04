/***************************************************************************
                          calc_bc.c  -  description
                             -------------------
    begin                : Fri Apr 2 2004
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
#include <string.h>

#include "calc_bc.h"
#include "trajectory_funcs.h"
#include "messages.h"
#include "curses_func.h"
#include "form_handlers.h"
#include "window_backgrounds.h"
#include "main.h"
#include "main_menu.h"

#define FORM_FIELD_WIDTH 8

static void calc_bc_form_init(FORM *);
static void calc_bc_form_term(FORM *);
static void show_calc_bc(void);

calc_bc_param_t calc_bc_param = {0.0, 1000.0, 100.0, 900.0};

/* setup ballistic coefficient calculation */
void calc_bc(void) {
  
int i;

  /* use global form handler function */
  handler = FORM_HANDLER;

  /* setup background */
  formbg();

  /* set changable field attributes */
  set_field_fore(NULL, COLOR_PAIR(MENU_PAIR) | A_STANDOUT | A_DIM);
  set_field_back(NULL, COLOR_PAIR(MENU_PAIR) | A_REVERSE | A_DIM);
  /* field_opts_off(NULL, O_BLANK); */

  /* create float form items */
  set_field_type(NULL, TYPE_NUMERIC, FORM_FIELD_WIDTH, 0.0, 5000.0);
  field_items_ptr[0] = new_field(1,FORM_FIELD_WIDTH,1,1,0,0);	/* X0 */
  field_items_ptr[1] = new_field(1,FORM_FIELD_WIDTH,2,1,0,0);	/* V0 */
  field_items_ptr[2] = new_field(1,FORM_FIELD_WIDTH,4,1,0,0);	/* X1 */
  field_items_ptr[3] = new_field(1,FORM_FIELD_WIDTH,5,1,0,0);	/* V1 */

  /* create field labels */
  set_field_fore(NULL, COLOR_PAIR(BG_PAIR));
  set_field_back(NULL, COLOR_PAIR(BG_PAIR));
  field_items_ptr[4] = new_field(1,CALC_BC_WIDTH,1,10,0,0);
  field_items_ptr[5] = new_field(1,CALC_BC_WIDTH,2,10,0,0);
  field_items_ptr[6] = new_field(1,CALC_BC_WIDTH,4,10,0,0);
  field_items_ptr[7] = new_field(1,CALC_BC_WIDTH,5,10,0,0);

  /* done button */
  set_field_fore(NULL, COLOR_PAIR(BG_PAIR) | A_REVERSE | A_DIM);
  set_field_back(NULL, COLOR_PAIR(BG_PAIR) | A_REVERSE | A_DIM);
  field_items_ptr[8] = new_field(1,8,7,10,0,0);
  done_field = 8;

  /* end of items */
  field_items_ptr[9] = NULL;

  /* set input field options */
  for(i=0; i<4; i++)
    field_opts_off(field_items_ptr[i], O_NULLOK);

  /* put labels into the items */
  if(calcparam.units == ENGLISH) {
    for(i=4; i <= 7; i++) {
      set_field_buffer(field_items_ptr[i],0,calc_bc_e[i-4]);
      field_opts_off(field_items_ptr[i], O_ACTIVE | O_EDIT);
    }
  }
  else {
    for(i=4; i <= 7; i++) {
      set_field_buffer(field_items_ptr[i],0,calc_bc_m[i-4]);
      field_opts_off(field_items_ptr[i], O_ACTIVE | O_EDIT);
    }
  }

  set_field_buffer(field_items_ptr[done_field],0,done_str);


  /* create new form */
  form_ptr = new_form(field_items_ptr);

  /* setup form handler functions */
  set_form_init(form_ptr, calc_bc_form_init);
  set_form_term(form_ptr, calc_bc_form_term);

  /* set place to return when form is done */
  set_form_userptr(form_ptr,show_calc_bc);

}

/* calculate bc form term function */
static void calc_bc_form_init(FORM *myform) {
  
char temp[FORM_FIELD_WIDTH+1];

  snprintf(temp,FORM_FIELD_WIDTH+1, "%.3f",calc_bc_param.x0);
  set_field_buffer(field_items_ptr[0], 0, temp);
  snprintf(temp,FORM_FIELD_WIDTH+1, "%.3f",calc_bc_param.v0);
  set_field_buffer(field_items_ptr[1], 0, temp);
  snprintf(temp,FORM_FIELD_WIDTH+1, "%.3f",calc_bc_param.x1);
  set_field_buffer(field_items_ptr[2], 0, temp);
  snprintf(temp,FORM_FIELD_WIDTH+1, "%.3f",calc_bc_param.v1);
  set_field_buffer(field_items_ptr[3], 0, temp);

}

/* calculate bc form term function */
static void calc_bc_form_term(FORM *myform) {
  
char *temp;

  temp = field_buffer(field_items_ptr[0], 0);
  calc_bc_param.x0 = atof(temp);
  temp = field_buffer(field_items_ptr[1], 0);
  calc_bc_param.v0 = atof(temp);
  temp = field_buffer(field_items_ptr[2], 0);
  calc_bc_param.x1 = atof(temp);
  temp = field_buffer(field_items_ptr[3], 0);
  calc_bc_param.v1 = atof(temp);

}

/* show calculated bc */
static void show_calc_bc(void) {
  
float dist, vel;
int i,j,x,y;

  /* setup background */
  titlewindowbg();

  /* calculate trajectory of default bullet */
  bullet.bc = 1.0;
  firearm.v0 = calc_bc_param.v0;
  firearm.angle = 0.0;
  wind.x = wind.y = wind.z = 0.0;
  calctraj();

  /* find distance */
  dist = calc_bc_param.x1 - calc_bc_param.x0;
  if(calcparam.units == ENGLISH)
    dist *= 3.0;

  /* find standard velocity at distance */
  j = 1;
  while ( j < calcparam.nstep && drop_array[1][j] < dist)
    j++;

  vel = linint(drop_array[1][j-1],drop_array[0][j-1],drop_array[1][j],drop_array[0][j],dist);

  /* calculate bc & free memory */
  bullet.bc = (calc_bc_param.v0 - vel) / (calc_bc_param.v0 - calc_bc_param.v1);
  freetraj();

  /* print BC */
  y = LINES/2;
  x = (COLS - strlen(calc_bc_results) - 5) / 2;
  mvprintw(y,x,"%s %.3f",calc_bc_results,bullet.bc);

  refresh();

  /* wait for 'q' */
  i = TRUE;
  while(i==TRUE) {
    j = getch();
    switch (j) {
      case 27:	/* ESC */
      case 'q':
        i = FALSE;
      default:
      break;
    }
  }

  /* setup screen for return to main loop */
  create_mainmenu();
  return;

}
