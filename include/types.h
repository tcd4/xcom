#ifndef __MY_TYPES__
#define __MY_TYPES__


/**
 * @file types.h
 * 
 * @brief contains types that I like to use
 */


#include <glib.h>


/* unsigned sized int defines */

typedef unsigned char	uint8;		/**< unsigned 8 bit integer  */
typedef unsigned short	uint16;		/**< unsigned 16 bit integer */
typedef unsigned int	uint32;		/**< unsigned 32 bit integer */
typedef unsigned long	uint64;		/**< unsigned 64 bit integer */

/* signed sized int defines */

typedef signed char	int8;		/**< signed 8 bit integer  */
typedef signed short	int16;		/**< signed 16 bit integer */
typedef signed int	int32;		/**< signed 32 bit integer */
typedef signed long	int64;		/**< signed 64 bit integer */


/* data pointer defines */

typedef void*		data;	/**< void pointer data type */
typedef const void*	const_data;	/**< constant void pointer data type */


/* vector types */

/*< 1d vector type */
typedef double vec_t;

/*< 2d vector type */
typedef vec_t vec2_t[ 2 ];

/*< 3d vector type */
typedef vec_t vec3_t[ 3 ];

/*< 4d vector type */
typedef vec_t vec4_t[ 4 ];


/* TRUE/FALSE defines */

#ifndef FALSE
#define FALSE ( 0 )                      /**< false define */
#endif

#ifndef TRUE
#define TRUE (!FALSE)                    /**< true define */
#endif


#endif