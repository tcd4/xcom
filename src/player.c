#include "player.h"
#include "game.h"
#include "cmds.h"
#include "unit.h"
#include "logger.h"


void next_unit( data param );
void move_unit( data param );
void pick_weapon( data param );
void hunker_unit( data param );
void steady_unit( data param );

void exit_attack_cmds( data param );
void end_turn();

static uint16 current_unit;


Entity* create_player( int num_units, vec2_t spawn_position )
{
  Entity *player;
  int i;
  
  player = create_entity();
  if( !player )
    return NULL;
  
  player->type = ENT_PLAYER;
  player->flags = ENTITY_NONE;
  player->num_slaves = MAX_UNITS;
  current_unit = 0;
  
  if( !add_cmd_map( "unit_controls" ) )
    return FALSE;
  
  if( !add_cmd( "next_unit", "unit_controls", SDL_KEYDOWN, SDLK_TAB, next_unit, player ) )
    return FALSE;
  
  if( !add_cmd( "pick_weapon", "unit_controls", SDL_KEYDOWN, SDLK_1, pick_weapon, player ) )
    return FALSE;
  
  if( !add_cmd( "move_unit", "unit_controls", SDL_KEYDOWN, SDLK_2, move_unit, player ) )
    return FALSE;
  
  if( !add_cmd( "hunker_unit", "unit_controls", SDL_KEYDOWN, SDLK_3, hunker_unit, player ) )
    return FALSE;
  
  if( !add_cmd( "steady_unit", "unit_controls", SDL_KEYDOWN, SDLK_4, steady_unit, player ) )
    return FALSE;
  
  if( !add_cmd( "exit_attack_cmds", NULL, SDL_KEYDOWN, SDLK_ESCAPE, exit_attack_cmds, NULL ) )
    return FALSE;
  
  if( !add_cmd( "end_player_turn", NULL, SDL_KEYDOWN, SDLK_RETURN, end_turn, NULL ) )
    return FALSE;
  
  i = 0;
  player->slaves[ i ] = create_unit( player, spawn_position, "../models/monkey.obj", "../models/monkey.png" );
  
  /* set up units */
  
  player->free = free_player;
  
  return player;
}


void turn_on_player_cmds()
{
  turn_on_cmd_map( "unit_controls" );
  turn_on_cmd( "end_player_turn" );
}


void turn_off_player_cmds()
{
  turn_off_cmd_map( "unit_controls" );
  turn_off_cmd( "end_player_turn" );
}


void next_unit( data param )
{
  Entity *player;
  
  player = ( Entity* )( param );
  current_unit = ( current_unit + 1 ) % player->num_slaves;
  /* check if unit is dead */
}


void move_unit( data param )
{
  Entity *player;
  
  player = ( Entity* )( param );
}


void pick_weapon( data param )
{
  Entity *player;
  
  player = ( Entity* )( param );
  turn_on_cmd( "exit_attack_cmds" );
  /* turn on weapon cmds */
}


void hunker_unit( data param )
{
  Entity *player;
  
  player = ( Entity* )( param );
}


void steady_unit( data param )
{
  Entity *player;
  
  player = ( Entity* )( param );
}


void exit_attack_cmds( data param )
{
  turn_off_cmd( "exit_attack_cmds" );
  /* turn off weapon cmds */
}


void end_turn( data param )
{
  game_end_turn();
}


void free_player( Entity *ent )
{
  int i;
  
  for( i = 0; i < ent->num_slaves; i++ )
  {
    free_entity( ent->slaves[ i ] );
    ent->slaves[ i ] = NULL;
  }
}


/* eof */