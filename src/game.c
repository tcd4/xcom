#include <SDL.h>
#include <GL/glew.h>

#include "game.h"
#include "game_math.h"
#include "parser.h"
#include "camera.h"


typedef struct engine_s
{
  vec2_t	resolution;
  uint32	frame_delay;
  
  GLdouble	model_matrix[ 16 ];
  GLint		view_matrix[ 4 ];
  GLdouble	projection_matrix[ 16 ];
  
  uint32	current_time;
  uint32	previous_time;
  uint32	current_frame;
  
  Dict		*config;
  vec3_t	default_camera_position;
  vec3_t	default_camera_rotation;
}Game_Engine;


static Game_Engine game;


void init_game_engine( int sw, int sh, uint32 frame_delay )
{
  game.current_time = SDL_GetTicks();
  game.previous_time = game.current_time;
  game.current_frame = 0;
  
  vec2_set( game.resolution, sw, sh );
  game.frame_delay = frame_delay;
  
  glGetDoublev( GL_MODELVIEW_MATRIX, game.model_matrix );
  glGetIntegerv( GL_VIEWPORT, game.view_matrix );
  glGetDoublev( GL_PROJECTION_MATRIX, game.projection_matrix );
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
  return game.model_matrix;
}


int* get_view_matrix()
{
  return game.view_matrix;
}


double* get_projection_matrix()
{
  return game.projection_matrix;
}


void game_start( char *game_config )
{
  game.config = parse( game_config );
  
  str_vec3( find_dict( game.config, "default_camera_position" ), game.default_camera_position );
  str_vec3( find_dict( game.config, "default_camera_rotation" ), game.default_camera_rotation );
  set_camera( game.default_camera_position, game.default_camera_rotation );
}


void game_check()
{
  
}


void game_end()
{
  
}



























/* eof */