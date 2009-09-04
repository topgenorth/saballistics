/***************************************************************************
                          results_pad.c  -  description
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
#include <math.h>
#include <stdio.h>
#include <errno.h>

#ifdef HAVE_DIRENT_H
# include <dirent.h>
# define NAMLEN(dirent) strlen((dirent)->d_name)
#else
# define dirent direct
# define NAMLEN(dirent) (dirent)->d_namlen
# if HAVE_SYS_NDIR_H
#  include <sys/ndir.h>
# endif
# if HAVE_SYS_DIR_H
#  include <sys/dir.h>
# endif
# if HAVE_NDIR_H
#  include <ndir.h>
# endif
#endif


#include <string.h>

#include "main.h"
#include "results_pad.h"
#include "messages.h"
#include "curses_func.h"
#include "window_backgrounds.h"
#include "trajectory_funcs.h"
#include "main_menu.h"

/* file local functions */
static void results_pad_handler(int,int,int,int,int);
static void save_results_table(void);
static void write_results(FILE *);

/* trajectory results window */
void results_pad(void) {
  
int j, padrows=0, padcols=0, row;
float i,t,Vx,x,Vy,y,Vz,z,V,E,M,path,conv;
float zero, drop;
int start_y,start_x,end_x,end_y;

  /* setup background */
  calcwindowbg();

  /* determine pad length */
  for(i=printparam.start; i<=printparam.end; i+=printparam.step)
    padrows++;

  padcols = strlen(calc_headings)+1;

  /* create pad window */
  sub_window = newpad(padrows,padcols);

  keypad(sub_window,TRUE); /* enable keypad */
  wattrset(sub_window,COLOR_PAIR(MENU_PAIR)); /* setup colors */
  wbkgdset(sub_window,COLOR_PAIR(MENU_PAIR));
  werase(sub_window);	/* erase and color window */

  /* calculate trajectory */
  calctraj();

  /* conversion factor for elevation angle
     converts line of sight distance to horizontal distance
     so the path values are reported relative to line of sight,
     not horizontal distance */
  conv = cos((firearm.angle*M_PI)/180.0);

  /* write results */
  row = 0;
  for (i = printparam.start, j = 0; i <= printparam.end; i += printparam.step) {

    if(calcparam.units == ENGLISH) i *= 3.0;  /* convert yards to feet */

    /* get the zero data */
    while (j < calcparam.nstep && zero_array[1][j] < i) j++;
    t = linint(zero_array[1][j - 1], time_points[j - 1], zero_array[1][j], time_points[j], i);
    zero = linint(time_points[j - 1], zero_array[3][j - 1], time_points[j], zero_array[3][j], t);

    /* get the drop data */
    j = 0;
    while (j < calcparam.nstep && drop_array[1][j] < i) j++;
    t = linint(drop_array[1][j - 1], time_points[j - 1], drop_array[1][j], time_points[j], i);
    drop = linint(time_points[j - 1], drop_array[3][j - 1], time_points[j], drop_array[3][j], t);

    /* get the path data */
    /* path is reported according to line of sight distance, not
       horizontal distance */
    j = 0;
    while (j < calcparam.nstep && velpos_array[1][j] < i ) j++;
    t = linint(velpos_array[1][j - 1], time_points[j - 1], velpos_array[1][j], time_points[j], i * conv);
    Vx = linint(time_points[j - 1], velpos_array[0][j - 1], time_points[j], velpos_array[0][j], t);
    x = linint(time_points[j - 1], velpos_array[1][j - 1], time_points[j], velpos_array[1][j], t);
    Vy = linint(time_points[j - 1], velpos_array[2][j - 1], time_points[j], velpos_array[2][j], t);
    y = linint(time_points[j - 1], velpos_array[3][j - 1], time_points[j], velpos_array[3][j], t);
    Vz = linint(time_points[j - 1], velpos_array[4][j - 1], time_points[j], velpos_array[4][j], t);
    z = linint(time_points[j - 1], velpos_array[5][j - 1], time_points[j], velpos_array[5][j], t);
    V = sqrt(Vx*Vx + Vy*Vy + Vz*Vz);

    /* take care of elevation angle as the velpos_array coordinates are
       based on the horizontal, not the line of sight */
    path = y - x * tan((firearm.angle*M_PI)/180.0);

    /* unit conversions */
    if(calcparam.units == METRIC) {
      E = .5 * V * V * bullet.weight / 1000.0 / 1000.0;
      M = V * bullet.weight / 1000.0;
    }
    else {
      E = .5 * V * V * bullet.weight / 7000.0 / G_E;
      M = V * bullet.weight / 7000.0;
      x /= 3.0; /* feet to yards */
      path *= 12.0; /* feet to inches */
      z *= 12.0; /* feet to inches */
      drop *= 12.0; /* feet to inches */
      zero *= 12.0; /* feet to inches */
    }

                            /*	12345678901234567890123456789012345678901234567890 */
    mvwprintw(sub_window,row,0,"%5.0f %8.1f  %7.2f %8.2f %7.2f %7.2f %7.2f %6.2f %5.1f",
      x,V,E,M,path,zero,drop,z,t);
    row++;
    if(calcparam.units == ENGLISH)
      i = i / 3.0;  /* back to yards */
    if (j >= calcparam.nstep)
      break;
    }

  /* display the pad */
  start_x = (COLS - strlen(calc_headings)) / 2;
  start_y = 10;
  end_x = start_x + padcols;
  end_y = LINES - 4;
  prefresh(sub_window,0,0,start_y,start_x,end_y,end_x);

  results_pad_handler(padrows,start_y,start_x,end_y,end_x);

  /* free trajectory arrays */
  freetraj();

  /* setup everything for return to main loop */
  delwin(sub_window);
  create_mainmenu();
  return;

}

