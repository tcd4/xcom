#ifndef __GAME__
#define __GAME__


/**
 * @file game.h
 * 
 * @brief has the basic game struct
 */


#include "types.h"
#include "entity.h"


enum turn_enum
{
  TURN_PLAYER = 0,
  TURN_ENEMY,
  TURN_NONE
};


/* engine functions */

/**
 * @brief initializes the Game_Engine struct
 * 
 * @param sw the screen width
 * @param sh the screen height
 * @param frame_delay the frame delay
 */
void init_game_engine( int sw, int sh, uint32 frame_delay );

/**
 * @brief updates the current game time
 */
void update_game_time();

/**
 * @brief updates the previous game time
 */
void update_previous_time();

/**
 * @brief updates the current game frame
 */
void update_game_frame();

/**
 * @brief gets the current game time
 * 
 * @return the current game time
 */
uint32 get_game_time();

/**
 * @brief gets the previous game time
 * 
 * @return the previous game time
 */
uint32 get_previous_time();

/**
 * @brief gets the current game frame
 * 
 * @return the current game frame
 */
uint32 get_frame();

/**
 * @brief gets the frame delay
 * 
 * @return the frame delay
 */
uint32 get_frame_delay();

/**
 * @brief gets the screen resolution
 * 
 * @return the screen resolution
 */
vec_t* get_resolution();

/**
 * @brief gets the center of the grid
 * 
 * @return the center of the grid
 */
vec_t* get_grid_center();

/**
 * @brief gets the model matrix
 * 
 * @return a pointer to the model matrix
 */
double* get_model_matrix();

/**
 * @brief gets the view matrix
 * 
 * @return a pointer to the view matrix
 */
int* get_view_matrix();

/**
 * @brief gets the projection matrix
 * 
 * @return a pointer to the projection matrix
 */
double* get_projection_matrix();

/* game functions */

/**
 * @brief initializes the game
 * 
 * @param game_config the config file to load the game from
 */
void game_start( char *game_config );

/**
 * @brief checks for a winner and displays the winner
 */
void game_check();

/**
 * @brief ends a turn
 */
void game_end_turn();

/**
 * @brief draws all entities
 */
void game_set_winner( Entity *loser );

/**
 * @brief ends the game
 */
void game_end();


#endif