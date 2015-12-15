#include "opengl_funcs.h"

#include <GL/glu.h>
#include "game.h"
#include "logger.h"


void get_screen_coord( vec3_t position, vec2_t out )
{
  GLdouble z;
  gluProject( position[ XA ], position[ YA ], position[ ZA ], 
	      get_model_matrix(), get_projection_matrix(), get_view_matrix(),
	      out, out + 1, &z);
}


void get_world_coord( vec2_t position, vec3_t out )
{
  GLdouble y;
  y = get_view_matrix()[ 3 ] - position[ YA ];
  gluUnProject( position[ XA ], y, 0.99f, 
	      get_model_matrix(), get_projection_matrix(), get_view_matrix(),
	      out, out + 1, out + 2 );
}


/* eof */