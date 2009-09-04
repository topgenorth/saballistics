/***************************************************************************
                          messages.c  -  description
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
#include <config.h>
#endif

#include "messages.h"
#include "main.h"

#include <stdlib.h>

#ifdef ENGLISH_LANG
/* error strings */
char initstring[] = "Couldn't initialize screen";
char need_color_str[] = "This program requires a color terminal";

/* splashscreen strings */
char gpl1[] = "Small Arms Ballistics comes with ABSOLUTELY NO WARRANTY;";
char gpl2[] = "This is free software and you are welcome to distribute";
char gpl3[] = "it under certain conditions: see the file 'COPYING' for";
char gpl4[] = "details.";

char info1[] = "Small Arms Ballistics is " COPYRIGHT;
char info2[] = "It is derived from smallball, originally written by";
char info3[] = "Ole-Hj. Kristensen <ohk@edeber.nta.no>";

/* title window strings */
char name_str[] = "Small Arms Ballistics " VERSION;
char author_str[] = COPYRIGHT;
char usage_str[] = "Use the arrow keys to move, enter to select, `q' to exit.";

/* modify parameters strings */
char modusage_str[] = "Use the arrow keys to move, select DONE or `q' when finished.";

/* configuration strings */
char *units_str[] =
  {
    "ENGLISH",
    "METRIC"
  };

char *model_str[] =
  {
    "British",
    "Ingalls",
    "G1",
    "G2",
    "G5",
    "G6",
    "G7",
    "G8"
  };

char *model_desc_str[] =
  {
    "     British 1909 Model     ",
    "  Based on 1881 Krupp data  ",
    " G1 - Standard bullet model ",
    "        G2 - Unknown        ",
    "  G5 - Moderate boat tails  ",
    "G6 - Flat base, spire points",
    "    G7 - \"VLD\" boat tail    ",
    "        G8 - Unknown        "
  };

char *configuration_options[] =
  {
    "Unit System",
    "Drag Model",
    "Maximum Flight Time [s]",
    "Integration Points Per Second"
  };

/* calculate ballistic coefficient strings */
char *calc_bc_e[] =
  {
    "Initial Range [yds]",
    "Initial Velocity [ft/s]",
    "Final Range [yds]",
    "Final Velocity [ft/s]"
  };

char *calc_bc_m[] =
  {
    "Initial Range [m]",
    "Initial Velocity [m/s]",
    "Final Range [m]",
    "Final Velocity [m/s]"
  };

char *calc_bc_results = "The calculated B.C. is";

/* buttons */
char done_str[] = "  DONE";
char reset_str[] = " RESET";

/* main menu strings */
char *mainmenu_options[] =
  {
    "Configuration     ",
    "Select Bullet     ",
    "Modify Parameters ",
    "Compute Trajectory",
    "Calculate B.C.",
    "Quit Ballistic    "
  };

char *mainmenu_help[] =
  {
    "- Global Configuration Options ",
    "- Select Bullet From Database ",
    "- Modify Calculation Parameters ",
    "- Compute Trajectory ",
    "- Calculate Bullet B.C. ",
    "- Quit Small Arms Ballistics "
  };

/* select bullet strings */
char *bullet_str = "D [in]     Description                Weight [gr]     B.C.";

/* modify bullet paramaters strings */
char *calculation_parameters_e[] =
  {
    "Ballistic Coefficient",
    "Bullet Weight   [grains]",
    "Wind Velocity   [ft/s]",
    "Muzzle Velocity [ft/s]",
    "Bore-Sight Distance [in]",
    "Zero Distance   [yds]",
    "Firing Angle [deg]",
    "Starting Range  [yds]",
    "Ending Range    [yds]",
    "Step Size       [yds]"
  };

char *calculation_parameters_m[] =
  {
    "Ballistic Coefficient",
    "Bullet Weight   [grams]",
    "Wind Velocity   [m/s]",
    "Muzzle Velocity [m/s]",
    "Bore-Sight Distance [m]",
    "Zero Distance   [m]",
    "Firing Angle [deg]",
    "Starting Range  [m]",
    "Ending Range    [m]",
    "Step Size       [m]"
  };

/* calculation display strings */
                     /* 12345678901234567890123456789012345678901234567890 */
char calc_headings[] = "Range  Velocity  Energy   Mom.     Path    Zero    Drop  Drift   Time";
char calc_units_m[]  = " [m]     [m/s]    [kJ]  [kg.m/s]   [m]     [m]     [m]    [m]    [s]";
char calc_units_e[]  = "[yds]   [ft/s] [ft.lbf] [ft.lb/s]  [in]    [in]    [in]    [in]   [s]";
char calc_usage_str[] = "Use the arrow keys to move, `s' to save table, `q' to exit.";

/* save trajectory table strings */
char save_table_str[] = "Output Filename: ";
char opendir_err[] = "Couldn't open current directory";
char save_file_exists[] = "File already exists, overwrite (y/n)?";
char save_table_err[] = "Couldn't Open File, press RETURN";
#endif
