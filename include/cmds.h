#ifndef __COMMANDS__
#define __COMMANDS__


#include <SDL.h>

#include "types.h"


typedef void ( *command_notify )( data param );


uint8 init_command_system();
uint8 is_cmd_sys_init();
uint8 add_cmd( char *name, char *map, uint32 type, int id, command_notify activate, data params );
uint8 add_cmd_map( char *name );
void turn_on_cmd( char *name );
void turn_off_cmd( char *name );
void turn_on_cmd_map( char *name );
void turn_off_cmd_map( char *name );
void check_cmds( SDL_Event *event );
void exit_command_system();


#endif