#include "unit.h"
#include "grid.h"
#include "game_math.h"
#include "logger.h"
#include "game.h"


void unit_die();
void unit_draw();

static Obj	*_selected;
static Sprite	*_selected_texture;


void setup_unit_selection()
{
  _selected = obj_load( "../models/selected.obj" );
  _selected_texture = LoadSprite( "../models/selected.png", -1, -1 );
}

Entity* create_unit( Entity *owner, vec2_t spawn_position, vec4_t color, char *model, char *texture )
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
  
  vec4_copy( color, unit->color );
  vec3_set( unit->scale, 1, 1, 1 );
  vec3_set( unit->rotation, 90, 0, 0 );
  
  vec2_copy( spawn_position, unit->grid_position );
  world_spawn = grid_to_world( spawn_position );
  vec3_copy( world_spawn, unit->position );
  unit->position[ ZA ] = 2;
  
  unit->health = BASE_HEALTH;
  unit->dodge = BASE_DODGE;
  unit->accuracy = BASE_ACCURACY;
  
  unit->die = unit_die;
  unit->draw = unit_draw;
  
  return unit;
}


void unit_draw( Entity *unit )
{
  vec3_t selected_position;
  
  obj_draw( unit->model, unit->position, unit->rotation, unit->scale, unit->color, unit->texture );
  
  if( unit->unit_flags & UNIT_SELECTED )
  {
    vec3_copy( unit->position, selected_position );
    selected_position[ ZA ] += SELECTED_OFFSET;
    obj_draw( _selected, selected_position, unit->rotation, unit->scale, unit->color, _selected_texture );
  }
}


void take_damage( Entity *unit, int damage )
{
  unit->health -= damage;
  if( unit->health <= 0 )
    unit->die( unit );
}


void unit_die( Entity *unit )
{
  unit->unit_flags |= UNIT_DEAD;
  unit->flags &= ~ENTITY_VISIBLE;
  unit->owner->living_units--;
  if( unit->owner->living_units <= 0 )
    game_set_winner( unit->owner );
}

/* eof */