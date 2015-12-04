#include <yaml.h>

#include "parser.h"


static void _parse( yaml_parser_t *parser, Dict *dict );


Dict* parse( char *filename )
{
  Dict *parsed;
  FILE *file;
  yaml_parser_t parser;
  
  if( !yaml_parser_initialize( &parser ) ) 
    return NULL;

  file = fopen( filename, "r" );
  if( !file )
    return NULL;
  
  parsed = create_dict();  
  if( !parsed )
  {
    yaml_parser_delete( &parser );
    return NULL;
  }
  
  yaml_parser_set_input_file( &parser, file );
  
  _parse( &parser, parsed );
  
  yaml_parser_delete( &parser );
  fclose( file );
  
  return parsed;
}


static void _parse( yaml_parser_t *parser, Dict *dict )
{
  int done = 0;
  int state = 0;
  char key[ 128 ];
  Dict *next;
  yaml_event_t	event;
  
  strncpy( key, "", 128 );
  
  do
  {
    yaml_parser_parse( parser, &event );
    
    switch( event.type )
    {
      case YAML_SCALAR_EVENT:
	if( state == 0 )
	  strncpy( key, ( char* )event.data.scalar.value, 128 );
	else
	  add_str_dict( dict, key, ( char* )event.data.scalar.value );
	  
	state ^= 1;
	break;
	
      case YAML_SEQUENCE_START_EVENT:
	next = create_dict();
	add_dict_dict( dict, key, next );
	_parse( parser, next );
	break;
	
      case YAML_MAPPING_START_EVENT:
	break;
	
      case YAML_MAPPING_END_EVENT:
	break;
	
      case YAML_STREAM_END_EVENT:
	done = 1;
	break;
	
      case YAML_SEQUENCE_END_EVENT:
	done = 1;
	break;
	
      default:
	break;
    }
    
    if( parser->error != YAML_NO_ERROR ) return;
    
    yaml_event_delete( &event );
  }
  while( !done );
}


/*eof*/