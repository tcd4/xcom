#ifndef __GRID__
#define __GRID__


/**
 * @file grid.h
 * 
 * @brief files for handling actions pertaining to the world grid
 */


#include "types.h"
#include "entity.h"


typedef struct grid_tile_s
{
  vec2_t grid_position; /**< the position in the grid */
  vec3_t world_position; /**< the position of the tile in the world */
  vec3_t center_position; /**< the position of the center of the tile in the world */
}Grid_Tile;


/**
 * @brief initializes the game grid
 * 
 * @param grid_size the size of the grid
 * @param tile_size the size of a tile
 * @param tile_scale the scale to draw the tiles
 * @param tile_model_file the tile model
 * @param tile_texture_file the tile texture
 * 
 * @return TRUE on success, FALSE if else
 */
uint8 init_grid( vec2_t grid_size, vec2_t tile_size, vec2_t tile_scale, char *tile_model_file, char *tile_texture_file  );

/**
 * @brief draws all the tiles in the grid
 */
void draw_grid();

/**
 * @brief free all the tiles in the grid
 */
void free_grid();

/**
 * @brief converts a grid position to a world position
 * 
 * @param grid_position the position in the grid to convert
 * 
 * @return the center of the choosen tile in the world
 */
vec_t* grid_to_world( vec_t *grid_position );


#endif