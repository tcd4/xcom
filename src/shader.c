#include "shader.h"
#include "logger.h"

#include <stdio.h>


GLuint build_shader_program( const char *vertex_shader_file, const char *fragment_shader_file )
{
  GLint log_length, status;
  GLuint vertex_shader, fragment_shader, tmp_prog;
  GLchar info_log[ 4096 ];
  
  vertex_shader = create_shader( GL_VERTEX_SHADER, vertex_shader_file );
  fragment_shader = create_shader( GL_FRAGMENT_SHADER, fragment_shader_file );
  tmp_prog = glCreateProgram();
  
  glAttachShader( tmp_prog, vertex_shader );
  glAttachShader( tmp_prog, fragment_shader );
  glLinkProgram( tmp_prog );
  
  glGetProgramiv( tmp_prog, GL_LINK_STATUS, &status );
  if( status == GL_FALSE )
  {
    glGetProgramiv( tmp_prog, GL_INFO_LOG_LENGTH, &log_length );
    glGetProgramInfoLog( tmp_prog, log_length, NULL, info_log );
    log( ERROR, "shader linker failure: %s", info_log );
    return 0;
  }
  
  glDetachShader( tmp_prog, vertex_shader );
  glDetachShader( tmp_prog, fragment_shader );
  
  return tmp_prog;
}


GLuint create_shader( GLenum shader_type, const char *shader_file )
{
  char shader_source[ 4096 ];
  char in;
  FILE *shader_FILE;
  int i = 0;
  GLuint shader;
  GLint status, log_length;
  GLchar info_log[ 4096 ];
  char shader_type_char[ 16 ];
  const char *ss;
  
  shader_FILE = fopen( shader_file, "r" );
  if( !shader_file )
  {
    log( ERROR, "failed to open shader file %s", shader_file );
    return 0;
  }
  
  while( fscanf( shader_FILE, "%c", &in ) > 0 )
  {
    shader_source[ i++ ] = in;
  }
  
  shader_source[ i - 1 ] = '\0';
  fclose( shader_FILE );
  
  shader = glCreateShader( shader_type );
  ss = shader_source;
  glShaderSource( shader, 1, &ss, NULL );
  glCompileShader( shader );
  
  glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
  if( status == GL_FALSE )
  {
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &log_length );
    glGetShaderInfoLog( shader, log_length, NULL, info_log );
    
    switch( shader_type )
    {
      case GL_GEOMETRY_SHADER:
	sprintf( shader_type_char, "geometry" );
	break;
	
      case GL_VERTEX_SHADER:
	sprintf( shader_type_char, "vertex" );
	break;
	
      case GL_FRAGMENT_SHADER:
	sprintf( shader_type_char, "fragment" );
	break;
    }
    
    log( ERROR, "shader compile failer in %s\n shader: %s\n%s", shader_file, shader_type_char, info_log );
    return 0;
  }
  
  return shader;
}


/* eof */