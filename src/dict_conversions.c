#include "dict_conversions.h"
#include "game_math.h"

#include <stdio.h>


uint8 str_bool( char *str, uint8 *out )
{
  uint8 tmp = 0;
  
  if( !str || !out )
    return FALSE;
  
  if( sscanf( str, "%hhu", &tmp ) != 1 )
    return FALSE;
  
  *out = tmp;
  return TRUE;
}


uint8 str_uint( char *str, uint32 *out )
{
  uint32 tmp = 0;
  
  if( !str || !out )
    return FALSE;
  
  if( sscanf( str, "%u", &tmp ) != 1 )
    return FALSE;
  
  *out = tmp;
  return TRUE;
}


uint8 str_int( char *str, int *out )
{
  int tmp = 0;
  
  if( !str || !out )
    return FALSE;
  
  if( sscanf( str, "%i", &tmp ) != 1 )
    return FALSE;
  
  *out = tmp;
  return TRUE;
}


uint8 str_float( char *str, float *out )
{
  float tmp = 0;
  
  if( !str || !out )
    return FALSE;
  
  if( sscanf( str, "%f", &tmp ) != 1 )
    return FALSE;
  
  *out = tmp;
  return TRUE;
}


uint8 str_double( char *str, double *out )
{
  double tmp = 0;
  
  if( !str || !out )
    return FALSE;
  
  if( sscanf( str, "%lf", &tmp ) != 1 )
    return FALSE;
  
  *out = tmp;
  return TRUE;
}


uint8 str_vec2( char *str, vec_t *out )
{
  vec2_t tmp;
  
  if( !str || !out )
    return FALSE; 
  
  vec2_clear( tmp );
  
  if( sscanf( str, "%lf,%lf", &tmp[ 0 ], &tmp[ 1 ] ) != 2 )
    return FALSE;
  
  vec2_copy( tmp, out );
  return TRUE;
}


uint8 str_vec3( char *str, vec_t *out )
{
  vec3_t tmp;
  
  if( !str || !out )
    return FALSE; 
  
  vec3_clear( tmp );
  
  if( sscanf( str, "%lf,%lf,%lf", &tmp[ 0 ], &tmp[ 1 ], &tmp[ 2 ] ) != 3 )
    return FALSE;
  
  vec3_copy( tmp, out );
  return TRUE;
}


uint8 str_vec4( char *str, vec_t *out )
{
  vec4_t tmp;
  
  if( !str || !out )
    return FALSE; 
  
  vec4_clear( tmp );
  
  if( sscanf( str, "%lf,%lf,%lf,%lf", &tmp[ 0 ], &tmp[ 1 ], &tmp[ 2 ], &tmp[ 3 ] ) != 3 )
    return FALSE;
  
  vec4_copy( tmp, out );
  return TRUE;
}



/* eof */