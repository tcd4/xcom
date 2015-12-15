#include "grid.h"
#include "logger.h"
#include "game_math.h"

#include <glib.h>


static Grid_Tile	**_grid;
static vec2_t		_grid_size;
static vec2_t		_tile_size;
static vec3_t		_tile_scale;
static vec3_t		_tile_rotation;
static vec4_t		_tile_color;
static Obj		*_tile_model;
static Sprite		*_tile_texture;

static void create_tile( uint32 row, uint32 col );
static void free_tile( Grid_Tile *tile );
static void init_grid_tiles();


uint8 init_grid( vec2_t grid_size, vec2_t tile_size, vec2_t tile_scale, char *tile_model_file, char *tile_texture_file )
{
  uint32 i;
  
  log( INFO, "initializing grid" );
  
  _grid = ( Grid_Tile** )g_new0( Grid_Tile, grid_size[ XA ] );
  if( !_grid )
  {
    log( ERROR, "couldn't allocate memory for the grid" );
    return FALSE;
  }
  
  for( i = 0; i < grid_size[ XA ]; i++ )
  {
    _grid[ i ] = g_new0( Grid_Tile, grid_size[ YA ] );
    if( !_grid[ i ] )
    {
      log( ERROR, "couldn't allocate memory for the grid" );
      return FALSE;
    }
  }
  
  vec2_copy( grid_size, _grid_size );
  vec2_copy( tile_size, _tile_size );
  vec2_copy( tile_scale, _tile_scale );
  _tile_scale[ ZA ] = 1;
  vec3_clear( _tile_rotation );
  _tile_rotation[ XA ] = 90;
  vec4_clear( _tile_color );
  
  _tile_model = obj_load( tile_model_file );
  _tile_texture = LoadSprite( tile_texture_file, -1, -1 );
  
  init_grid_tiles();
  
  log( INFO, "grid initialized" );
  return TRUE;
}


static void init_grid_tiles()
{
  uint32 i, j;
  
  for( i = 0; i < _grid_size[ XA ]; i++ )
  {
    for( j = 0; j < _grid_size[ YA ]; j++ )
    {
      create_tile( i, j );
    }
  }
}


static void create_tile( uint32 row, uint32 col )
{
  Grid_Tile *tmp;
  
  tmp = &_grid[ row ][ col ];
  vec2_set( tmp->grid_position, row, col );
  vec3_set( tmp->world_position, row * _tile_size[ XA ], col * _tile_size[ YA ], 0 );
  tmp->center_position[ XA ] = tmp->world_position[ XA ] + _tile_size[ XA ] / 2;
  tmp->center_position[ YA ] = tmp->world_position[ YA ] + _tile_size[ YA ] / 2;
  tmp->center_position[ ZA ] = 0;
}


void draw_grid()
{
  uint32 i, j;
  Grid_Tile *tmp;
  
  for( i = 0; i < _grid_size[ XA ]; i++ )
  {
    for( j = 0; j < _grid_size[ YA ]; j++ )
    {
      tmp = &_grid[ i ][ j ];
      obj_draw( _tile_model, tmp->world_position, _tile_rotation, _tile_scale, _tile_color, _tile_texture );
    }
  }
}


vec_t* grid_to_world( vec_t *grid_position )
{
  int row, col;
  
  row = grid_position[ YA ];
  col = grid_position[ XA ];
  return _grid[ row ][ col ].center_position;
}


static void free_tile( Grid_Tile *tile )
{
  if( !tile )
    return;
  
  memset( tile, 0, sizeof( Grid_Tile ) );
}


void free_grid()
{
  int i, j;
  
  for( i = 0; i < _grid_size[ XA ]; i++ )
  {
    for( j = 0; j < _grid_size[ YA ]; j++ )
    {
      free_tile( &_grid[ i ][ j ] );
    }
    
    g_free( _grid[ i ] );
  }
  
  g_free( _grid );
  obj_free( _tile_model );
  FreeSprite( _tile_texture );
  vec2_clear( _grid_size );
  vec2_clear( _tile_size );
  vec2_clear( _tile_scale );
}


/* eof */