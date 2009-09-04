/***************************************************************************
                          configuration.c  -  description
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "messages.h"
#include "curses_func.h"
#include "form_handlers.h"
#include "main.h"
#include "configuration.h"
#include "function_tables.h"
#include "window_backgrounds.h"
#include "main_menu.h"

/* form fields */
#define UNIT_F 0
#define DRAG_F 1
#define TIME_F 2
#define IPTS_F 3
#define UNIT_L_F 4
#define DRAG_L_F 5
#define TIME_L_F 6
#define IPTS_L_F 7
#define DONE_F 8
#define RESET_F 9

/* parameter configuration form */
void configuration(void) {
  
  char **opt_str;
  char **opt_str1;
  int i;

  /* setup background */
  formbg();

  /* set changable field attributes */
  set_field_fore(NULL, COLOR_PAIR(FORM_FIELD_PAIR) | A_NORMAL );
  set_field_back(NULL, COLOR_PAIR(FORM_FIELD_PAIR) | A_REVERSE );
  /* field_opts_off(NULL, O_BLANK); */

  /* create ENUM type options */
  opt_str = (char **) calloc(3, sizeof(char *));
  opt_str[0] = units_str[0];
  opt_str[1] = units_str[1];
  opt_str[2] = NULL;
  opt_str1 = (char **) calloc(NUM_DRAG_MODELS+1, sizeof(char *));
  for(i = 0; i < NUM_DRAG_MODELS; i++ )
    opt_str1[i] = model_str[i];
  opt_str1[NUM_DRAG_MODELS] = NULL;


  /* create ENUM form items */
  set_field_type(NULL, TYPE_ENUM, opt_str, FALSE, TRUE);
  field_items_ptr[UNIT_F] = new_field(1,8,1,1,0,0); /* Units */
  set_field_type(NULL, TYPE_ENUM, opt_str1, FALSE, TRUE);
  field_items_ptr[DRAG_F] = new_field(1,8,3,1,0,0); /* drag model */

  /* create INTEGER fields */
  set_field_type(NULL, TYPE_INTEGER,0,0,0);
  field_items_ptr[TIME_F] = new_field(1,8,5,1,0,0);	/* max flight time */
  field_items_ptr[IPTS_F] = new_field(1,8,7,1,0,0);	/* integration points */

  /* create field labels */
  set_field_fore(NULL, COLOR_PAIR(BG_PAIR));
  set_field_back(NULL, COLOR_PAIR(BG_PAIR));
  field_items_ptr[UNIT_L_F] = new_field(1,CONFIGURATION_WIDTH,1,10,0,0);
  field_items_ptr[DRAG_L_F] = new_field(1,CONFIGURATION_WIDTH,3,10,0,0);
  field_items_ptr[TIME_L_F] = new_field(1,CONFIGURATION_WIDTH,5,10,0,0);
  field_items_ptr[IPTS_L_F] = new_field(1,CONFIGURATION_WIDTH,7,10,0,0);

  /* done button */
  set_field_fore(NULL, COLOR_PAIR(BG_PAIR) | A_REVERSE | A_DIM);
  set_field_back(NULL, COLOR_PAIR(BG_PAIR) | A_REVERSE | A_DIM);
  field_items_ptr[DONE_F] = new_field(1,8,9,3,0,0);
  done_field = DONE_F;

  /* reset button */
  field_items_ptr[RESET_F] = new_field(1,8,9,13,0,0);

  field_items_ptr[10] = NULL;

  /* field options */
  field_opts_off(field_items_ptr[UNIT_F], O_EDIT);
  field_opts_off(field_items_ptr[DRAG_F], O_EDIT);

  field_opts_off(field_items_ptr[UNIT_L_F], O_ACTIVE);
  field_opts_off(field_items_ptr[DRAG_L_F], O_ACTIVE);
  field_opts_off(field_items_ptr[TIME_L_F], O_ACTIVE);
  field_opts_off(field_items_ptr[IPTS_L_F], O_ACTIVE);

  field_opts_off(field_items_ptr[DONE_F], O_EDIT);
  field_opts_off(field_items_ptr[RESET_F], O_EDIT);

  /* put labels into the items */
  set_field_buffer(field_items_ptr[UNIT_L_F],0,configuration_options[0]);
  set_field_buffer(field_items_ptr[DRAG_L_F],0,configuration_options[1]);
  set_field_buffer(field_items_ptr[TIME_L_F],0,configuration_options[2]);
  set_field_buffer(field_items_ptr[IPTS_L_F],0,configuration_options[3]);

  set_field_buffer(field_items_ptr[DONE_F],0,done_str);
  set_field_buffer(field_items_ptr[RESET_F],0,reset_str);

  /* create new form */
  form_ptr = new_form(field_items_ptr);

  /* setup form handler functions */
  set_form_init(form_ptr, configuration_form_init);
  set_form_term(form_ptr, configuration_form_term);

  /* set place to return when form is done */
  set_form_userptr(form_ptr,create_mainmenu);

  /* display the form */
  display_form();
  configuration_form_handler();

  /* delete form and prepare for main loop */
  delete_form();
  create_mainmenu();
  return;

}

