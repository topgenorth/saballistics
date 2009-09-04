/***************************************************************************
                          trajectory_funcs.h  -  description
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

/* functions */

extern void calctraj(void);
extern void freetraj(void);
extern float linint(float, float, float, float, float);

/* variables */
extern float **drop_array;
extern float **zero_array;
extern float **velpos_array;
extern float *time_points;
