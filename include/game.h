#ifndef __GAME__
#define __GAME__


/**
 * @file game.h
 * 
 * @brief has the basic game struct
 */


#include <SDL.h>
#include <GL/glew.h>

#include "types.h"


typedef struct engine_s
{
  SDL_Window	*window;
  SDL_GLContext	context;
  
  GLuint	shader_program;
  GLuint 	vertex_buffer;
  GLuint 	UV_buffer;
  GLuint 	normal_buffer;
  
  uint32	frame_delay;
  uint32	current_time;
  uint32	previous_time;
  uint32	current_frame;
  
  vec2_t	resolution;
}Game_Engine;


extern Game_Engine game;


#define GAME_TIME game.current_time
#define GAME_FRAME game.current_frame
#define WINDOW_RESOLUTION game.resolution
#define SHADER_PROGRAM game.shader_program

#endif