/***************************************************************************
                          calc_bc.h  -  description
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

typedef struct {
  float x0;
  float v0;
  float x1;
  float v1;
} calc_bc_param_t;

/* variables */
extern calc_bc_param_t calc_bc_param;

/* functions */
extern void calc_bc(void);


