/***************************************************************************
                          main.h  -  description
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

/* global defines */
#define POINTSPERSEC 1000     /* time integration points per second */
#define MAXTIME 4             /* maximum calculation time (sec) */
#define ENGLISH_LANG          /* use english messages */

/* don't touch these!! */
/* #define _POSIX_C_SOURCE 2 */
#define ENGLISH 1
#define METRIC 0
#define G_M 9.806     /* Gravity 9.806 m/s^2 */
#define G_E 32.174    /* Gravity 32.174 ft/s^2 */
#define M_PI 3.14159265358979323846264338327
#define MTOE 3.28083989501    /* convert meters to feet */
#define ETOM .3048            /* convert feet to meters */
#define NVAR 6                /* number of variables being integrated */

/* curses handler id's */
#define MENU_HANDLER 0
#define FORM_HANDLER 1

/* The coordinate system is defined as follows:
    X: downrange,
    Y: vertical,
    Z: tangential
 */

/* global structs */
typedef struct {
  float bc;       /* Ballistic coefficient */
  float cd;       /* coefficient of drag */
  float weight;   /* weight in grains */
  double (*drag) (double);  /* Pointer to drag function */
} bullet_t;       /* bullet parameters */

typedef struct {
  float x;  /* applied wind velocities */
  float y;  /* units in m/s or ft/2 */
  float z;
} wind_t;   /* applied wind */

typedef struct {
  float v0;     /* muzzle velocity */
  float angle;  /* elevation angle in radians */
  float height; /* distance between line of sight and bore */
  float zero;   /* zero distance */
} firearm_t;    /* firearm parameters */

typedef struct {
  unsigned int maxtime;  /* maximum bullet flight time */
  unsigned int units;    /* unit system */
  unsigned int nstep;    /* number of time steps */
  unsigned int stepsize;  /* points per second */
  float zero_angle;       /* angle required for zero */
  float wx;               /* wind velocity x */
  float wy;               /* wind velocity y */
  float wz;               /* wind velocity z */
} calcparam_t;    /* parameters used for ballistic calculation */

typedef struct {
  float start;  /* starting range */
  float end;    /* ending range */
  float step;   /* range steps */
} printparam_t; /* parameters for data output format */

/* global variables */
extern bullet_t bullet;
extern wind_t wind;
extern firearm_t firearm;
extern calcparam_t calcparam;
extern printparam_t printparam;
extern void (*func_ptr)(void);
extern unsigned int handler;

/* function prototypes */
extern int main(int, char *[]);
