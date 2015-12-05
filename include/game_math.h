#ifndef __GAME_MATH__
#define __GAME_MATH__


/**
 * @file game_math.h
 * 
 * @brief file for handling various math functions
 */


#include "types.h"


/* standard math defines */

/*< PI define */
#define PI 3.14159265

/*< TAU define */
#define TAU 6.283185308

/*< radian to degree conversion constant */
#define TODEG 57.2957795

/*< degree to radian conversion constant */
#define TORAD 0.0174532925

/*< converts an angle from radians to degrees */
#define angle_to_deg( a )                       ( a * TODEG )

/*< converts an angle from degrees to radians */
#define angle_to_rad( a )                       ( a * TORAD )


/* random macros */

/**
 * @brief random macro from Id Software's Quake 2 Source
 * This macro makes rand() more random
 *
 * @return a random float from 0 to 1.0
 */
#define random()	( ( rand() & 0x7fff ) / ( ( float )0x7fff ) )

/**
 * @brief random macro from Id Software's Quake 2 Source
 * 
 * @return a random float from -1.0 to 1.0
 */
#define crandom()	( 2.0 * ( random() - 0.5 ) )

/**
 * @brief random macro for integer values
 * 
 * @return a random int from 0 to 100
 */
#define irandom()	( ( int )( random() * 100 ) )

/**
 * @brief random macro for integer in a range of values
 * 
 * @param start	the starting value of the range
 * @param end	the ending value of the range
 * 
 * @return a int between start and end
 */
#define rand_ranged( start, end )	( ( int )( random() * ( end - start ) + start ) )


/* vector macros */

/*< sets a 2d vector */
#define vec2_set( v, a, b )			( v[ XA ] = a, v[ YA ] = b )

/*< subtracts 2 2d vectors */
#define vec2_subtract( a, b, c )	        ( c[ XA ] = a[ XA ] - b[ XA ], c[ YA ] = a[ YA ] - b[ YA ] )

/*< adds 2 2d vectors */
#define vec2_add( a, b, c )		        ( c[ XA ] = a[ XA ] + b[ XA ], c[ YA ] = a[ YA ] + b[ YA ] )

/*< finds the dot product of 2 2d vectors */
#define vec2_dot_product( a, b )                ( a[ XA ] * b[ XA ] + a[ YA ] * b[ YA ] )

/*< copys 2d vector a into b */
#define vec2_copy( a, b )		        ( b[ XA ] = a[ XA ], b[ YA ] = a[ YA ] )

/*< sets a 2d vector to [ 0, 0 ] */
#define vec2_clear( a )			        ( a[ XA ] = 0, a[ YA ] = 0 )

/*< checks if 2 2d vectors are equal */
#define vec2_compare( a, b )		        ( ( a[ XA ] == b[ XA ] && a[ YA ] == b[ YA ] ) ? 1: 0 )

/*< checks if a 2d vector is zeroed */
#define vec2_zeroed( a )			( ( a[ XA ] == 0 && a[ YA ] == 0 ) ? 1: 0 )

/*< scales a 2d vector */
#define vec2_scale( dst, src, factor )          ( dst[ XA ] = src[ XA ] * factor, dst[ YA ] = src[ YA ] * factor )

/*< sets a 3d vector */
#define vec3_set( v, a, b, c )			( vec2_set( v, a, b ), v[ ZA ] = c )

/*< subtracts 2 3d vectors */
#define vec3_subtract( a, b, c )	        ( vec2_subtract( a, b, c ), c[ ZA ] = a[ ZA ] - b[ ZA ] )

/*< adds 2 3d vectors */
#define vec3_add( a, b, c )		        ( vec2_add( a, b, c ), c[ ZA ] = a[ ZA ] + b[ ZA ] )

/*< finds the dot product of 2 3d vectors */
#define vec3_dot_product( a, b )                ( vec2_dot_product( a, b ) + a[ ZA ] * b[ ZA ] )

/*< copys 3d vector a into b */
#define vec3_copy( a, b )		        ( vec2_copy( a, b ), b[ ZA ] = a[ ZA ] )

