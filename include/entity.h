#ifndef __ENTITY__
#define __ENTITY__


#include "types.h"
#include "obj.h"
#include "sprite.h"


#define MAX_UNITS 5

struct entity_s;
typedef void ( *entity_func )( struct entity_s *self );


enum entity_flags
{
  ENTITY_NONE = 0,
  ENTITY_THINKING = 1,
  ENTITY_VISIBLE = 2,
};

enum ent_types
{
  ENT_NONE = 0,
  ENT_GRID,
  ENT_PLAYER,
  ENT_ENEMY,
  ENT_UNIT,
  ENT_COVER
};


typedef struct entity_s
{
  uint8			inuse;
  
  char			name[ 20 ];
  uint32		type;
  data			custom_data;
  
  struct entity_s	*self;
  struct entity_s	*owner;
  struct entity_s	*slaves[ MAX_UNITS ];
  uint32		num_slaves;
  
  vec3_t 		position;
  vec2_t		grid_position;
  vec3_t		rotation;
  vec3_t		scale;
  vec4_t		color;
  
  Obj			*model;
  Sprite		*texture;
  
  /*struct actor_s *actors;*/
  /*struct body_s *body */
  
  uint32		state;
  uint32		flags;
  uint32		think_rate;
  uint32		next_think;
  
  int 			health;
  
  entity_func		think;
  entity_func		draw;
  entity_func		move;
  entity_func		touch;
  entity_func		die;
  entity_func		free;
}Entity;


uint8 init_entity_system( uint32 max_entities );
Entity* create_entity();

void update_entity( Entity *ent );
void update_all_entities();

void draw_entity( Entity *ent );
void draw_all_entities();

void free_entity( Entity *ent );
void free_all_entities();
void exit_entity_system();


#endif