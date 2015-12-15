#include "entity.h"
#include "logger.h"

#include <string.h>
#include <glib.h>


static Entity *_entity_list = NULL;
static uint32 _max_entities = 0;
static uint32 _num_entities = 0;
static uint8 _is_init = 0;

uint8 is_ent_sys_init();


uint8 is_ent_sys_init()
{
  return ( _is_init ? TRUE:FALSE );
}


uint8 init_entity_system( uint32 max_entities )
{
  if( is_ent_sys_init() )
  {
    log( WARN, "entity system already initialized" );
    return TRUE;
  }
  
  _entity_list = g_new0( Entity, max_entities );
  if( !_entity_list )
  {
    log( ERROR, "couldn't allocate memory for entity system" );
    return FALSE;
  }
  
  _max_entities = max_entities;
  _is_init = TRUE;
  
  return TRUE;
}


Entity* create_entity()
{
  int i = 0;
  int e = 0;
  
  if( _num_entities + 1 >= _max_entities )
  {
    log( WARN, "the entity list is full" );
    return NULL;
  }
  
  for( ; ( i < _max_entities ) && ( e <= _num_entities ); i++ )
  {
    if( _entity_list[ i ].inuse )
      e++;
    else
    {
      _entity_list[ i ].inuse = TRUE;
      _num_entities++;
      _entity_list[ i ].self = &_entity_list[ i ];
      return &_entity_list[ i ];
    }
  }
  
  log( WARN, "new entity wasn't created" );
  return NULL;
}


void update_entity( Entity *ent )
{
  if( !ent )
    return;
  
  if( ent->think )
    ent->think( ent );
}


void update_all_entities()
{
  int i = 0;
  int e = 0;
  
  for( ; ( i < _max_entities ) && ( e <= _num_entities ); i++ )
  {
    if( _entity_list[ i ].inuse )
    {
      update_entity( &_entity_list[ i ] );
      e++;
    }
  }
}


void draw_entity( Entity *ent )
{
  if( !ent )
    return;
  
  if( !flag_is_set( ent->flags, ENTITY_VISIBLE ) )
    return;
  
  if( ent->draw )
    ent->draw( ent );
  else
    obj_draw( ent->model, ent->position, ent->rotation, ent->scale, ent->color, ent->texture );
}


void draw_all_entities()
{
  int i = 0;
  int e = 0;
  
  for( ; ( i < _max_entities ) && ( e <= _num_entities ); i++ )
  {
    if( _entity_list[ i ].inuse )
    {
      draw_entity( &_entity_list[ i ] );
      e++;
    }
  }
}


void free_entity( Entity *ent )
{
  if( !ent )
    return;
  
  /* free actors */
  /* free body */
  
  if( ent->free )
    ent->free( ent );
  
  memset( ent, 0, sizeof( Entity ) );
  _num_entities--;
}


void free_all_entities()
{
  int i;
  
  for( i = 0; i < _max_entities; i++ )
  {
    free_entity( &_entity_list[ i ] );
  }
  
  _num_entities = 0;
}


void exit_entity_system()
{
  free_all_entities();
  g_free( _entity_list );
  _entity_list = NULL;
  _max_entities = 0;
  _is_init = FALSE;
}


/* eof */