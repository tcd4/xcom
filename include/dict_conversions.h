#ifndef __DICT_CONVERSIONS__
#define __DICT_CONVERSIONS__


#include "types.h"


/**
 * @brief converts a string to a bool
 * 
 * @param str the string to convert
 * @param out the output variable
 * 
 * @return TRUE on success, FALSE on error
 */
uint8 str_bool( char *str, uint8 *out );

/**
 * @brief converts a string to an uint32
 * 
 * @param str the string to convert
 * @param out the output variable
 * 
 * @return TRUE on success, FALSE on error
 */
uint8 str_uint( char *str, uint32 *out );

/**
 * @brief converts a string to an int
 * 
 * @param str the string to convert
 * @param out the output variable
 * 
 * @return TRUE on success, FALSE on error
 */
uint8 str_int( char *str, int *out );

/**
 * @brief converts a string to a float
 * 
 * @param str the string to convert
 * @param out the output variable
 * 
 * @return TRUE on success, FALSE on error
 */
uint8 str_float( char *str, float *out );

/**
 * @brief converts a string to a double
 * 
 * @param str the string to convert
 * @param out the output variable
 * 
 * @return TRUE on success, FALSE on error
 */
uint8 str_double( char *str, double *out );

/**
 * @brief converts a string to a vec2_t
 * 
 * @param str the string to convert
 * @param out the output variable
 * 
 * @return TRUE on success, FALSE on error
 */
uint8 str_vec2( char *str, vec_t *out );

/**
 * @brief converts a string to a vec3_t
 * 
 * @param str the string to convert
 * @param out the output variable
 * 
 * @return TRUE on success, FALSE on error
 */
uint8 str_vec3( char *str, vec_t *out );

/**
 * @brief converts a string to a vec4_t
 * 
 * @param str the string to convert
 * @param out the output variable
 * 
 * @return TRUE on success, FALSE on error
 */
uint8 str_vec4( char *str, vec_t *out );



#endif