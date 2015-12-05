#ifndef __ENTITY__
#define __ENTITY__


#include "types.h"


struct entity_s;
typedef void ( *entity_func )( struct entity_s *self );


enum entity_flags
{
  ENTITY_NONE = 0,
  ENTITY_THINKING = 1,
  ENTITY_VISIBLE = 2,
};


typedef struct entity_s
{
  uint8			inuse;
  
  char			*name;
  uint32		type;
  data			custom_data;
  
  struct entity_s	*self;
  struct entity_s	*owner;
  struct entity_s	*slaves;
  uint32		num_slaves;
  
  /*struct actor_s *actors;*/
  /*struct body_s *body */
  
  uint32		state;
  uint32		flags;
  uint32		think_rate;
  uint32		next_think;
  
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