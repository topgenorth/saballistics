/***************************************************************************
                          drag_models.c  -  description
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

 /* ballistic drag functions

   These functions return the standard projectile retardation
   (decelaration) for a given projectile velocity.
   The retardation values are experimentally determined.

   The experimental data is in the English unit system (ft,sec)
   so a conversion must be applied for metric calculations.

   The G series of drag functions were computed based on drag
   function test data available somewhere on the Internet.
   I'm not sure where it came from now, but www.snipercountry.com
   may be a good place to start.  Josh
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <math.h>

#include "drag_models.h"
#include "main.h"

/*
 *  original Ingalls function
 *  in english units (ft,sec)
 *  computed from 1881 Krupp tests
 */
double ingalls(double v) {

double convert = 1.0;
double unconvert = 1.0;

  if (calcparam.units == METRIC) {
    convert = MTOE;
    unconvert = 1 / MTOE;
  }

  if ( v * convert > 2600 )
    return unconvert * DRAGFUN(v * convert, 4.0648825E-03, 1.55);
  if ( v * convert > 1800 )
    return unconvert * DRAGFUN(v * convert, 1.2479524E-03, 1.7);
  if ( v * convert > 1370 )
    return unconvert * DRAGFUN(v * convert, 1.3160125E-04, 2.0);
  if ( v * convert > 1230 )
    return unconvert * DRAGFUN(v * convert, 9.5697809E-08, 3.0);
  if ( v * convert > 970 )
    return unconvert * DRAGFUN(v * convert, 6.3368148E-14, 5.0);
  if ( v * convert > 790 )
    return unconvert * DRAGFUN(v * convert, 5.9353046E-08, 3.0);
  return unconvert * DRAGFUN(v * convert, 4.6761777E-05, 2.0);

}

/*
 *  original British 1909 function
 *  in english units (ft,sec)
 */
double british(double v) {
  
double convert = 1.0;
double unconvert = 1.0;

  if (calcparam.units == METRIC) {
    convert = MTOE;
    unconvert = 1 / MTOE;
  }

  if ( v * convert > 2600 )
    return unconvert * DRAGFUN(v*convert, 15366E-07, 1.67);
  if ( v * convert > 2000 )
    return unconvert * DRAGFUN(v*convert, 58495E-07, 1.5);
  if ( v * convert > 1460 )
    return unconvert * DRAGFUN(v*convert, 59814E-08, 1.8);
  if ( v * convert > 1190 )
    return unconvert * DRAGFUN(v*convert, 95408E-12, 3.0);
  if ( v * convert > 1040 )
    return unconvert * DRAGFUN(v*convert, 23385E-22, 6.45);
  if ( v * convert > 840 )
    return unconvert * DRAGFUN(v*convert, 59939E-12, 3.0);
  return unconvert * DRAGFUN(v*convert, 74422E-08, 1.6);

}

/*
 *  G1 drag function, computed from G1 test data by Joshua Weage
 *  English units (ft,sec)
 */
double g1(double v) {
  
double convert = 1.0;
double unconvert = 1.0;

  if (calcparam.units == METRIC) {
    convert = MTOE;
    unconvert = 1 / MTOE;
  }

  if ( v * convert > 3030 )
    return unconvert * DRAGFUN(v*convert, 0.000296635108154501 , 1.87252063407832);
  if ( v * convert > 1680 )
    return unconvert * DRAGFUN(v*convert, 0.00265008089051, 1.59991739552902);
  if ( v * convert > 1370 )
    return unconvert * DRAGFUN(v*convert, 7.4943163444737e-05, 2.07924007208305);
  if ( v * convert > 1188 )
    return unconvert * DRAGFUN(v*convert, 3.70259572966957e-08, 3.13397627815142);
  if ( v * convert > 1102 )
    return unconvert * DRAGFUN(v*convert, 2.03819724134521e-12, 4.51864414221529);
  if ( v * convert > 1002 )
    return unconvert * DRAGFUN(v*convert, 1.26894810865425e-14, 5.24444510076256);
  if ( v * convert > 897 )
    return unconvert * DRAGFUN(v*convert, 2.50774278169392e-12, 4.47699813972495);
  if ( v * convert > 815 )
    return unconvert * DRAGFUN(v*convert, 3.58554042439043e-09, 3.40803262472929);
  if ( v * convert > 670 )
    return unconvert * DRAGFUN(v*convert, 1.64345495555904e-06, 2.4945292265651);
  if ( v * convert > 171 )
    return unconvert * DRAGFUN(v*convert, 0.000104179611848886, 1.85590504676905);
  return unconvert * DRAGFUN(v*convert, 7.79067551784038e-05, 1.91007352175472);

}

/*
 *  G2 drag function, computed from G2 test data by Joshua Weage
 *  English units (ft,sec)
 */
double g2(double v) {
  
double convert = 1.0;
double unconvert = 1.0;

  if (calcparam.units == METRIC) {
    convert = MTOE;
    unconvert = 1 / MTOE;
  }

  if ( v * convert > 1674 )
    return unconvert * DRAGFUN(v*convert, 0.0079470052136733, 1.36999902851493);
  if ( v * convert > 1172 )
    return unconvert * DRAGFUN(v*convert, 0.00100419763721974, 1.65392237010294);
  if ( v * convert > 1060 )
    return unconvert * DRAGFUN(v*convert, 7.15571228255369e-23, 7.91913562392361);
  if ( v * convert > 949 )
    return unconvert * DRAGFUN(v*convert, 1.39589807205091e-10, 3.81439537623717);
  if ( v * convert > 670 )
    return unconvert * DRAGFUN(v*convert, 0.000234364342818625, 1.71869536324748);
  if ( v * convert > 335 )
    return unconvert * DRAGFUN(v*convert, 0.000177962438921838, 1.76877550388679);
  return unconvert * DRAGFUN(v*convert, 5.18033561289704e-05, 1.98160270524632);

}

