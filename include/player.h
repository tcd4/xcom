#ifndef __PLAYER__
#define __PLAYER__


#include "entity.h" 


Entity* create_player( int num_units, vec2_t spawn_position );
void turn_on_player_cmds();
void turn_off_player_cmds();
void free_player( Entity *ent );


#endif