#include "cmds.h"
#include "logger.h"

#include <glib.h>
#include <glib/glist.h>
#include <stdlib.h>
#include <string.h>


static GSList *_cmd_list_head;
static GSList *_cmd_map_list_head;
static uint8 _is_init = 0;


typedef struct cmd_s
{
  uint8 inuse;
  char *name;
  uint32 event_type;
  int id;
  struct cmd_map_s *map;
  
  command_notify activate;
  data event_params;
}Cmd;


typedef struct cmd_map_s
{
  char *name;
  GSList *cmd_list_head;
  uint8 inuse;
}Cmd_Map;


static Cmd* _find_cmd( char *name );
static Cmd_Map* _find_cmd_map( char *name );
static void _free_cmd( data param );
static void _free_cmd_map( data param );
static void _check_cmd( Cmd *cmd, SDL_Event *event );
static void _check_cmd_map( Cmd_Map *map, SDL_Event *event );


uint8 init_command_system()
{
  if( is_cmd_sys_init() )
  {
    log( WARN, "command system is already initialized" );
    return TRUE;
  }
  
  _cmd_list_head = g_slist_alloc();
  if( !_cmd_list_head )
 {
   log( ERROR, "command list couldn't be allocated" );
   return FALSE;
 }
 
 _cmd_map_list_head = g_slist_alloc();
  if( !_cmd_map_list_head )
 {
   free( _cmd_list_head );
   log( ERROR, "command map list couldn't be allocated" );
   return FALSE;
 }
 
 _cmd_map_list_head->data = NULL;
 _cmd_list_head->data = NULL;
 
 _is_init = TRUE; 
  return TRUE;
}


uint8 is_cmd_sys_init()
{
  return ( _is_init ? TRUE:FALSE );
}


uint8 add_cmd( char *name, char *map, uint32 type, int id, command_notify activate, data params )
{
  Cmd *new;
  Cmd_Map *cmd_map;
  
  if( !is_cmd_sys_init() || !name )
    return FALSE;
  
  new = g_new0( Cmd, 1 );
  if( !new )
  {
    log( ERROR, "couldn't allocate memory for new command" );
    return FALSE;
  }
  
  if( map )
  {
    cmd_map = _find_cmd_map( map );
    if( cmd_map )
    {
      if( !g_slist_append( cmd_map->cmd_list_head, new ) )
      {
	free( new );
	log( ERROR, "couldn't add the new command to command map %s", map );
	return FALSE;
      }
    }
    else
    {
      free( new );
      log( ERROR, "couldn't find command map %s", map );
      return FALSE;
    }
    
    new->map = cmd_map;
  }
  else
  {
    if( !g_slist_append( _cmd_list_head, new ) )
    {
      free( new );
      log( ERROR, "couldn't append the new command to the command list" );
      return FALSE;
    }
  }
  
  new->name = strdup( name );
  new->event_type = type;
  new->id = id;
  new->activate = activate;
  new->event_params = params;
  
  return TRUE;
}


uint8 add_cmd_map( char *name )
{
  Cmd_Map *new;
  
  if( !is_cmd_sys_init() || !name )
    return FALSE;
  
  new = g_new0( Cmd_Map, 1 );
  if( !new )
  {
    log( ERROR, "couldn't allocate memory for new command" );
    return FALSE;
  }
  
  if( !g_slist_append( _cmd_map_list_head, new ) )
  {
    free( new );
    log( ERROR, "couldn't append the new command map to the command map list" );
    return FALSE;
  }
  
  new->cmd_list_head = g_slist_alloc();
  if( !new->cmd_list_head )
 {
   free( new->cmd_list_head );
   log( ERROR, "command list couldn't be allocated for new map %s", name );
   return FALSE;
 }
 
  new->name = strdup( name );
  
  return TRUE;
}


void turn_on_cmd( char *name )
{
  Cmd *tmp;
  
  if( !name )
    return;
  
  tmp = _find_cmd( name );
  if( tmp )
    tmp->inuse = 1;
}


void turn_off_cmd( char *name )
{
  Cmd *tmp;
  
  if( !name )
    return;
  
  tmp = _find_cmd( name );
  if( tmp )
    tmp->inuse = 0;
}


void turn_on_cmd_map( char *name )
{
  Cmd_Map *tmp_map;
  
  if( !name )
    return;
  
  tmp_map = _find_cmd_map( name );
  if( !tmp_map )
    return;
  
  tmp_map->inuse = 1;
}


void turn_off_cmd_map( char *name )
{
  Cmd_Map *tmp_map;
  
  if( !name )
    return;
  
  tmp_map = _find_cmd_map( name );
  if( !tmp_map )
    return;
  
  tmp_map->inuse = 0;
}


