#ifndef __DEF_PARSER__
#define __DEF_PARSER__


/**
 * @file parser.h
 * 
 * @brief functions for parsing files
 */


#include "dict.h"


/**
 * @brief parses a file
 * 
 * @param filename the file to parse
 * 
 * @return a Dict containing the parsed values or NULL on error
 */
Dict* parse( char *filename );


#endif