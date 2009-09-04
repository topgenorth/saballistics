/***************************************************************************
                          messages.h  -  description
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

/* error strings */
extern char initstring[];
extern char need_color_str[];

/* splash screen strings */
extern char gpl1[], gpl2[], gpl3[], gpl4[];
extern char info1[],info2[],info3[];

/* title window strings */
extern char name_str[];
extern char author_str[];
extern char usage_str[];

/* modify parameters strings */
extern char modusage_str[];

/* configuration strings */
#define CONFIGURATION_WIDTH 30
#define NUM_DRAG_MODELS 8
extern char *units_str[];
extern char *model_str[];
extern char *model_desc_str[];
extern char *configuration_options[];

/* BC calculation */
#define CALC_BC_WIDTH 23
extern char *calc_bc_e[];
extern char *calc_bc_m[];
extern char *calc_bc_results;

/* buttons */
extern char done_str[];
extern char reset_str[];

/* maximum number of options in all menus + 1 for null */
#define MENU_OPTIONS 7

/* main menu strings */
#define MAIN_MENU_OPTIONS 6
extern char *mainmenu_options[];
extern char *mainmenu_help[];

/* select bullet strings */
extern char *bullet_str;

/* maximum number of form fields * 2 + 2 */
#define FORM_FIELDS 22
#define PARAMETERS_WIDTH 25

/* calculation paramaters */
extern char *calculation_parameters_e[];
extern char *calculation_parameters_m[];

/* calculation display strings */
extern char calc_headings[];
extern char calc_units_m[];
extern char calc_units_e[];
extern char calc_usage_str[];

/* save trajectory table strings */
extern char save_table_str[];
extern char opendir_err[];
extern char save_file_exists[];
extern char save_table_err[];


