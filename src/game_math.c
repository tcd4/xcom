#include <math.h>

#include "game_math.h"


float get_angle_deg( float x, float y )
{    
  return angle_to_deg( atan2( y, x ) + PI );
}


float get_angle_rad( float x, float y )
{
  return ( atan2( y, x ) + PI ) ;
}


void cross_product( vec3_t *out, vec3_t v1, vec3_t v2 )
{
  *out[ 0 ] = v1[ 1 ] * v2[ 2 ] - v1[ 2 ] * v2[ 1 ];
  *out[ 1 ] = v1[ 2 ] * v2[ 0 ] - v1[ 0 ] * v2[ 2 ];
  *out[ 2 ] = v1[ 0 ] * v2[ 1 ] - v1[ 1 ] * v2[ 0 ];
}

void vec2_normalize( vec2_t *v )
{
  float m;

  if( !v )
    return;

  m = vec2_get_magnitude( *v );
  if( m != 0.0f )
    return;
  m = 1 / m;

  *v[ 0 ] *= m;
  *v[ 1 ] *= m;
}


float vec2_get_magnitude( vec2_t v )
{
  return sqrt( v[ 0 ] * v[ 0 ] + v[ 1 ] * v[ 1 ] );
}


void vec2_set_magnitude( vec2_t *v, float m )
{
  if( !v )
    return;

  vec2_normalize( v );
  
  *v[ 0 ] *= m;
  *v[ 1 ] *= m;
}


int8 vec2_magnitude_compare( vec2_t v1, vec2_t v2 )
{
  float m1, m2;

  m1 = vec2_get_magnitude( v1 );
  m2 = vec2_get_magnitude( v2 );

  if( m1 > m2 ) 
    return 1;
  else if( m1 < m2 ) 
    return -1;
  else 
    return 0;
}


uint32 vec2_distance_between( vec2_t v1, vec2_t v2 )
{
  vec2_subtract( v1, v2, v1 );

  return fabs( vec2_get_magnitude( v1 ) );
}


void vec2_set_angle_degs( vec2_t *v, float a )
{
  if( !v )
    return;

  a = angle_to_rad( a );

  *v[ 0 ] = cos( a );
  *v[ 1 ] = sin( a );
}


void vec2_set_angle_rads( vec2_t *v, float a )
{
  if( !v )
    return;

  *v[ 0 ] = cos( a );
  *v[ 1 ] = sin( a );
}


void vec3_normalize( vec3_t *v )
{
  float m;

  if( !v )
    return;

  m = vec3_get_magnitude( *v );
  if( m != 0.0f )
    return;
  m = 1 / m;

  *v[ 0 ] *= m;
  *v[ 1 ] *= m;
  *v[ 2 ] *= m;
}


float vec3_get_magnitude( vec3_t v )
{
  return sqrt( v[ 0 ] * v [ 0 ] + v[ 1 ] * v[ 1 ] + v[ 2 ] * v[ 2 ] );
}


void vec3_set_magnitude( vec3_t *v, float m )
{
  if( !v )
    return;

  vec3_normalize( v );
  
  *v[ 0 ] *= m;
  *v[ 1 ] *= m;
  *v[ 2 ] *= m;
}


int8 vec3_magnitude_compare( vec3_t v1, vec3_t v2 )
{
  float m1, m2;

  m1 = vec3_get_magnitude( v1 );
  m2 = vec3_get_magnitude( v2 );

  if( m1 > m2 ) 
    return 1;
  else if( m1 < m2 ) 
    return -1;
  else 
    return 0;
}


uint32 vec3_distance_between( vec3_t v1, vec3_t v2 )
{
  vec3_subtract( v1, v2, v1 );

  return fabs( vec3_get_magnitude( v1 ) );
}


void vec3_set_angle_degs( vec3_t *v, float a )
{
  if( !v )
    return;

  a = angle_to_rad( a );

  *v[ 0 ] = cos( a );
  *v[ 1 ] = sin( a );
}


void vec3_set_angle_rads( vec3_t *v, float a )
{
  if( !v )
    return;

  *v[ 0 ] = cos( a );
  *v[ 1 ] = sin( a );
}


void vec4_normalize( vec4_t *v )
{
  float m;

  if( !v )
    return;

  m = vec4_get_magnitude( *v );
  if( m != 0.0f )
    return;
  m = 1 / m;

  *v[ 0 ] *= m;
  *v[ 1 ] *= m;
  *v[ 2 ] *= m;
  *v[ 3 ] *= m;
}


float vec4_get_magnitude( vec4_t v )
{
  return sqrt( v[ 0 ] * v[ 0 ] + v[ 1 ] * v[ 1 ] + v[ 2 ] * v[ 2 ] + v[ 3 ] * v[ 3 ] );
}


void vec4_set_magnitude( vec4_t *v, float m )
{
  if( !v )
    return;

  vec4_normalize( v );
  
  *v[ 0 ] *= m;
  *v[ 1 ] *= m;
  *v[ 2 ] *= m;
  *v[ 3 ] *= m;
}


int8 vec4_magnitude_compare( vec4_t v1, vec4_t v2 )
{
  float m1, m2;

  m1 = vec4_get_magnitude( v1 );
  m2 = vec4_get_magnitude( v2 );

  if( m1 > m2 ) 
    return 1;
  else if( m1 < m2 ) 
    return -1;
  else 
    return 0;
}


uint32 vec4_distance_between( vec4_t v1, vec4_t v2 )
{
  vec4_subtract( v1, v2, v1 );

  return fabs( vec4_get_magnitude( v1 ) );
}


void vec4_set_angle_degs( vec4_t *v, float a )
{
  if( !v )
    return;

  a = angle_to_rad( a );

  *v[ 0 ] = cos( a );
  *v[ 1 ] = sin( a );
}


void vec4_set_angle_rads( vec4_t *v, float a )
{
  if( !v )
    return;

  *v[ 0 ] = cos( a );
  *v[ 1 ] = sin( a );
}


/*eof*/