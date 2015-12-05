#include <stdlib.h>
#include <SDL.h>

#include "parser.h"
#include "logger.h"
#include "graphics3d.h"
#include "game.h"
#include "cmds.h"


Game_Engine game;


void end_game();


static uint8 _game_over = 0;

static uint8 _init_systems();
static uint8 _init_SDL();
static uint8 _init_cmds();

static void _loop();

static void _exit_systems();


static uint8 _init_systems()
{
  Dict *config;
  
  config = parse( "../cfg/system_config.def" );
  if( !config )
    return FALSE;
  
  if( !init_logger( find_dict( config, "log_file" ) ) )
    return FALSE;
  
  log( INFO, "initializing systems" );
  
  GAME_TIME = 0;
  
  if( !_init_SDL() )
    return FALSE;
  
  if( enable_logger_threading() )
    log( INFO, "threaded logger initialized" );
  
  if( !_init_cmds() )
    return FALSE;
  
  log( INFO, "systems initialized" );
  free_dict( config );
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
    
  log( INFO, "command system initialized" );
  return TRUE;
}




void _loop()
{
  
}


void end_game()
{
  _game_over = 1;
}


static void _exit_systems()
{
  log( INFO, "shutting down" );
  
  exit_command_system();
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