/*< sets a 3d vector to [ 0, 0, 0 ] */
#define vec3_clear( a )			        ( vec2_clear( a ), a[ ZA ] = 0 )

/*< checks if 2 3d vectors are equal */
#define vec3_compare( a, b )		        ( ( vec2_compare( a, b ) && a[ ZA ] == b[ ZA ] ) ? 1: 0 )

/*< checks if a 3d vector is zeroed */
#define vec3_zeroed( a )			( ( a[ XA ] == a[ YA ] == a[ ZA ] == 0 ) ? 1: 0 )

/*< scales a 3d vector */
#define vec3_scale( dst, src, factor )          ( vec2_scale( dst, src, factor ), dst[ ZA ] = src[ ZA ] * factor )

/*< sets a 4d vector */
#define vec4_set( v, a, b, c, d )		( vec3_set( v, a, b, c ), v[ AA ] = d )

/*< subtracts 2 4d vectors */
#define vec4_subtract( a, b, c )	        ( vec3_subtract( a, b, c ), c[ AA ] = a[ AA ] - b[ AA ] )

/*< adds 2 4d vectors */
#define vec4_add( a, b, c )		        ( vec3_add( a, b, c ), c[ AA ] = a[ AA ] + b[ AA ] )

/*< finds the dot product of 2 4d vectors */
#define vec4_dot_product( a, b )                ( vec3_dot_product( a, b ) + a[ AA ] * b[ AA ] )

/*< copys 4d vector a into b */
#define vec4_copy( a, b )		        ( vec3_copy( a, b ), b[ AA ] = a[ AA ] )

/*< sets a 4d vector to [ 0, 0, 0, 0 ] */
#define vec4_clear( a )			        ( vec3_clear( a ), a[ AA ] = 0 )

/*< checks if 2 4d vectors are equal */
#define vec4_compare( a, b )		        ( ( vec3_compare( a, b ) && a[ AA ] == b[ AA ] ) ? 1: 0 )

/*< checks if a 4d vector is zeroed */
#define vec4_zeroed( a )			( ( a[ XA ] == a[ YA ] == a[ ZA ] == a[ AA ] == 0 ) ? 1: 0 )

/*< scales a 4d vector */
#define vec4_scale( dst, src, factor )          ( vec3_scale( dst, src, factor ), dst[ AA ] = src[ AA ] * factor )



/* vector functions */


/**
 * @brief normalizes a vector
 *
 * @param v the vector to normalize
 */
void vec2_normalize( vec2_t *v );

/**
 * @brief gets the magnitude of a vector
 *
 * @param v the vector to use
 *
 * @return the magnitude of a vector
 */
float vec2_get_magnitude( vec2_t v );

/**
 * @brief normalizes a vector then sets its magnitude
 *
 * @param v the vector to use
 * @param m the magnitude to set the vector to
 */
void vec2_set_magnitude( vec2_t *v, float m );

/**
 * @brief compares the magnitudes of 2 vectors
 *
 * @param v1 the 1st vector to compare
 * @param v2 the 2nd vector to compare
 *
 * @return 1 if v1 > v2, 0 if v1 == v2, -1 if v1 < v2
 */
int8 vec2_magnitude_compare( vec2_t v1, vec2_t v2 );

/**
 * @brief gets the distance between 2 vectors
 *
 * @param v1 the 1st vector to use
 * @param v2 the 2nd vector to use
 *
 * @return the distance between the 2 vectors
 */
uint32 vec2_distance_between( vec2_t v1, vec2_t v2 );

/**
 * @brief sets the angle of a vector
 *
 * @param v the vector to use
 * @param a the angle ( in degrees ) to use
 */
void vec2_set_angle_degs( vec2_t *v, float a );

/**
 * @brief sets the angle of a vector
 *
 * @param v the vector to use
 * @param a the angle ( in radians ) to use
 */
void vec2_set_angle_rads( vec2_t *v, float a );

/**
 * @brief normalizes a vector
 *
 * @param v the vector to normalize
 */
