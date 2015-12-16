#ifndef __CAMERA__
#define __CAMERA__


/**
 * @file camera.h
 * 
 * @brief set of functions for camera control
 */


#include "types.h"


/**
 * @brief initializes the camera and its controls
 * 
 * @return TRUE on success, FALSE if else
 */
uint8 init_camera();

/**
 * @brief sets the camera position
 * 
 * @param x the x position
 * @param y the y position
 * @param z the z position
 */
void set_camera_position( double x, double y, double z );

/**
 * @brief sets the camera rotation
 * 
 * @param x the x rotation
 * @param y the y rotation
 * @param z the z rotation
 */
void set_camera_rotation( double x, double y, double z );

/**
 * @brief sets the camera position
 * 
 * @param pos the new camera position
 */
void set_camera_position_v( vec3_t pos );

/**
 * @brief sets the camera rotation
 * 
 * @param pos the new camera rotation
 */
void set_camera_rotation_v( vec3_t rot );

/**
 * @brief sets the camera rotation and postion
 * 
 * @param pos the new camera position
 * @param rot the new camera rotation
 */
void set_camera( vec3_t pos, vec3_t rot );

/**
 * @brief gets the camera position

 * @return the camera position
 */
vec_t* get_camera_position();

/**
 * @brief gets the camera rotation
 * 
 * @return the camera rotation
 */
vec_t* get_camera_rotation();

/**
 * @brief moves the camera in the world
 */
void move_camera();

/**
 * @brief turns on the camera controls
 */
void turn_on_camera_controls();

/**
 * @brief turns off the camera controls
 */
void turn_off_camera_controls();

/**
 * @brief moves the camera forwards
 */
void camera_forward( data param );

/**
 * @brief moves the camera backwards
 */
void camera_backward( data param );

/**
 * @brief moves the camera right
 */
void camera_right( data param );

/**
 * @brief moves the camera left
 */
void camera_left( data param );

/**
 * @brief rotates the world 45 degrees around the center point
 */
void camera_rotate_right( data param );

/**
 * @brief rotates the world -45 degrees around the center point
 */
void camera_rotate_left( data param );


#endif