/*
 *  G5 drag function, computed from G5 test data by Joshua Weage
 *  English units (ft,sec)
 */
double g5(double v) {
  
double convert = 1.0;
double unconvert = 1.0;

  if (calcparam.units == METRIC) {
    convert = MTOE;
    unconvert = 1 / MTOE;
  }

  if ( v * convert > 1730 )
    return unconvert * DRAGFUN(v*convert, 0.00724854775171929, 1.41538574492812);
  if ( v * convert > 1228 )
    return unconvert * DRAGFUN(v*convert, 3.50563361516117e-05, 2.13077307854948);
  if ( v * convert > 1116 )
    return unconvert * DRAGFUN(v*convert, 1.84029481181151e-13, 4.81927320350395);
  if ( v * convert > 1004 )
    return unconvert * DRAGFUN(v*convert, 1.34713064017409e-22, 7.8100555281422);
  if ( v * convert > 837 )
    return unconvert * DRAGFUN(v*convert, 1.03965974081168e-07, 2.84204791809926);
  if ( v * convert > 335 )
    return unconvert * DRAGFUN(v*convert, 0.000109301593869823, 1.81096361579504);
  return unconvert * DRAGFUN(v*convert, 3.51963178524273e-05, 2.00477856801111);

}

/*
 *  G6 drag function, computed from G6 test data by Joshua Weage
 *  English units (ft,sec)
 */
double g6(double v) {
  
double convert = 1.0;
double unconvert = 1.0;

  if (calcparam.units == METRIC) {
    convert = MTOE;
    unconvert = 1 / MTOE;
  }

  if ( v * convert > 3236 )
    return unconvert * DRAGFUN(v*convert, 0.0455384883480781, 1.15997674041274);
  if ( v * convert > 2065 )
    return unconvert * DRAGFUN(v*convert, 0.0716726184965377, 1.10704436538885);
  if ( v * convert > 1311 )
    return unconvert * DRAGFUN(v*convert, 0.00166676386084348, 1.60085100195952);
  if ( v * convert > 1144 )
    return unconvert * DRAGFUN(v*convert, 1.01482730119215e-07, 2.9569674731838);
  if ( v * convert > 1004 )
    return unconvert * DRAGFUN(v*convert, 4.31542773103552e-18, 6.34106317069757);
  if ( v * convert > 670 )
    return unconvert * DRAGFUN(v*convert, 2.04835650496866e-05, 2.11688446325998);
  return unconvert * DRAGFUN(v*convert, 7.50912466084823e-05, 1.92031057847052);

}

/*
 *  G7 drag function, computed from G7 test data by Joshua Weage
 *  English units (ft,sec)
 */
double g7(double v) {
  
double convert = 1.0;
double unconvert = 1.0;

  if (calcparam.units == METRIC) {
    convert = MTOE;
    unconvert = 1 / MTOE;
  }

  if ( v * convert > 4200 )
    return unconvert * DRAGFUN(v*convert, 1.29081656775919e-09, 3.24121295355962);
  if ( v * convert > 3000 )
    return unconvert * DRAGFUN(v*convert, 0.0171422231434847, 1.27907168025204);
  if ( v * convert > 1470 )
    return unconvert * DRAGFUN(v*convert, 0.00233355948302505, 1.52693913274526);
  if ( v * convert > 1260 )
    return unconvert * DRAGFUN(v*convert, 0.000797592111627665, 1.67688974440324);
  if ( v * convert > 1110 )
    return unconvert * DRAGFUN(v*convert, 5.71086414289273e-12, 4.3212826264889);
  if ( v * convert > 960 )
    return unconvert * DRAGFUN(v*convert, 3.02865108244904e-17, 5.99074203776707);
  if ( v * convert > 670 )
    return unconvert * DRAGFUN(v*convert, 7.52285155782535e-06, 2.1738019851075);
  if ( v * convert > 540 )
    return unconvert * DRAGFUN(v*convert, 1.31766281225189e-05, 2.08774690257991);
  return unconvert * DRAGFUN(v*convert, 1.34504843776525e-05, 2.08702306738884);

}

/*
 *  G8 drag function, computed from G8 test data by Joshua Weage
 *  English units (ft,sec)
 */
double g8(double v) {
  
double convert = 1.0;
double unconvert = 1.0;

  if (calcparam.units == METRIC) {
    convert = MTOE;
    unconvert = 1 / MTOE;
  }

  if ( v * convert > 3571 )
    return unconvert * DRAGFUN(v*convert, 0.0112263766252305, 1.33207346655961);
  if ( v * convert > 1841 )
    return unconvert * DRAGFUN(v*convert, 0.0167252613732636, 1.28662041261785);
  if ( v * convert > 1120 )
    return unconvert * DRAGFUN(v*convert, 0.00220172456619625, 1.55636358091189);
  if ( v * convert > 1088 )
    return unconvert * DRAGFUN(v*convert, 2.0538037167098e-16, 5.80410776994789);
  if ( v * convert > 976 )
    return unconvert * DRAGFUN(v*convert, 5.92182174254121e-12, 4.29275576134191);
  return unconvert * DRAGFUN(v*convert, 4.3917343795117e-05, 1.99978116283334);

}
