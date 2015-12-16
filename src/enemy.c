#include "enemy.h"
#include "unit.h"
#include "game_math.h"


static Entity *_enemy = NULL;


Entity* create_enemy( int num_units, vec2_t spawn_position )
{
  Entity *enemy;
  int i;
  vec4_t color;
  
  enemy = create_entity();
  if( !enemy )
    return NULL;
  
  _enemy = enemy;
  enemy->type = ENT_ENEMY;
  enemy->flags = ENTITY_NONE;
  enemy->num_slaves = MAX_UNITS;

  
  vec4_set( color, 1, 0, 0, 1 );
  for( i = 0; i < MAX_UNITS; i++ )
  {
    enemy->slaves[ i ] = create_unit( enemy, spawn_position, color, "../models/monkey.obj", "../models/monkey.png" );
    spawn_position[ YA ]++;
  }
  enemy->living_units = MAX_UNITS;
  enemy->free = free_enemy;
  
  return enemy;
}


Entity* get_enemy_units()
{
  return _enemy->slaves[ 0 ];
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