#include "enemy.h"
#include "unit.h"


static Entity *_enemy = NULL;


Entity* create_enemy( int num_units, vec2_t spawn_position )
{
  Entity *enemy;
  int i;
  
  enemy = create_entity();
  if( !enemy )
    return NULL;
  
  _enemy = enemy;
  enemy->type = ENT_ENEMY;
  enemy->flags = ENTITY_NONE;
  enemy->num_slaves = MAX_UNITS;

  i = 0;
  enemy->slaves[ i ] = create_unit( enemy, spawn_position, "../models/cube.obj", "../models/cube_text.png" );
  
  /* set up units */
  
  enemy->free = free_enemy;
  
  return enemy;
}


Entity* get_enemy_units()
{
  return *_enemy->slaves;
}


void free_enemy( Entity *ent )
{
  int i;
  
  for( i = 0; i < ent->num_slaves; i++ )
  {
    free_entity( ent->slaves[ i ] );
    ent->slaves[ i ] = NULL;
  }
}


/* eof */