void remove_cmd( char *name )
{
  Cmd *tmp;
  
  if( !name )
    return;
  
  tmp = _find_cmd( name );
  if( !tmp )
    return;
  
  _free_cmd( tmp );
}


static void _free_cmd( data param )
{
  Cmd *cmd;
  
  if( !param )
    return;
  
  cmd = ( Cmd* )( param );
  
  if( cmd->map )
    cmd->map->cmd_list_head = g_slist_delete_link( cmd->map->cmd_list_head, g_slist_find( cmd->map->cmd_list_head, cmd ) );
  else
    _cmd_list_head = g_slist_delete_link( _cmd_list_head, g_slist_find( _cmd_list_head, cmd ) );
  
  free( cmd->name );
  free( cmd );
}


void remove_cmd_map( char *name )
{
  Cmd_Map *tmp;
  
  if( !name )
    return;
  
  tmp = _find_cmd_map( name );
  if( !tmp )
    return;
  
  _free_cmd_map( tmp );
}


static void _free_cmd_map( data param )
{
  Cmd_Map *map;
  
  if( !param )
    return;
  
  map = ( Cmd_Map* )( param );
  
  g_slist_free_full( map->cmd_list_head, _free_cmd );
  _cmd_map_list_head = g_slist_delete_link( _cmd_map_list_head, g_slist_find( _cmd_map_list_head, map ) );
  free( map->name );
  free( map );
}


static Cmd* _find_cmd( char *name )
{
  Cmd *tmp;
  GSList *iter;
  
  if( !name )
    return NULL;
  
  iter = _cmd_list_head->next;
  while( iter )
  {
    tmp = ( Cmd* )( iter->data );
    if( !strcmp( tmp->name, name ) )
      return tmp;
    
    iter = iter->next;
  }
    
  return NULL;
}


static Cmd_Map* _find_cmd_map( char *name )
{
  Cmd_Map *tmp;
  GSList *iter;
  
  if( !name )
    return NULL;
  
  iter = _cmd_map_list_head->next;
  while( iter )
  {
    tmp = ( Cmd_Map* )( iter->data );
    if( !strcmp( tmp->name, name ) )
      return tmp;
    
    iter = iter->next;
  }
    
  return NULL;
}


void check_cmds( SDL_Event *event )
{
  Cmd *tmp_cmd;
  Cmd_Map *tmp_map;
  GSList *iter;
  
  if( !event )
    return;
  
  /* check maps */
  iter = _cmd_map_list_head->next; 
  while( iter )
  {
    tmp_map = ( Cmd_Map* )( iter->data );
    if( tmp_map->inuse )
      _check_cmd_map( tmp_map, event );
    
    iter = iter->next;
  }
  
  /* check not maps */
  iter = _cmd_list_head->next; 
  while( iter )
  {
    tmp_cmd = ( Cmd* )( iter->data );
    if( tmp_cmd->inuse )
      _check_cmd( tmp_cmd, event );
    
    iter = iter->next;
  }
}


static void _check_cmd_map( Cmd_Map *map, SDL_Event *event )
{
  Cmd *tmp;
  GSList *iter;
  
  iter = map->cmd_list_head->next; 
  while( iter )
  {
    tmp = ( Cmd* )( iter->data );
    if( tmp->inuse )
      _check_cmd( tmp, event );
    
    iter = iter->next;
  }
}


static void _check_cmd( Cmd *cmd, SDL_Event *event )
{
  if( event->type != cmd->event_type )
    return;
  
  if( event->type == SDL_KEYDOWN || event->type == SDL_KEYUP )
  {
    if( event->key.keysym.sym == cmd->id )
      goto hit;
    else
      goto end;
  }
  else if( event->type == SDL_JOYBUTTONDOWN || event->type == SDL_JOYBUTTONUP )
  {
    if( event->jbutton.button == cmd->id )
      goto hit;
    else
      goto end;
  }
  else if( event->type == SDL_CONTROLLERBUTTONDOWN || event->type == SDL_CONTROLLERBUTTONUP )
  {
    if( event->cbutton.button == cmd->id )
      goto hit;
    else
      goto end;
  }
  else if( event->type == SDL_CONTROLLERAXISMOTION )
  {
    if( event->caxis.axis == cmd->id )
      goto hit;
    else
      goto end;
  }
  else
    goto end;

hit:
  if( cmd->activate )
    cmd->activate( cmd->event_params );
  
end:
  return;
}


void exit_command_system()
{
  _is_init = 0;

  g_slist_free_full( _cmd_list_head, _free_cmd );
  g_slist_free_full( _cmd_map_list_head, _free_cmd_map );
}


/* eof */