/* results pad handler */
static void results_pad_handler(int padrows, int start_y, int start_x, int end_y, int end_x) {
  
int c;
int toprow=0, bottomrow = end_y - start_y;

  /* turn on hardware insert delete */
  idlok(sub_window,TRUE);

  while((c=wgetch(sub_window))) {
    switch (c) {
      case 'k':
      case KEY_DOWN:
        if(bottomrow < padrows-1) {
          prefresh(sub_window,++toprow,0,start_y,start_x,end_y,end_x);
          bottomrow++;
        }
        else
          beep();
        break;
      case 'j':
      case KEY_UP:
        if(toprow > 0) {
          prefresh(sub_window,--toprow,0,start_y,start_x,end_y,end_x);
          bottomrow--;
        }
        else
          beep();
        break;
      case 's':
        save_results_table();
        calcwindowbg();
        prefresh(sub_window,toprow,0,start_y,start_x,end_y,end_x);
        break;
      case 27:	/* ESC */
      case 'q':
        idlok(sub_window,FALSE);
        return;
        break;
      default: break;
    }
  }
  return;
}

/* save results */
static void save_results_table(void) {
  
int rows,cols,n=40,length,c;
WINDOW *mywin;
FILE *outfile;
DIR *mydir;
struct dirent *mydirent;
char fname[n+1];

  rows = (LINES - 3) / 2;
  length = strlen(save_table_str) + n + 2;
  cols = (COLS - length) / 2;

  /* create input window */
  mywin = subwin(stdscr,3,length,rows,cols);
  keypad(mywin,TRUE);
  wattrset(mywin,COLOR_PAIR(BG_PAIR));	/* setup colors */
  wbkgdset(mywin,COLOR_PAIR(BG_PAIR));
  werase(mywin);	/* erase and color window */

  mvwaddstr(mywin,1,1,save_table_str);
  length = strlen(save_table_str) + 1;
  box(mywin,0,0);
  wrefresh(mywin);

  echo();
  mvwgetnstr(mywin,1,length,fname,n);
  noecho();

  /* open current directory */
  mydir = opendir(".");
  if (mydir == NULL ) {
    werase(mywin);
    mvwaddstr(mywin,1,1,opendir_err);
    box(mywin,0,0);
    wrefresh(mywin);
    while ( (c = mvwgetch(mywin,1,strlen(save_file_exists)+1)) ) {
      if(c == 'n' || c == 'N') {
        delwin(mywin);
        return;
      }
    }
  }

  /* check existing files */
  while( (mydirent = readdir(mydir)) != NULL ) {
    if( strcmp(fname,mydirent->d_name) == 0 ) {
      werase(mywin);
      mvwaddstr(mywin,1,1,save_file_exists);
      box(mywin,0,0);
      wrefresh(mywin);
      while ( (c = mvwgetch(mywin,1,strlen(save_file_exists)+1)) ) {
        if(c == 'n' || c == 'N') {
          delwin(mywin);
          closedir(mydir);
        return;
        }
        else if (c == 'y' || c == 'Y')
          break;
      }
      break;
    }
  }

  closedir(mydir);

  /* open output file */
  errno = 0;
  outfile = fopen(fname,"w");
  if (errno) {
    werase(mywin);
    mvwaddstr(mywin,1,1,save_table_err);
    box(mywin,0,0);
    wrefresh(mywin);
    while( (c = mvwgetch(mywin,1,strlen(save_table_err+1))) ) {
      if( c == 13 ) {
        delwin(mywin);
        return;
      }
    }
  }

  /* write results */
  write_results(outfile);
  fclose(outfile);

  delwin(mywin);
  return;

}

