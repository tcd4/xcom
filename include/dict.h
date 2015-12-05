#ifndef __DICT__
#define __DICT__


/**
 * @file dict.h
 * 
 * @brief a dictionary data type
 */

#include <glib.h>

#include "dict_conversions.h"


typedef struct dict_s
{
  GHashTable	*table;
  uint32	length;
}Dict;


typedef struct entry_s
{
  data value;
  uint8	is_dict;
}Entry;


/**
 * @brief creates a new Dict type
 * 
 * @return a pointer to the new Dict
 */
Dict* create_dict();

/**
 * @brief adds a new key value pair to a Dict
 * 
 * @param dict the Dict to add to
 * @param key the key to add
 * @param value the value to add
 * 
 * @return TRUE on success, FALSE if else
 */
uint8 add_str_dict( Dict *dict, char *key, char* value );

/**
 * @brief adds a new key value pair to a Dict
 * 
 * @param dict the Dict to add to
 * @param key the key to add
 * @param value the value to add
 * 
 * @return TRUE on success, FALSE if else
 */
uint8 add_dict_dict( Dict *dict, char *key, Dict *value );

/**
 * @brief removes a key value pair from a Dict
 * 
 * @param dict the Dict to remove from
 * @param key the key to search for and remove
 */
void remove_dict( Dict *dict, char *key );

/**
 * @brief finds a value in a Dict
 * 
 * @param dict the Dict to search in
 * @param key the key to search for to get the value
 * 
 * @return a pointer to the value in the Dict
 */
data find_dict( Dict *dict, char *key );

/**
 * @brief frees a Dict
 */
void free_dict( data dict );


#endif