/* display current parameter configuration */
void configuration_form_init(FORM *myform) {

  int i;
  
  char temp[CONFIGURATION_WIDTH];

  if(calcparam.units == ENGLISH)
    set_field_buffer(field_items_ptr[UNIT_F], 0, units_str[0]);
  else
    set_field_buffer(field_items_ptr[UNIT_F], 0, units_str[1]);

  for (i=0; i<NUM_DRAG_MODELS; i++) {
    if (bullet.drag == drag_table[i]) {
      set_field_buffer(field_items_ptr[DRAG_F], 0, model_str[i]);
      break;
    }
  }

  snprintf(temp,sizeof(temp),"%u",calcparam.maxtime);
  set_field_buffer(field_items_ptr[TIME_F], 0, temp);
  snprintf(temp,sizeof(temp),"%u",calcparam.stepsize);
  set_field_buffer(field_items_ptr[IPTS_F], 0, temp);

}

/* update parameter configuration */
void configuration_form_term(FORM *myform) {
  
  char *temp;
  char field[CONFIGURATION_WIDTH];
  int i;

  temp = field_buffer(field_items_ptr[UNIT_F], 0);
  if( strcmp(temp, "ENGLISH ")==0)
    calcparam.units = ENGLISH;
  else
    calcparam.units = METRIC;

  /* fields are padded with spaces, so truncate the string */
  strncpy(field, field_buffer(field_items_ptr[DRAG_F],0), sizeof(field));
                      
  for (i=0; i<sizeof(field); i++)
    if (field[i] == ' ') field[i]='\0';

  for (i=0; i<NUM_DRAG_MODELS; i++)
    if (strcmp(field, model_str[i])==0 ) {
      bullet.drag = drag_table[i];
      break;
    };

  temp = field_buffer(field_items_ptr[TIME_F], 0);
  calcparam.maxtime = (unsigned int) atoi(temp);
  temp = field_buffer(field_items_ptr[IPTS_F], 0);
  calcparam.stepsize = (unsigned int) atoi(temp);

}


void configuration_form_handler(void) {
  
  int c;
  int temp;

  /* display initial drag description */
  drag_model_desc();

  while((c=wgetch(sub_window))) {
    switch (c) {
      case KEY_MOUSE:
        form_driver(form_ptr,KEY_MOUSE);
        break;
      case 9:	/* TAB */
      case KEY_DOWN:
        form_driver(form_ptr,REQ_NEXT_FIELD);
        break;
      case KEY_UP:
        form_driver(form_ptr,REQ_PREV_FIELD);
        break;
      case KEY_LEFT:
        temp = field_index(current_field(form_ptr));
        if ( temp == TIME_F || temp == IPTS_F )
          form_driver(form_ptr,REQ_PREV_CHAR);
        else if ( temp == UNIT_F || temp == DRAG_F )
          form_driver(form_ptr,REQ_PREV_CHOICE);
        if ( temp == DRAG_F ) drag_model_desc();
        break;
      case KEY_RIGHT:
        temp = field_index(current_field(form_ptr));
        if ( temp == TIME_F || temp == IPTS_F )
          form_driver(form_ptr,REQ_NEXT_CHAR);
        else if (temp == UNIT_F || temp == DRAG_F )
          form_driver(form_ptr,REQ_NEXT_CHOICE);
        else if (temp == done_field)
          return;
        else if (temp == RESET_F )
          reset_config();
        if ( temp == DRAG_F ) drag_model_desc();
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
        return;
      case 13:
      case KEY_ENTER:
        temp = field_index(current_field(form_ptr));
        if (temp == done_field)
          return;
        else if (temp == RESET_F ) {
          reset_config();
          break;
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

/* add model description to window */
void drag_model_desc() {
  
  char temp[CONFIGURATION_WIDTH];
  int i;
  int row, col;

  /* fields are padded with spaces, so truncate the string */
  strncpy(temp, field_buffer(field_items_ptr[DRAG_F],0), sizeof(temp));

  for (i=0; i<sizeof(temp); i++)
    if (temp[i] == ' ') temp[i]='\0';

  for (i=0; i<NUM_DRAG_MODELS; i++)
    if (strcmp(temp,model_str[i])==0) break;

  col = (COLS - strlen(model_desc_str[i])) / 2;
  row = LINES - 5;

  mvaddstr(row,col,model_desc_str[i]);
  refresh();

}

/* reset the configuration */
void reset_config(void) {
  
  char temp[CONFIGURATION_WIDTH];

  snprintf(temp,sizeof(temp),"%u", MAXTIME);
  set_field_buffer(field_items_ptr[TIME_F], 0, temp);
  snprintf(temp,sizeof(temp),"%u", POINTSPERSEC);
  set_field_buffer(field_items_ptr[IPTS_F], 0, temp);

}
