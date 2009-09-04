/***************************************************************************
                          drag_models.h  -  description
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

/*  General form of drag function*/
#define DRAGFUN(vel,a,m) (a * pow(vel,m))

/* Standard British 1909 drag function */
extern double british(double v);

/* Mayevski (Ingall's) drag function */
extern double ingalls(double v);

/* G functions */
extern double g1(double v);
extern double g2(double v);
extern double g5(double v);
extern double g6(double v);
extern double g7(double v);
extern double g8(double v);
