#include <SDL.h>
#include <GL/glew.h>
#include <gsl/gsl_matrix.h>

#include "game.h"
#include "game_math.h"
#include "parser.h"
#include "camera.h"
#include "logger.h"
#include "grid.h"
#include "player.h"
#include "enemy.h"
#include "unit.h"
#include "weapon.h"


typedef struct engine_s
{
  vec2_t	resolution;
  uint32	frame_delay;
  
  gsl_matrix	*model_matrix;
  gsl_matrix	*view_matrix;
  gsl_matrix	*projection_matrix;
  
  uint32	current_time;
  uint32	previous_time;
  uint32	current_frame;
  
  Dict		*config;
  vec3_t	default_camera_position;
  vec3_t	default_camera_rotation;
  
  Entity	*player;
  Entity	*enemy;
  int		num_units;
  uint8		turn;
  uint8		winner;
  vec2_t	grid_center;
}Game_Engine;


static Game_Engine game;

static void update_mvp();


void init_game_engine( int sw, int sh, uint32 frame_delay )
{
  game.current_time = SDL_GetTicks();
  game.previous_time = game.current_time;
  game.current_frame = 0;
  
  vec2_set( game.resolution, sw, sh );
  game.frame_delay = frame_delay;
  
  game.model_matrix = gsl_matrix_calloc( 4, 4 );
  game.view_matrix = gsl_matrix_calloc( 2, 2 );
  game.projection_matrix = gsl_matrix_calloc( 4, 4 );
  update_mvp();
}


static void update_mvp()
{
  glGetDoublev( GL_MODELVIEW_MATRIX, game.model_matrix->data );
  glGetIntegerv( GL_VIEWPORT, ( int* )( game.view_matrix->data ) );
  glGetDoublev( GL_PROJECTION_MATRIX, game.projection_matrix->data );
}


void update_game_time()
{
  game.current_time = SDL_GetTicks();
}


void update_previous_time()
{
   game.previous_time = game.current_time;
}


void update_game_frame()
{
  game.current_frame++;
}


uint32 get_game_time()
{
  return game.current_time;
}


uint32 get_previous_time()
{
  return game.previous_time;
}


uint32 get_frame()
{
  return game.current_frame;
}


uint32 get_frame_delay()
{
  return game.frame_delay;
}


vec_t* get_resolution()
{
  return game.resolution;
}


double* get_model_matrix()
{
  return game.model_matrix->data;
}


int* get_view_matrix()
{
  return ( int* )( game.view_matrix->data );
}


double* get_projection_matrix()
{
  return game.projection_matrix->data;
}


vec_t* get_grid_center()
{
  return game.grid_center;
}


void game_start( char *game_config )
{
  vec2_t grid_size, tile_size, tile_scale, player_spawn, enemy_spawn;
  
  game.config = parse( game_config );

  str_vec3( find_dict( game.config, "default_camera_position" ), game.default_camera_position );
  str_vec3( find_dict( game.config, "default_camera_rotation" ), game.default_camera_rotation );
  
  str_vec2( find_dict( game.config, "grid_size" ), grid_size );
  str_vec2( find_dict( game.config, "tile_size" ), tile_size );
  str_vec2( find_dict( game.config, "tile_scale" ), tile_scale );
  
  str_bool( find_dict( game.config, "starting_turn" ), &game.turn );
  str_int( find_dict( game.config, "num_units" ), &game.num_units );
  
  str_vec2( find_dict( game.config, "player_spawn" ), player_spawn );
  str_vec2( find_dict( game.config, "enemy_spawn" ), enemy_spawn );
  
  vec2_set( game.grid_center, grid_size[ XA ] * tile_size[ XA ] / 2, grid_size[ YA ] * tile_size[ YA ] / 2 );
  if( !init_grid( grid_size, tile_size, tile_scale, find_dict( game.config, "tile_model" ), find_dict( game.config, "tile_texture" ) ) )
    exit( -1 );
  
  set_camera( game.default_camera_position, game.default_camera_rotation );
  turn_on_camera_controls();
  
  setup_unit_selection();
  game.player = create_player( game.num_units, player_spawn );
  game.enemy = create_enemy( game.num_units, enemy_spawn );
  init_weapons( find_dict( game.config, "weapon_config" ), game.player, game.enemy );
  
  start_player_turn( game.player );
}


void game_check()
{
  if( game.winner == TURN_NONE )
  {
    /* do turn checks */
  }
  else
  {
    if( game.winner == TURN_PLAYER )
    {
      /* display player wins */
    }
    else
    {
      /* display player loses */
    }
  }
}


void game_end_turn()
{
  if( game.turn == TURN_NONE )
    return;
  
  game.turn ^= 1;
  if( game.turn == TURN_PLAYER )
  {
    /* turn off enemy ai */
    start_player_turn( game.player );
  }
  else
  {
    turn_off_player_cmds();
    game_end_turn();
    /* turn on enemy ai */
  }
}


void game_set_winner( Entity *loser )
{
  turn_off_player_cmds();
  
  if( loser == game.player )
    game.winner = TURN_ENEMY;
  else
    game.winner = TURN_PLAYER;
}


void game_end()
{
  free_grid();
}



























/* eof */