#ifndef __OPENGL_H__
#define __OPENGL_H__


/**
 * @file opengl_funcs.h
 * 
 * @brief file for certain functions in opengl
 */


#include "types.h"

#include <GL/glew.h>


/**
 * @brief converts a world coordinate to a screen coordinate
 * 
 * @param position the world coordinate
 * @param out the output vector containing the screen coordinate
 */
void get_screen_coord( vec3_t position, vec2_t out );

/**
 * @brief converts a screen coordinate to a world coordinate
 * 
 * @param position the screen coordinate
 * @param out the output vector containing the world coordinate
 */
void get_world_coord( vec2_t position, vec3_t out );


#endif