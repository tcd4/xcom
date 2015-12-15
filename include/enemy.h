#ifndef __ENEMY__
#define __ENEMY__


#include "entity.h"

Entity* create_enemy( int num_units, vec2_t spawn_position );
Entity* get_enemy_units();
void free_enemy( Entity *ent );


#endif