void vec3_normalize( vec3_t *v );

/**
 * @brief gets the magnitude of a vector
 *
 * @param v the vector to use
 *
 * @return the magnitude of a vector
 */
float vec3_get_magnitude( vec3_t v );

/**
 * @brief normalizes a vector then sets its magnitude
 *
 * @param v the vector to use
 * @param m the magnitude to set the vector to
 */
void vec3_set_magnitude( vec3_t *v, float m );

/**
 * @brief compares the magnitudes of 2 vectors
 *
 * @param v1 the 1st vector to compare
 * @param v2 the 2nd vector to compare
 *
 * @return 1 if v1 > v2, 0 if v1 == v2, -1 if v1 < v2
 */
int8 vec3_magnitude_compare( vec3_t v1, vec3_t v2 );

/**
 * @brief gets the distance between 2 vectors
 *
 * @param v1 the 1st vector to use
 * @param v2 the 2nd vector to use
 *
 * @return the distance between the 2 vectors
 */
uint32 vec3_distance_between( vec3_t v1, vec3_t v2 );

/**
 * @brief sets the angle of a vector
 *
 * @param v the vector to use
 * @param a the angle ( in degrees ) to use
 */
void vec3_set_angle_degs( vec3_t *v, float a );

/**
 * @brief sets the angle of a vector
 *
 * @param v the vector to use
 * @param a the angle ( in radians ) to use
 */
void vec3_set_angle_rads( vec3_t *v, float a );

/**
 * @brief normalizes a vector
 *
 * @param v the vector to normalize
 */
void vec4_normalize( vec4_t *v );

/**
 * @brief gets the magnitude of a vector
 *
 * @param v the vector to use
 *
 * @return the magnitude of a vector
 */
float vec4_get_magnitude( vec4_t v );

/**
 * @brief normalizes a vector then sets its magnitude
 *
 * @param v the vector to use
 * @param m the magnitude to set the vector to
 */
void vec4_set_magnitude( vec4_t *v, float m );

/**
 * @brief compares the magnitudes of 2 vectors
 *
 * @param v1 the 1st vector to compare
 * @param v2 the 2nd vector to compare
 *
 * @return 1 if v1 > v2, 0 if v1 == v2, -1 if v1 < v2
 */
int8 vec4_magnitude_compare( vec4_t v1, vec4_t v2 );

/**
 * @brief gets the distance between 2 vectors
 *
 * @param v1 the 1st vector to use
 * @param v2 the 2nd vector to use
 *
 * @return the distance between the 2 vectors
 */
uint32 vec4_distance_between( vec4_t v1, vec4_t v2 );

/**
 * @brief sets the angle of a vector
 *
 * @param v the vector to use
 * @param a the angle ( in degrees ) to use
 */
void vec4_set_angle_degs( vec4_t *v, float a );

/**
 * @brief sets the angle of a vector
 *
 * @param v the vector to use
 * @param a the angle ( in radians ) to use
 */
void vec4_set_angle_rads( vec4_t *v, float a );


/* standard math functions */

/**
 * @brief calculates an angle from an x and a y
 *
 * @param x the length to use
 * @param y the height to use
 *
 * @return an angle in degrees
 */
float get_angle_deg( float x, float y );

/**
 * @brief calculates an angle from an x and a y
 *
 * @param x the length to use
 * @param y the height to use
 *
 * @return an angle in radians
 */
float get_angle_rad( float x, float y );

/**
 * @brief calculates the cross product of 2 3d vectors
 *
 * @param out	the output vector
 * @param v1	the 1st vector to use
 * @param v2	the 2nd vector to use
 */
void cross_product( vec3_t *out, vec3_t v1, vec3_t v2 );


#ifndef MIN
/**< finds the min out of 2 variables */
#define MIN( a, b )     ( ( a <= b ) ? a : b );
#endif

#ifndef MAX
/**< finds the max out of 2 variables */
#define MAX( a, b )     ( ( a >= b ) ? a : b );
#endif


#endif