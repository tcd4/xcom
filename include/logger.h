#ifndef __LOGGER__
#define __LOGGER__


#include "types.h"


/**
 * @file logger.h
 * 
 * @brief contains functions for logging
 */


/**< the various logging levels */
typedef enum 
{
  NONE = 0,
  FATAL,
  ERROR,
  WARN,
  TRACE,
  INFO,
  ALL
}Log_Level;

/**< logging flags */
enum
{
  LOG_NONE = 0,
  LOG_INITIALIZED = 1,
  LOG_LOGGING = 2,
  LOG_THREADED = 4
};


/**
 * @brief initializes the logger
 * 
 * @param log_file the file to log to
 * 
 * @return TRUE on success, FALSE if else
 */
uint8 init_logger( char *log_file );

/**
 * @brief checks if the logger is initialized
 * 
 * @return TRUE if it is, FALSE if else
 */
uint8 logger_is_init();

/**
 * @brief checks if the logger is threaded
 * 
 * @return TRUE if it is, FALSE if else
 */
uint8 logger_is_threaded();

/**
 * @brief checks if the logger is logging
 * 
 * @return TRUE if it is, FALSE if else
 */
uint8 logger_is_logging();

/**
 * @brief enables multithreading for the logger
 * 
 * @return TRUE on success, FALSE if else
 */
uint8 enable_logger_threading();

/**
 * @brief converts a Log_Level to a string
 * 
 * @param lvl the Log_Level to convert
 * 
 * @return a string representation of lvl or NULL on error
 */
char* log_level_to_str( Log_Level lvl );

/**
 * @brief define for easier logging
 * 
 * @param lvl the Log_Level to write to
 * @param ... the message including its additional arguments
 */
#define log( lvl, ... ) log_msg( __FILE__, __LINE__, lvl, __VA_ARGS__ )

/**
 * @brief logs a message
 * 
 * @param file the file name that's writing the message
 * @param line the line number in the file
 * @param lvl the Log_Level to write to
 * @param msg the message
 * @param ... additional arguments for msg
 */
void log_msg( char *file, int line, Log_Level lvl, char *msg, ... );

/**
 * @brief stops logging
 */
void stop_logging();

/**
 * @brief turns off the logger
 */
void exit_logging();


#endif