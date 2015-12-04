#include <stdlib.h>

#include "parser.h"
#include "logger.h"



static uint8 _init_systems();
static uint8 _init_SDL();

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
  /*
  if( enable_logger_threading() )
    log( INFO, "threaded logger initialized" );
  */
  log( INFO, "systems initialized" );
  free_dict( config );
  return TRUE;
}


static uint8 _init_SDL()
{
  return TRUE;
}


static void _exit_systems()
{
  exit_logging();
}


int main( int argc, const char *argv[] )
{
  if( !_init_systems() )
    exit( -1 );
  
  
  _exit_systems();
  
  exit( 0 );
  return 0;
}


/* eof */