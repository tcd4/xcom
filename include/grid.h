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


uint8 init_grid( vec2_t grid_size, vec2_t tile_size, vec2_t tile_scale, char *tile_model_file, char *tile_texture_file  );
void draw_grid();
void free_grid();
vec_t* grid_to_world( vec_t *grid_position );


#endif