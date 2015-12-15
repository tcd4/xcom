#include <GL/glew.h>
#include "cmds.h"
#include "camera.h"
#include "game_math.h"
#include "logger.h"
#include "game.h"


static vec3_t position;
static vec3_t rotation;
static double circular_rotation;


uint8 init_camera()
{
  vec3_clear( position );
  vec3_clear( rotation );
  circular_rotation = 90;
  
  if( !add_cmd_map( "camera_controls" ) )
    return FALSE;
  
  if( !add_cmd( "camera_forward", "camera_controls", SDL_KEYDOWN, SDLK_w, camera_forward, NULL ) )
    return FALSE;
  
  if( !add_cmd( "camera_backward", "camera_controls", SDL_KEYDOWN, SDLK_s, camera_backward, NULL ) )
    return FALSE;
  /*
  if( !add_cmd( "camera_right", "camera_controls", SDL_KEYDOWN, SDLK_d, camera_right, NULL ) )
    return FALSE;
  
  if( !add_cmd( "camera_left", "camera_controls", SDL_KEYDOWN, SDLK_a, camera_left, NULL ) )
    return FALSE;
  */
  if( !add_cmd( "camera_rotate_right", "camera_controls", SDL_KEYDOWN, SDLK_q, camera_rotate_right, NULL ) )
    return FALSE;
  
  if( !add_cmd( "camera_rotate_left", "camera_controls", SDL_KEYDOWN, SDLK_e, camera_rotate_left, NULL ) )
    return FALSE;
  
  return TRUE;
}


void set_camera_position_v( vec3_t pos )
{
  vec3_copy( pos, position );
}


void set_camera_rotation_v( vec3_t rot )
{
  vec3_copy( rot, rotation );
}


void set_camera_position( double x, double y, double z )
{
  vec3_set( position, x, y, z );
}


void set_camera_rotation( double x, double y, double z )
{
  vec3_set( rotation, x, y, z );
}


void set_camera( vec3_t pos, vec3_t rot )
{
  vec3_copy( pos, position );
  vec3_copy( rot, rotation );
}


vec_t* get_camera_position()
{
  return position;
}


vec_t* get_camera_rotation()
{
  return rotation;
}


void move_camera()
{
  vec_t *center;
  
  center = get_grid_center();
  gluLookAt( position[ XA ], position[ YA ], position[ ZA ], center[ XA ], center[ YA ], 0, 0, 0, 1 );
}


void turn_on_camera_controls()
{
  turn_on_cmd_map( "camera_controls" );
}


void turn_off_camera_controls()
{
  turn_off_cmd_map( "camera_controls" );
}


void camera_forward( data param )
{
  vec_t *center;
  vec3_t normal;
  
  center = get_grid_center();
  vec3_copy( position, normal );
  vec2_subtract( center, normal, normal );
  vec3_normalize( normal );
  vec3_add( position, normal, position );
}

void camera_backward( data param )
{
  vec_t *center;
  vec3_t normal;
  
  center = get_grid_center();
  vec3_copy( position, normal );
  vec2_subtract( center, normal, normal );
  vec3_normalize( normal );
  vec3_subtract( position, normal, position );
}


void camera_right( data param )
{
  position[ ZA ]++;
}


void camera_left( data param )
{
  position[ ZA ]--;
}


void camera_rotate_right( data param )
{
  double radius, angle, rot;
  vec_t *center;
  vec2_t pos;
  
  center = get_grid_center();
  rot = ( ( int )( rotation[ ZA ] ) + 45 ) % 360;
  circular_rotation = rot - 90;
  
  pos[ XA ] = center[ XA ] - position[ XA ];
  pos[ YA ] = center[ YA ] - position[ YA ];
  radius = sqrt( pos[ XA ] * pos[ XA ] + pos[ YA ] * pos[ YA ] );
  
  angle = angle_to_rad( circular_rotation );
  position[ XA ] = center[ XA ] + radius * sin( angle );
  position[ YA ] = center[ YA ] + radius * cos( angle );
  
  rotation[ ZA ] = rot;
}


void camera_rotate_left( data param )
{
  double radius, angle, rot;
  vec_t *center;
  vec2_t pos;
  
  center = get_grid_center();
  rot = ( ( int )( rotation[ ZA ] ) - 45 ) % 360;
  circular_rotation = rot - 90;
  
  pos[ XA ] = center[ XA ] - position[ XA ];
  pos[ YA ] = center[ YA ] - position[ YA ];
  radius = sqrt( pos[ XA ] * pos[ XA ] + pos[ YA ] * pos[ YA ] );
  
  angle = angle_to_rad( circular_rotation );
  position[ XA ] = center[ XA ] + radius * sin( angle );
  position[ YA ] = center[ YA ] + radius * cos( angle );
  
  rotation[ ZA ] = rot;
}


/* eof */