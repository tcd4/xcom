#include <stdlib.h>
#include <SDL.h>

#include "parser.h"
#include "logger.h"
#include "graphics3d.h"
#include "shader.h"
#include "obj.h"
#include "sprite.h"
#include "cmds.h"
#include "entity.h"
#include "camera.h"
#include "game.h"
#include "game_math.h"
#include "grid.h"


void end_game();


static uint8	_game_over = 0;
static Dict	*_sys_config;

static uint8 _init_systems();
static uint8 _init_SDL();
static uint8 _init_cmds();
static uint8 _init_graphics();
static uint8 _init_ents();

static void _loop();

static void _exit_systems();


static uint8 _init_systems()
{
  _sys_config = parse( "../cfg/system_config.def" );
  if( !_sys_config )
    return FALSE;
  
  if( !init_logger( find_dict( _sys_config, "log_file" ) ) )
    return FALSE;
  
  log( INFO, "initializing systems" );
  
  if( !_init_SDL() )
    return FALSE;
  
  if( enable_logger_threading() )
    log( INFO, "threaded logger initialized" );
  
  if( !_init_cmds() )
    return FALSE;
  
  if( !_init_graphics() )
    return FALSE;
  
  if( !init_camera() )
    return FALSE;
  
  if( !_init_ents() )
    return FALSE;
  
  
  log( INFO, "systems initialized" );
  return TRUE;
}


static uint8 _init_SDL()
{
  log( INFO, "initializing SDL" );
  
  if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
  {
    log( FATAL, "failed to initialize SDL" );
    return FALSE;
  }
  
  log( INFO, "SDL initialized" );
  return TRUE;
}


static uint8 _init_cmds()
{
  log( INFO, "initializing command system" );
  
  if( !init_command_system() )
    return FALSE;
  
  log( INFO, "adding quit command" );
  if( !add_cmd( "game_over", NULL, SDL_KEYUP, SDLK_F12, end_game, NULL ) )
    return FALSE;

  turn_on_cmd( "game_over" );
  
  log( INFO, "command system initialized" );
  return TRUE;
}


static uint8 _init_graphics()
{
  vec2_t res;
  uint32 fd;
  int flags = 0;
  
  log( INFO, "initializing graphics" );
  
  str_uint( find_dict( _sys_config, "frame_delay" ), &fd );
  str_vec2( find_dict( _sys_config, "resolution" ), res );
  flags |= SDL_WINDOW_SHOWN;
  flags |= SDL_WINDOW_OPENGL;
  flags |= SDL_WINDOW_FULLSCREEN;
  flags |= SDL_WINDOW_BORDERLESS;
  
  if( graphics3d_init( res[ XA ], res[ YA ], 1, "xcom", fd ) < 0 )
    return FALSE;
  
  log( INFO, "graphics initialized" );
  
  log( INFO, "initializing model system" );
  model_init();
  log( INFO, "model system initialized" );
  
  log( INFO, "initializing obj system" );
  obj_init();
  log( INFO, "obj system initialized" );
  
  log( INFO, "initializing sprite system" );
  InitSpriteList();
  log( INFO, "sprite system initialized" );
  
  return TRUE;
}


static uint8 _init_ents()
{
  uint32 max;
  
  log( INFO, "initializing entity system" );
  
  str_uint( find_dict( _sys_config, "max_entities" ), &max );
  if( !init_entity_system( max ) )
    return FALSE;
  
  log( INFO, "entity system initialized" );
  return TRUE;
}













void _loop()
{
  SDL_Event event;/*
  Obj *tile;
  Sprite *texture;
  vec3_t p, s, r;
  vec4_t c;
  
  
  Sprite* test;
  vec2_t p, s, r;
  
  test = LoadSprite( "../models/attack.png", -1, -1 );
  vec2_set( p, 500, 500 );
  vec2_set( s, 1, 1 );
  vec2_set( r, 0, 0 );
  */
  game_start( find_dict( _sys_config, "game_config" ) );
  
  while( !_game_over )
  {
    game_check();
    update_all_entities();
    
    /* move space */
    
    while( SDL_PollEvent( &event ) )
    {
      if( event.type == SDL_QUIT )
	_game_over = 1;
      else
	check_cmds( &event );
    }
    
    graphics3d_frame_begin();
    
    glPushMatrix();
    move_camera();
    draw_grid();
    draw_all_entities();
    /*draw_sprite( test, p, s, r, 1 );*/
    
    glPopMatrix();
    
    graphics3d_next_frame();
  }
}


void end_game()
{
  _game_over = 1;
}


static void _exit_systems()
{
  log( INFO, "!!!!!SHUTTING DOWN!!!!!" );
  
  free_dict( _sys_config );
  
  exit_entity_system();
  log( INFO, "entity system shutdown" );
  
  exit_command_system();
  log( INFO, "command system shutdown" );
  
  exit_logging();
  SDL_Quit();
}


int main( int argc, const char *argv[] )
{
  atexit( _exit_systems );
  
  if( !_init_systems() )
    exit( -1 );
  
  _loop();
  
  exit( 0 );
  return 0;
}


/* eof */