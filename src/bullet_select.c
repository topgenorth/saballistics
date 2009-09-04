/***************************************************************************
                          bullet_select.c  -  description
                             -------------------
    begin                : Wed Mar 31 2004
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
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "main.h"
#include "bullet_select.h"
#include "curses_func.h"
#include "menu_handlers.h"
#include "window_backgrounds.h"
#include "messages.h"
#include "main_menu.h"


/* lines to read at a time */
#define CHUNK_SIZE 10
#define DESC_LENGTH 30
#define LINE_LENGTH 90

static void del_newline(char *);
static void bullet_handler(int);
static void free_filebuf(void);

/* file global variable with lines of bullet data file */
typedef struct {
  char **lines;    /* array of file data */
  int len;            /* number of lines allocated */
  } filebuf_t;

static filebuf_t filebuf = {NULL, 0};
  
/* bullet database menu */
void bullet_database(void) {
  
  int count, i;
  char *err;
  FILE *infile;
  char temp[LINE_LENGTH+1];

  /* setup background */
  titlewindowbg();

  /* open data file */
  infile = fopen( DATADIR "/bullet.dat","r");

  /* error check */
  if (infile == NULL) {
    fprintf(stderr,"bullet_database(): Couldn't open " DATADIR "/bullet.dat file.\n");
    finish(0);
  }
  
  /* allocate space */
  assert(filebuf.lines == NULL);
  assert(filebuf.len == 0);
  
  filebuf.lines = malloc(CHUNK_SIZE * sizeof(char *));

  for (i = 0; i < CHUNK_SIZE; i++)
    filebuf.lines[i] = malloc( (LINE_LENGTH+1) * sizeof(char));


  filebuf.len = CHUNK_SIZE;
  
  count = 0;

  /* skip 2 lines */
  fgets(temp,LINE_LENGTH,infile);
  fgets(temp,LINE_LENGTH,infile);

  /* read in datafile */
  /* last entry in filebuf.lines will be zero length string */
  while (1) {
    if (count == filebuf.len) {
      filebuf.len += CHUNK_SIZE;
      filebuf.lines = realloc(filebuf.lines, filebuf.len * sizeof(char *));
      for (i = count; i < filebuf.len; i++)
        filebuf.lines[i] = malloc( (LINE_LENGTH+1) * sizeof(char));
    }

    err = fgets(filebuf.lines[count],LINE_LENGTH,infile);
    del_newline(filebuf.lines[count]);

    if (err == NULL || *err == EOF)
      break;

    count++;

  }

  /* close datafile */
  fclose(infile);

  /* create menu items */
  assert(my_menu_items == NULL);
  
  my_menu_items = malloc((count+1) * sizeof(ITEM *));

  if (my_menu_items == NULL) {
    fprintf(stderr,"create_main_menu(): Out of memory\n");
    finish(0);
  }

  for (i = 0; i < count; i++)
    my_menu_items[i] = new_item(filebuf.lines[i],NULL);

  my_menu_items[i] = NULL;

  /* create menu */
  menu_ptr = new_menu(my_menu_items);
  menu_opts_off(menu_ptr, O_SHOWDESC);

  bullet_handler(count);

  return;

}

/* handle bullet selection */
static void bullet_handler(int count) {
  
  int c;

  display_menu();

  keypad(sub_window,TRUE);
  wtimeout(sub_window,-1);

  mvaddstr(3,(COLS-strlen(bullet_str))/2,bullet_str);
  refresh();

  while((c=wgetch(sub_window))) {
    switch (c) {
      case KEY_MOUSE:
        menu_driver(menu_ptr,KEY_MOUSE);
        break;
      case 9:	/* TAB */
      case 'k':
      case KEY_DOWN:
        menu_driver(menu_ptr,REQ_DOWN_ITEM);
        break;
      case KEY_NPAGE:
        menu_driver(menu_ptr,REQ_SCR_DPAGE);
        break;
      case KEY_PPAGE:
        menu_driver(menu_ptr,REQ_SCR_UPAGE);
        break;
      case 'j':
      case KEY_UP:
        menu_driver(menu_ptr,REQ_UP_ITEM);
        break;
      case 27:	/* ESC */
      case 'q':
        free_filebuf();
        delete_menu();
        create_mainmenu();
        return;
      case 13:
      case KEY_ENTER:
        c = item_index(current_item(menu_ptr));
        sscanf(filebuf.lines[c],"%*40c %f %f",&bullet.weight,&bullet.bc);
        if (calcparam.units == METRIC)
          bullet.weight = bullet.weight * 0.06479891;

        free_filebuf();  
        delete_menu();
        create_mainmenu();
        return;
      default: break;
    }
  }
}

/* delete newline from array */
static void del_newline(char *line) {

  while( *line != '\0') {
    
    if ( *line == '\n') {
      *line = '\0';
      return;
    }
    
    line++;
  }

  return;
}

/* empty filebuf */
static void free_filebuf(void) {

  int i;
  
  for(i=0; i < filebuf.len; i++)
    free(filebuf.lines[i]);
    
  free(filebuf.lines);

  filebuf.len = 0;
  filebuf.lines = NULL;
  
}

