#ifndef __COMMANDS__
#define __COMMANDS__


/**
 * @file cmds.h
 * 
 * @brief a command system for handling input events
 */


#include <SDL.h>

#include "types.h"


/**< a type for functions for commands to call upon activation */
typedef void ( *command_notify )( data param );


/**
 * @brief initializes the command system
 */
uint8 init_command_system();

/**
 * @brief checks if the command system is initialized
 * 
 * @return TRUE if it is, FALSE if else
 */
uint8 is_cmd_sys_init();

/**
 * @brief adds a command to the system
 * 
 * @param name the name of the command
 * @param map the command map it's part of
 * @param type the event type of the command
 * @param id the key that the command checks for
 * @param activate the function to call when the id occurs
 * @param params data to send with activate
 * 
 * @return TRUE on success, FALSE if else
 */
uint8 add_cmd( char *name, char *map, uint32 type, int id, command_notify activate, data params );

/**
 * @brief adds a command map to the system
 * 
 * @param name the name of the command map
 * 
 * @return TRUE on succes, FALSE if else
 */
uint8 add_cmd_map( char *name );

/**
 * @brief turns on a command
 * 
 * @param name the name of the command to turn on
 */
void turn_on_cmd( char *name );

/**
 * @brief turns off a command
 * 
 * @param name the name of the command to turn off
 */
void turn_off_cmd( char *name );

/**
 * @brief turns on a command map
 * 
 * @param name the name of the command map to turn on
 */
void turn_on_cmd_map( char *name );

/**
 * @brief turns off a command map
 * 
 * @param name the name of the command map to turn off
 */
void turn_off_cmd_map( char *name );

/**
 * @brief checks if a command should be activated
 * 
 * @param event the SDL event to check with
 */
void check_cmds( SDL_Event *event );

/**
 * @brief closes the command system
 */
void exit_command_system();


#endif