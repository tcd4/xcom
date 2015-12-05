#include "game.h"
#include "graphics3d.h"
#include "logger.h"
#include "shader.h"


#include <GL/glu.h>


void setup_default_light();


uint8 init_graphics( vec2_t resolution, int screen_flags, char *name, uint32 frame_delay )
{
  const unsigned char *version;
  GLenum glew_status;
  
  game.frame_delay = frame_delay;
  game.window = SDL_CreateWindow( ( name ? name:"window" ), 
				  SDL_WINDOWPOS_UNDEFINED, 
				  SDL_WINDOWPOS_UNDEFINED,
				  resolution[ XA ],
				  resolution[ YA ],
				  screen_flags );
  
  game.context = SDL_GL_CreateContext( game.window );
  if( !game.context )
  {
    log( ERROR, "failed to create the OpenGL context" );
    return FALSE;
  }
  
  version = glGetString( GL_VERSION );
  if( !version )
  {
    log( ERROR, "failed to create the version" );
    return FALSE;
  }
  
  SDL_GL_MakeCurrent( game.window, game.context );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
  
  glewExperimental = GL_TRUE;
  glew_status = glewInit();
  if( glew_status )
  {
    log( ERROR, "glew error: %s", glewGetErrorString( glew_status ) );
    return FALSE;
  }
  
  glViewport( 0, 0, resolution[ XA ], resolution[ YA ] );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 40, resolution[ XA ] / resolution[ YA ], .01, 2000.0f );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glClearColor(0.0,0.0,0.0,0.0);
  glClear( 1 );
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  
  setup_default_light();
  
  return TRUE;
}


void setup_default_light()
{
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };
  GLfloat light_position[] = { -10.0, -10.0, 10.0, 0.0 };
  GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  
  GLfloat light1_ambient[] = { 1.2, 1.2, 1.2, 1.0 };
  GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light1_position[] = { -20.0, 2.0, 1.0, 1.0 };
  GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };
  
  GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  
  //glShadeModel (GL_SMOOTH);
  
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  
  
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  
  
  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.9);
  glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.7);
  glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.3);
  
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 80.0);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_DEPTH_TEST);
}


void frame_start()
{
  glClearColor(0.0,0.0,0.0,0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
  glPushMatrix();
}


void frame_end()
{
  glPopMatrix();
  SDL_GL_SwapWindow( game.window );
  
  game.current_time = SDL_GetTicks();
  if( game.current_time - game.previous_time < game.frame_delay )
    SDL_Delay( game.frame_delay - ( game.current_time - game.previous_time ) );
  
  game.previous_time = game.current_time;
}


void exit_graphics()
{
  SDL_GL_DeleteContext( game.context );
}


/* eof */