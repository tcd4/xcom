#include "camera.h"
#include "game_math.h"

#include <GL/glew.h>


static vec3_t position;
static vec3_t rotation;


void set_camera_position( vec3_t pos )
{
  vec3_copy( pos, position );
}


void set_camera_rotation( vec3_t rot )
{
  vec3_copy( rot, rotation );
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
  glRotatef( -rotation[ XA ], 1.0f, 0.0f, 0.0f );
  glRotatef( -rotation[ YA ], 0.0f, 1.0f, 0.0f );
  glRotatef( -rotation[ ZA ], 0.0f, 0.0f, 1.0f );
  
  glTranslatef( -position[ XA ], -position[ YA ], -position[ ZA ] );
}


/* eof */