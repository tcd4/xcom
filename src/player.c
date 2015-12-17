#include "player.h"
#include "game.h"
#include "cmds.h"
#include "unit.h"
#include "logger.h"
#include "game_math.h"
#include "weapon.h"


void move_unit( data param );
void pick_weapon( data param );
void hunker_unit( data param );
void steady_unit( data param );

void end_turn();


Entity* create_player( int num_units, vec2_t spawn_position )
{
  Entity *player;
  int i;
  vec4_t color;
  
  player = create_entity();
  if( !player )
    return NULL;
  
  player->type = ENT_PLAYER;
  player->flags = ENTITY_NONE;
  player->num_slaves = MAX_UNITS;
  
  if( !add_cmd( "next_unit", NULL, SDL_KEYDOWN, SDLK_TAB, next_unit, player ) )
    return FALSE;
  
  if( !add_cmd( "pick_weapon", NULL, SDL_KEYUP, SDLK_1, pick_weapon, player ) )
    return FALSE;
  
  if( !add_cmd( "move_unit", NULL, SDL_KEYDOWN, SDLK_2, move_unit, player ) )
    return FALSE;
  
  if( !add_cmd( "hunker_unit", NULL, SDL_KEYDOWN, SDLK_3, hunker_unit, player ) )
    return FALSE;
  
  if( !add_cmd( "steady_unit", NULL, SDL_KEYDOWN, SDLK_4, steady_unit, player ) )
    return FALSE;
  
  if( !add_cmd( "exit_attack_cmds", NULL, SDL_KEYDOWN, SDLK_ESCAPE, exit_attack_cmds, NULL ) )
    return FALSE;
  
  if( !add_cmd( "end_player_turn", NULL, SDL_KEYDOWN, SDLK_RETURN, end_turn, NULL ) )
    return FALSE;
  
  vec4_set( color, 0, 0, 1, 1 );
  for( i = 0; i < MAX_UNITS; i++ )
  {
    player->slaves[ i ] = create_unit( player, spawn_position, color, "../models/monkey.obj", "../models/monkey.png" );
    spawn_position[ YA ]++;
  }
  player->slaves[ 0 ]->unit_flags |= UNIT_SELECTED;
  player->living_units = MAX_UNITS;
  
  player->free = free_player;
  
  return player;
}


void turn_on_player_cmds()
{
  turn_on_cmd( "next_unit" );
  turn_on_cmd( "pick_weapon" );
  turn_on_cmd( "move_unit" );
  turn_on_cmd( "hunker_unit" );
  turn_on_cmd( "steady_unit" );
  turn_on_cmd( "end_player_turn" );
}


void turn_off_player_cmds()
{
  turn_off_cmd( "next_unit" );
  turn_off_cmd( "pick_weapon" );
  turn_off_cmd( "move_unit" );
  turn_off_cmd( "hunker_unit" );
  turn_off_cmd( "steady_unit" );
  turn_off_cmd( "end_player_turn" );
}


void next_unit( data param )
{
  Entity *player;
  
  player = ( Entity* )( param );
  
  if( player->active_units <= 0 )
  {
    end_turn();
    return;
  }
  
  if( player->slaves[ player->cur_unit ] )
    player->slaves[ player->cur_unit ]->unit_flags &= ~UNIT_SELECTED;
  
  player->cur_unit = ( player->cur_unit + 1 ) % MAX_UNITS;
  
  if( ( !player->slaves[ player->cur_unit ] ) || ( player->slaves[ player->cur_unit ]->unit_flags & UNIT_DEAD ) || ( player->slaves[ player->cur_unit ]->unit_flags & UNIT_FINISHED ) )
  {
    next_unit( player );
    return;
  }
  
  player->slaves[ player->cur_unit ]->unit_flags |= UNIT_SELECTED;
}


void move_unit( data param )
{
  Entity *player;
  
  player = ( Entity* )( param );
  
  do_unit_action( player->slaves[ player->cur_unit ], UNIT_NONE );
}


void pick_weapon( data param )
{
  turn_off_player_cmds();
  turn_on_cmd( "exit_attack_cmds" );
  turn_on_weapon_cmds();
  next_target( NULL );
}


void hunker_unit( data param )
{
  Entity *player;
  
  player = ( Entity* )( param );
  
  if( player->slaves[ player->cur_unit ]->unit_flags & UNIT_HUNKERED )
    return;
  
  do_unit_action( player->slaves[ player->cur_unit ], UNIT_HUNKERED );
  log( TRACE, "unit hunkered" );
}


void steady_unit( data param )
{
  Entity *player;
  
  player = ( Entity* )( param );
  
  if( player->slaves[ player->cur_unit ]->unit_flags & UNIT_STEADIED )
    return;
  
  do_unit_action( player->slaves[ player->cur_unit ], UNIT_STEADIED );
  log( TRACE, "unit steadied" );
}


void do_unit_action( Entity *unit, int action )
{
  if( !unit )
    return;
  
  unit->unit_flags |= action;
  unit->unit_flags |= UNIT_FINISHED;
  unit->owner->active_units--;
  next_unit( unit->owner );
}


void exit_attack_cmds( data param )
{
  turn_off_cmd( "exit_attack_cmds" );
  turn_on_player_cmds();
  turn_off_weapon_cmds();
  clear_target();
}


void start_player_turn( Entity *player )
{
  int i;
  
  turn_on_player_cmds();
  
  player->active_units = player->living_units;
  
  for( i = 0; i < MAX_UNITS; i++ )
  {
    if( player->slaves[ i ] )
    {
      player->slaves[ player->cur_unit ]->unit_flags &= ~UNIT_FINISHED;
      
      if( player->slaves[ i ]->unit_flags & UNIT_HUNKERED )
      {
	player->slaves[ player->cur_unit ]->unit_flags &= ~UNIT_HUNKERED;
	player->slaves[ player->cur_unit ]->dodge -= HUNKER_BONUS;
      }
    }
  }
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