/* write results file */
static void write_results(FILE *outfile) {
  
int i,j;
float t,V,Vx,Vy,Vz,x,y,z,E,M;
float path, drop, zero, conv;

  /* write table */
  if ( calcparam.units == METRIC ) {
    fprintf(outfile,"# Minimum range is %.1f m\n", printparam.start);
    fprintf(outfile,"# Maximum range is %.1f m\n", printparam.end);
    fprintf(outfile,"# Step size is	%.1f m\n", printparam.step);
    fprintf(outfile,"# Zero range is %.2f m\n", firearm.zero);
    fprintf(outfile,"# Ballistic coefficient is %.4f\n", bullet.bc);
    fprintf(outfile,"# Muzzle velocity is %.2f m/s\n", firearm.v0);
    fprintf(outfile,"# Elevation is %.2f degrees\n", firearm.angle / M_PI * 180.0);
    fprintf(outfile,"# Height of sight is %.3f m\n", firearm.height);
    fprintf(outfile,"# Crosswind is %.2f m/s\n", wind.z);
  }
  else {
    fprintf(outfile,"# Minimum range is %.2f yds\n", printparam.start);
    fprintf(outfile,"# Maximum range is %.2f yds\n", printparam.end);
    fprintf(outfile,"# Step size is	%.2f yds\n", printparam.step);
    fprintf(outfile,"# Zero range is %.2f yds\n", firearm.zero);
    fprintf(outfile,"# Ballistic coefficient is %.4f\n", bullet.bc);
    fprintf(outfile,"# Muzzle velocity is %.2f ft/s\n", firearm.v0);
    fprintf(outfile,"# Elevation is %.2f degrees\n", firearm.angle / M_PI * 180.0);
    /* Height is entered in inches.  geff@spamcop.net */
    fprintf(outfile,"# Height of sight is %.3f in\n", firearm.height);
    fprintf(outfile,"# Crosswind is %.2f ft/s\n", wind.z);
  }

  fprintf(outfile,"#\n#%9s %10s %10s %10s %10s %10s %10s %10s %10s\n",
    "Range","Velocity","Energy","Mom","Path","Zero","Drop","Drift","Time");
  if (calcparam.units == ENGLISH) fprintf(outfile,"#%9s %10s %10s %10s %10s %10s %10s %10s %10s\n",
    "[yds]","[ft/s]","[ft.lbf]","[ft.lbf/s]","[in]","[in]","[in]","[in]","[s]");
  else fprintf(outfile,"#%9s %10s %10s %10s %10s %10s %10s %10s %10s\n",
    "[m]","[m/s]","[kJ]","[kg.m/s]","[m]","[m]","[m]","[m]","[s]");

  /* conversion factor for elevation angle
     converts line of sight distance to horizontal distance */
  conv = cos((firearm.angle*M_PI)/180.0);

  for (i = printparam.start, j = 0; i <= printparam.end; i += printparam.step) {

    if (calcparam.units == ENGLISH) i *= 3; /* convert yards to feet geff@spamcop.net */

    /* get the zero data */
    while (j < calcparam.nstep && zero_array[1][j] < i) j++;
    t = linint(zero_array[1][j - 1], time_points[j - 1], zero_array[1][j], time_points[j], i);
    zero = linint(time_points[j - 1], zero_array[3][j - 1], time_points[j], zero_array[3][j], t);

    /* get the drop data */
    j = 0;
    while (j < calcparam.nstep && drop_array[1][j] < i) j++;
    t = linint(drop_array[1][j - 1], time_points[j - 1], drop_array[1][j], time_points[j], i);
    drop = linint(time_points[j - 1], drop_array[3][j - 1], time_points[j], drop_array[3][j], t);

    /* get the path data */
    /* report path using line of sight distance, not the horizontal distance */
    j = 0;
    while (j < calcparam.nstep && velpos_array[1][j] < i * conv) j++;
    t = linint(velpos_array[1][j - 1], time_points[j - 1], velpos_array[1][j], time_points[j], (float) i * conv);
    Vx = linint(time_points[j - 1], velpos_array[0][j - 1], time_points[j], velpos_array[0][j], t);
    x = linint(time_points[j - 1], velpos_array[1][j - 1], time_points[j], velpos_array[1][j], t);
    Vy = linint(time_points[j - 1], velpos_array[2][j - 1], time_points[j], velpos_array[2][j], t);
    y = linint(time_points[j - 1], velpos_array[3][j - 1], time_points[j], velpos_array[3][j], t);
    Vz = linint(time_points[j - 1], velpos_array[4][j - 1], time_points[j], velpos_array[4][j], t);
    z = linint(time_points[j - 1], velpos_array[5][j - 1], time_points[j], velpos_array[5][j], t);
    V = sqrt(Vx*Vx + Vy*Vy + Vz*Vz);

    /* take care of elevation angle */
    path = y - x * tan((firearm.angle*M_PI)/180.0);

    if(calcparam.units == METRIC) {
      E = .5 * V * V * bullet.weight / 1000.0 / 1000.0;
      M = V * bullet.weight / 1000.0;
    }
    else {
      E = .5 * V * V * bullet.weight / 7000.0 / G_E;
      M = V * bullet.weight / 7000.0;
      x /= 3.0;
      path *= 12.0;
      z *= 12.0;
      drop *= 12.0;
      zero *= 12.0;
    }

    fprintf(outfile,"%10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f\n",x,V,E,M,path,zero,drop,z,t);

    if (calcparam.units == ENGLISH) i /= 3; /* back to yards geff@spamcop.net */

    if (j >= calcparam.nstep)
      break;
  }
}

