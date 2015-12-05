#ifndef __SHADER__
#define __SHADER__


/**
 * @file shader.h
 * 
 * @brief file for creating shaders
 */


#include <GL/glew.h>


GLuint build_shader_program( const char *vertex_shader_file, const char *fragment_shader_file );
GLuint create_shader( GLenum shader_type, const char *shader_file );


#endif