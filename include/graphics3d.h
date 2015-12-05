#ifndef __GRAPHICS3D__
#define __GRAPHICS3D__


/**
 * @file graphics3d.h
 * 
 * @brief contains support for creating 3d graphics
 */


#include <SDL.h>
#include <GL/glew.h>

#include "types.h"


/**
 * @brief initializes 3d graphics
 * 
 * @param resolution the resolution of the window
 * @param screen_flags the flags to initialize the screen with
 * @param name the name of the window
 * @param frame_delay how often to update the window
 * 
 * @return TRUE on success, FALSE if else
 */
uint8 init_graphics( vec2_t resolution, int screen_flags, char *name, uint32 frame_delay, uint32 flags );

/**
 * @brief starts a new frame
 */
void frame_start();

/**
 * @brief ends a frame
 */
void frame_end();

/**
 * @brief frees a window
 */
void exit_graphics();

#endif