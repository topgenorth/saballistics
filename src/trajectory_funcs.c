/***************************************************************************
                          trajectory_funcs.c  -  description
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

#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include "trajectory_funcs.h"
#include "main.h"

/* file local functions */
static void rungekutta(float *, float *, int, float, float, float *, void (*) (float, float *, float *));
static void rkdumb(float *, float, float **, void (*) (float, float *, float *));
static void flightmodel(float, float *, float *);
static void zeroin(float *, float *, float *, float **);

float **drop_array = NULL;
float **zero_array = NULL;
float **velpos_array = NULL;
float *time_points = NULL;

/* General fourth order Runge Kutta */
static void rungekutta(float *y, float *dydx, int n, float x, float h, float *yout,
  void (*d) (float x, float *y, float* dxdy))
  
  /* Initial values of y's */
  /* Initial values of derivatives */
  /* Number of variables to integrate */
  /* Current x value */
  /* Step size */
  /* New values of y's */
  /* Pointer to function which computes
  * derivatives */
{
  
  static int      oldn = 0;
  int             i;
  static float    xmid, halfstep, h6, *dy_mid, *dy_trial, *y_trial;

  /* Allocate new working area only if number of variables change */
  if (n != oldn) {
    if (n != 0) {
      if (y_trial) free(y_trial);
      if (dy_trial) free(dy_trial);
      if (dy_mid) free(dy_mid);
      oldn = n;
    }

    dy_mid = (float *) calloc(n, sizeof(float));
    dy_trial = (float *) calloc(n, sizeof(float));
    y_trial = (float *) calloc(n, sizeof(float));
  }
  
  /* Start crunching */

  halfstep = h * 0.5;
  h6 = h / 6.0;
  xmid = x + halfstep;

  for (i = 0; i < n; i++)
    y_trial[i] = y[i] + halfstep * dydx[i];

  (*d) (xmid, y_trial, dy_trial);
  
  for (i = 0; i < n; i++)
    y_trial[i] = y[i] + halfstep * dy_trial[i];

  (*d) (xmid, y_trial, dy_mid);
  for (i = 0; i < n; i++) {
    y_trial[i] = y[i] + h * dy_mid[i];
    dy_mid[i] += dy_trial[i];
  }

  (*d) (x + h, y_trial, dy_trial);
  for (i = 0; i < n; i++)
    yout[i] = y[i] + h6 * (dydx[i] + dy_trial[i] + 2.0 * dy_mid[i]);
}

/* Simple-minded driver for the rungekutta integration routine */
static void rkdumb(float *vstart, float x1, float **array,
  void (*d) (float x, float *y, float* dxdy)) {
  /* Initial values , Integrate from x1 ,
   * User-supplied function to compute derivatives */
   
int   i, k;
float x, h;
float *vcopy, *vout, *dvcopy;

  /* Allocate work space */
  vcopy = (float *) calloc(NVAR, sizeof(float));
  vout = (float *) calloc(NVAR, sizeof(float));
  dvcopy = (float *) calloc(NVAR, sizeof(float));

  /* Copy initial values */
  for (i = 0; i < NVAR; i++)
    array[i][0] = vcopy[i] = vstart[i];

  time_points[0] = x1;
  x = x1;
  h = (calcparam.maxtime - x1) / calcparam.nstep;	/* Step size */

  for (k = 0; k < calcparam.nstep; k++) {
    /* Update y's */
    (*d) (x, vcopy, dvcopy);
    rungekutta(vcopy, dvcopy, NVAR, x, h, vout, d);

    assert((x + h) != x);	/* Abort if we don't move */

    /* Update x */
    x += h;
    time_points[k + 1] = x;

    /* Copy result */
    for (i = 0; i < NVAR; i++)
      array[i][k + 1] = vcopy[i] = vout[i];
  }

  /* Free work space */
  free(dvcopy);
  free(vout);
  free(vcopy);
}

/*
  This is our flight model, expressed as a system of differential
  equations. It is rather simple, but should be sufficient for small
  arms fire. It is assumed that the projectile instantaneously adjusts
  itself to the wind, so that it is always pointing directly into the
  relative wind. This makes it simple to compute the effect of the
  crosswind, as the acceleration caused by the wind will just be
  a component of the drag. The drag is computed from the speed of
  the projectile relative to the wind, of course.

  g is assumed to be constant.
  Coriolis forces are not taken into account.

  If the last two assumptions do not hold for you,
  you are into artillery, not small arms fire.
  */
static void flightmodel(float x, float *y, float *dydx)
{
  /* Compute speed relative to wind */
  float u = sqrt( (y[0] + wind.x) * (y[0] + wind.x) +
    (y[2] + wind.y) * (y[2] + wind.y) +
    (y[4] + wind.z) * (y[4] + wind.z) );

/* Drag components (yes, it really is this simple) */
  float alfa = (y[0] - calcparam.wx) / u;
  float beta = (y[2] - calcparam.wy) / u;
  float gamma = (y[4] - calcparam.wz) / u;

/* Compute drag */
  float r = bullet.drag(u) / bullet.bc;

/* Compute acceleration and velocity */
  dydx[0] = -r * alfa;  /* Vx */
  dydx[1] = y[0];       /* Sx */
  if (calcparam.units == ENGLISH)
    dydx[2] = -r * beta - G_E;/* Vy */
  else
    dydx[2] = -r * beta - G_M;
    
  dydx[3] = y[2];   /* Sy */
  dydx[4] = -r * gamma; /* Vz */
  dydx[5] = y[4];   /* Sz */
}


