#ifndef __PLAYER__
#define __PLAYER__


#include "entity.h" 


Entity* create_player( int num_units, vec2_t spawn_position );
void start_player_turn( Entity *player );
void do_unit_action( Entity *unit, int action );
void next_unit( data param );
void turn_on_player_cmds();
void turn_off_player_cmds();
void exit_attack_cmds( data param );
void free_player( Entity *ent );


#endif