/***************************************************************************
                          configuration.h  -  description
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

#include <form.h>
 
/* functions */
extern void configuration(void);
extern void configuration_form_init(FORM *);
extern void configuration_form_term(FORM *);
extern void configuration_form_handler(void);
extern void drag_model_desc(void);
extern void reset_config(void);