/* Linear interpolation is close enough */
float linint(float x0, float y0, float x1, float y1, float x)
{
    return (x - x0) * (y1 - y0) / (x1 - x0) + y0;
}

/* Crude calculation of elevation, given a desired zero range */
static void zeroin(float *tval, float *vx, float *vy, float **array)
{
int   i;
float t;
float dx, dy, zero;

  if (calcparam.units == ENGLISH)
    zero = firearm.zero * 3.0;	/* yds to feet */
  else
    zero = firearm.zero;

  for (i = 1; i < calcparam.nstep && array[1][i] < zero; i++);
  t = linint(array[1][i - 1], tval[i - 1], array[1][i], tval[i], zero);
  dx = linint(tval[i - 1], array[1][i - 1], tval[i], array[1][i], t);
  dy = linint(tval[i - 1], array[3][i - 1], tval[i], array[3][i], t);
  calcparam.zero_angle += atan(-dy / dx);
  *vy = sin(calcparam.zero_angle) * firearm.v0;
  *vx = cos(calcparam.zero_angle) * firearm.v0;
}

/* Initialize and calculate trajectory tables.
 * Accomplished with a 4th order Runge-Kutta integration routine
 *
 * All of the drag functions work with English (ft,sec) units
 * based on a cartesian coordinate system oriented with
 * the earth.
 *
 * The drop_array is calculated based on the bullet being fired in the
 * horizontal only.
 *
 * The zero_array is calculated with an initial offset in bullet height.
 * The trajectory calculation is then run three times, using a linear
 * guess at the required elevation angle to achieve zero for calculations
 * two and three.
 *
 * The velpos_array is finally calculated using the elevation angle
 * computed for the zero and applying the user specified wind velocity
 * and firearm elevation angle.
 */
void calctraj(void) {
  
int i, t0;
float *vstart;

  t0 = 0.0;   /* Set tart time to 0.0 sec */

  calcparam.nstep = (calcparam.maxtime - t0) * calcparam.stepsize;	/* number of time steps */

  /* allocate and set to zero the starting velocity/position vector */
  vstart = (float *) calloc(NVAR, sizeof(float));

  /* Note: The arrays time_points and velpos_array must have indices up to nstep */
  time_points = (float *) calloc(calcparam.nstep + 1, sizeof(float));	/* Vector */
  drop_array = (float **) calloc(NVAR, sizeof(float *));	/* Matrix */
  zero_array = (float **) calloc(NVAR, sizeof(float *));	/* Matrix */
  velpos_array = (float **) calloc(NVAR, sizeof(float *));	/* Matrix */

  for (i = 0; i < NVAR; i++) {
    drop_array[i] = (float *) calloc(calcparam.nstep + 1, sizeof(float));
    zero_array[i] = (float *) calloc(calcparam.nstep + 1, sizeof(float));
    velpos_array[i] = (float *) calloc(calcparam.nstep + 1, sizeof(float));
  }

  /* vstart vector:   [0] = Vx (velocity downrange)
                      [1] = Xx (position downrange)
                      [2] = Vy (vertical)
                      [3] = Xy
                      [4] = Vz (transverse)
                      [5] = Xz
  */

  /* calculate drop array */
  vstart[0] = firearm.v0;
  vstart[1] = 0.0;
  vstart[2] = 0.0;
  vstart[3] = 0.0;
  vstart[4] = 0.0;
  vstart[5] = 0.0;

  /* set wind to zero */
  calcparam.wx = calcparam.wy = calcparam.wz = 0.0;
  rkdumb(vstart, t0, drop_array, flightmodel);

  /* calculate zero array */
  vstart[0] = firearm.v0;
  vstart[1] = 0.0;
  vstart[2] = 0.0;
  if (calcparam.units == ENGLISH ) vstart[3] = -firearm.height / 12.0; /* inches to feet */
  else vstart[3] = -firearm.height;
  vstart[4] = 0.0;
  vstart[5] = 0.0;

  rkdumb(vstart, t0, zero_array, flightmodel);

  /* Zero it twice, as the approximation is crude, but converges */
  calcparam.zero_angle = 0.0;
  zeroin(time_points, &vstart[0], &vstart[2], zero_array);
  rkdumb(vstart, t0, zero_array, flightmodel);

  zeroin(time_points, &vstart[0], &vstart[2], zero_array);
  rkdumb(vstart, t0, zero_array, flightmodel);

  /* calculate actual bullet flight */
  calcparam.wx = wind.x;
  calcparam.wy = wind.y;
  calcparam.wz = wind.z;

  vstart[0] = firearm.v0 * cos( ((firearm.angle*M_PI)/180) + calcparam.zero_angle);
  vstart[1] = 0.0;
  vstart[2] = firearm.v0 * sin( ((firearm.angle*M_PI)/180) + calcparam.zero_angle);
  if (calcparam.units == ENGLISH) vstart[3] = -firearm.height / 12.0; /* inches to feet */
  else vstart[3] = -firearm.height;
  vstart[4] = 0.0;
  vstart[5] = 0.0;

  rkdumb(vstart, t0, velpos_array, flightmodel);

  free(vstart);
  
}

/* function to free trajectory arrays */
void freetraj(void) {
  
int i;

  for (i = 0; i < NVAR; i++) {
    free(drop_array[i]);
    free(zero_array[i]);
    free(velpos_array[i]);
  }
  free(drop_array);
  free(zero_array);
  free(velpos_array);
  free(time_points);
}
