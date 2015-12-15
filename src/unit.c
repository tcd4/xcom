#include "unit.h"
#include "grid.h"
#include "game_math.h"
#include "logger.h"


void unit_die();


Entity* create_unit( Entity *owner, vec2_t spawn_position, char *model, char *texture )
{
  Entity *unit;
  vec_t *world_spawn;
  
  unit = create_entity();
  if( !unit )
    return NULL;
  
  unit->type = ENT_UNIT;
  unit->owner = owner;
  unit->model = obj_load( model );
  unit->texture = LoadSprite( texture, -1, -1 );
  unit->flags |= ENTITY_VISIBLE;
  unit->health = 4;
  unit->die = unit_die;
  vec3_set( unit->scale, 1, 1, 1 );
  vec3_set( unit->rotation, 90, 0, 0 );
  
  vec2_copy( spawn_position, unit->grid_position );
  world_spawn = grid_to_world( spawn_position );
  vec3_copy( world_spawn, unit->position );
  unit->position[ ZA ] = 2;
  
  return unit;
}


void unit_die()
{
  
}

/* eof */