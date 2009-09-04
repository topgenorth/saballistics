bin_PROGRAMS = saballistics

saballistics_SOURCES = drag_models.c calc_bc.c trajectory_funcs.c results_pad.c modify_parameters.c function_tables.c main_menu.c bullet_select.c configuration.c form_handlers.c menu_handlers.c messages.c window_backgrounds.c curses_func.c main.c 
saballistics_CFLAGS = -DDATADIR=\"${datadir}\"
saballistics_LDADD   = -lform -lmenu -lncurses -lm

data_DATA = bullet.dat
dist_data_DATA = bullet.dat

noinst_HEADERS = main.h curses_func.h window_backgrounds.h messages.h menu_handlers.h form_handlers.h configuration.h bullet_select.h main_menu.h function_tables.h modify_parameters.h results_pad.h trajectory_funcs.h calc_bc.h drag_models.h

INCLUDES= $(all_includes)

EXTRA_DIST = main.c main.h curses_func.h curses_func.c window_backgrounds.h window_backgrounds.c messages.h messages.c menu_handlers.c menu_handlers.h form_handlers.h form_handlers.c configuration.h configuration.c bullet_select.h bullet_select.c main_menu.h main_menu.c function_tables.h function_tables.c modify_parameters.h modify_parameters.c results_pad.h results_pad.c trajectory_funcs.h trajectory_funcs.c calc_bc.h calc_bc.c drag_models.h drag_models.c 

                                                                                
