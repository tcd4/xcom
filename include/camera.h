#ifndef __CAMERA__
#define __CAMERA__


/**
 * @file camera.h
 * 
 * @brief set of functions for camera control
 */


#include "types.h"


uint8 init_camera();

void set_camera_position( double x, double y, double z );
void set_camera_rotation( double x, double y, double z );
void set_camera_position_v( vec3_t pos );
void set_camera_rotation_v( vec3_t rot );
void set_camera( vec3_t pos, vec3_t rot );

vec_t* get_camera_position();
vec_t* get_camera_rotation();

void move_camera();

void turn_on_camera_controls();
void turn_off_camera_controls();
void camera_forward( data param );
void camera_backward( data param );
void camera_right( data param );
void camera_left( data param );
void camera_rotate_right( data param );
void camera_rotate_left( data param );


#endif