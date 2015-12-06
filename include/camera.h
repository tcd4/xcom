#ifndef __CAMERA__
#define __CAMERA__


/**
 * @file camera.h
 * 
 * @brief set of functions for camera control
 */


#include "types.h"


void set_camera_position( vec3_t pos );
void set_camera_rotation( vec3_t rot );
void set_camera( vec3_t pos, vec3_t rot );

vec_t* get_camera_position();
vec_t* get_camera_rotation();

void move_camera();


#endif