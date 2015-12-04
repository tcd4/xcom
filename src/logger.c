#include <stdio.h>
#include <SDL.h>
#include <glib/gprintf.h>

#include "logger.h"


static uint8		_logging_flags = 0;
static FILE		*_log_file = NULL;
static GAsyncQueue	*_log_queue = NULL;
static SDL_Thread	*_logging_thread = NULL;

static int	_logger_thread_func( data param );
static void	_write_msg( char *msg );


uint8 init_logger( char *log_file )
{
  if( logger_is_init() )
  {
    log( WARN, "logger already initialized" );
    return TRUE;
  }
  
  _log_file = fopen( log_file, "w" );
  if( !_log_file )
    return FALSE;
  
  _logging_flags |= LOG_INITIALIZED;
  _logging_flags |= LOG_LOGGING;
  return TRUE;
}


uint8 logger_is_init()
{
  return ( ( _logging_flags & LOG_INITIALIZED ) ? TRUE: FALSE );
}


uint8 logger_is_threaded()
{
  return ( ( _logging_flags & LOG_THREADED ) ? TRUE: FALSE );
}


uint8 logger_is_logging()
{
  return ( ( _logging_flags & LOG_LOGGING ) ? TRUE: FALSE );
}


uint8 enable_logger_threading()
{
  if( !logger_is_init() )
    return FALSE;
  
  if( logger_is_threaded() )
  {
    log( WARN, "logger is already threaded" );
    return TRUE;
  }
  
  _log_queue = g_async_queue_new();
  if( !_log_queue )
  {
    log( ERROR, "couldn't allocate memory for the log queue" );
    return FALSE;
  }
  
  _logging_thread = SDL_CreateThread( _logger_thread_func, "logger", NULL );
  SDL_DetachThread( _logging_thread );
  
  
  _logging_flags |= LOG_THREADED;
  return TRUE;
}


char* log_level_to_str( Log_Level lvl )
{
  char *l;
  
  l = g_new0( char, 5 );
  
  switch( lvl )
  {    
    case 1:
      l = "FATAL";
      break;
      
    case 2:
      l = "ERROR";
      break;
      
    case 3:
      l = "WARN";
      break;
      
    case 4:
      l = "TRACE";
      break;
      
    case 5:
      l = "INFO";
      break;
      
    case 6:
      l = "ALL";
      break;
      
    default:
      l = "NONE";
      break;
  }
  
  return l;
}


void log_msg( char *file, int line, Log_Level lvl, char *msg, ... )
{
  char *buffer, *message, *level;
  va_list ap;
  
  if( !logger_is_init() )
    return;
  
  va_start( ap, msg );
  g_vasprintf( &buffer, msg, ap );
  va_end( ap );
  
  level = log_level_to_str( lvl );
  message = g_strdup_printf( "%s:%i --- %s\n%s", file, line, level, buffer );
  
  if( logger_is_threaded() )
    g_async_queue_push( _log_queue, message );
  else
    _write_msg( message );
}


int _logger_thread_func( data param )
{
  char *msg = NULL;
  
  while( logger_is_logging() || msg )
  {
    msg = ( char* )( g_async_queue_pop( _log_queue ) );
    if( msg )
      _write_msg( msg );
  }
  
  exit_logging();
  return 0;
}


void _write_msg( char *msg )
{
  /* cmd line printing */
  printf( "%s\n", msg );
  
  /* log file printing */
  fprintf( _log_file, "%s\n", msg );
  fflush( _log_file );
  
  g_free( msg );
}


void stop_logging()
{
  _logging_flags &= ~LOG_LOGGING;
}


void exit_logging()
{
  if( logger_is_threaded() )
  {
    stop_logging();
    return;
  }
  
  _logging_flags = 0;
  fflush( _log_file );
  fclose( _log_file );
}


/*eof*/