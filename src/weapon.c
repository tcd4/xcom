#include "weapon.h"
#include "cmds.h"
#include "unit.h"
#include "player.h"
#include "parser.h"
#include "logger.h"
#include "enemy.h"
#include "game_math.h"

#include <glib.h>


void fire_sniper( data param );
void fire_shotgun( data param );
void fire_assault( data param );
void fire_smg( data param );
void fire( Entity *shooter, int weapon );
void create_weapon( char *weapon_config, int weapon );

Entity		*_player;
Entity 		*_enemy;
static Weapon	*_weapon_list;
static int	_target = 0;


uint8 init_weapons( char *weapon_config, Entity *player, Entity *enemy )
{
  Dict *config;
  
  _weapon_list = g_new0( Weapon, 4 );
  if( !_weapon_list )
    return FALSE;
  
  config = parse( weapon_config );
  create_weapon( find_dict( config, "sniper" ), 0 );
  create_weapon( find_dict( config, "shotgun" ), 1 );
  create_weapon( find_dict( config, "assault" ), 2 );
  create_weapon( find_dict( config, "smg" ), 3 );
  
  
  if( !add_cmd( "next_target", NULL, SDL_KEYDOWN, SDLK_TAB, next_target, player ) )
    return FALSE;
  
  if( !add_cmd( "fire_sniper", NULL, SDL_KEYDOWN, SDLK_5, fire_sniper, player ) )
    return FALSE;
  
  if( !add_cmd( "fire_shotgun", NULL, SDL_KEYDOWN, SDLK_6, fire_shotgun, player ) )
    return FALSE;
  
  if( !add_cmd( "fire_assault", NULL, SDL_KEYDOWN, SDLK_7, fire_assault, player ) )
    return FALSE;
  
  if( !add_cmd( "fire_smg", NULL, SDL_KEYDOWN, SDLK_8, fire_smg, player ) )
  
  _enemy = g_new0( Entity, 1 );
  _enemy = enemy;
  
  _player = g_new0( Entity, 1 );
  _player = _player;
  
  turn_off_weapon_cmds();
  
  return TRUE;
}


void create_weapon( char *weapon_config, int weapon )
{
  Dict *config;
  
  config = parse( weapon_config );
  str_int( find_dict( config, "accuracy" ), &_weapon_list[ weapon ].accuracy );
  str_int( find_dict( config, "damage" ), &_weapon_list[ weapon ].damage );
  str_int( find_dict( config, "range" ), &_weapon_list[ weapon ].range );
  str_int( find_dict( config, "shots" ), &_weapon_list[ weapon ].shots );
}


void turn_on_weapon_cmds()
{
  turn_on_cmd( "next_target" );
  turn_on_cmd( "fire_sniper" );
  turn_on_cmd( "fire_shotgun" );
  turn_on_cmd( "fire_assault" );
  turn_on_cmd( "fire_smg" );
}


void turn_off_weapon_cmds()
{
  turn_off_cmd( "next_target" );
  turn_off_cmd( "fire_sniper" );
  turn_off_cmd( "fire_shotgun" );
  turn_off_cmd( "fire_assault" );
  turn_off_cmd( "fire_smg" );
}


void next_target( data param )
{
  if( _enemy->living_units <= 0 )
    return;
  
  if( _enemy->slaves[ _target ] )
    _enemy->slaves[ _target ]->unit_flags &= ~UNIT_SELECTED;
  
  _target = ( _target + 1 ) % MAX_UNITS;
  
  if( ( !_enemy->slaves[ _target ] ) || ( _enemy->slaves[ _target ]->unit_flags & UNIT_DEAD ) || ( _enemy->slaves[ _target ]->flags & UNIT_FINISHED ) )
  {
    next_target( _enemy );
    return;
  }
  
  _enemy->slaves[ _target ]->unit_flags |= UNIT_SELECTED;
}


void clear_target()
{
  _enemy->slaves[ _target ]->unit_flags &= ~UNIT_SELECTED;
}


void fire_sniper( data param )
{
  Entity *shooter;
  
  shooter = ( Entity* )( param );
  if( !( shooter->slaves[ shooter->cur_unit ]->unit_flags & UNIT_FINISHED ) )
    fire( shooter, SNIPER );
}


void fire_shotgun( data param )
{
  Entity *shooter;
  
  shooter = ( Entity* )( param );
  if( !( shooter->slaves[ shooter->cur_unit ]->unit_flags & UNIT_FINISHED ) )
    fire( shooter, SHOTGUN );
}


void fire_assault( data param )
{
  Entity *shooter;
  
  shooter = ( Entity* )( param );
  if( !( shooter->slaves[ shooter->cur_unit ]->unit_flags & UNIT_FINISHED ) )
    fire( shooter, ASSAULT );
}


void fire_smg( data param )
{
  Entity *shooter;
  
  shooter = ( Entity* )( param );
  if( !( shooter->slaves[ shooter->cur_unit ]->unit_flags & UNIT_FINISHED ) )
    fire( shooter, SMG );
}


void fire( Entity *shooter, int weapon )
{
  int dodge, accuracy;
  int i;
  vec2_t distance_v;
  double distance;
  
  vec2_subtract( shooter->slaves[ shooter->cur_unit ]->grid_position, _enemy->slaves[ _target ]->grid_position, distance_v );
  distance = vec2_get_magnitude( distance_v );
  if( distance > _weapon_list[ weapon ].range )
  {
    /* display out of range */
    return;
  }
  
  dodge = _enemy->slaves[ _target ]->dodge;
  if( _enemy->slaves[ _target ]->unit_flags & UNIT_HUNKERED )
    dodge += HUNKER_BONUS;
  
  accuracy = shooter->slaves[ shooter->cur_unit ]->accuracy + _weapon_list[ weapon ].accuracy - dodge;
  if( shooter->slaves[ shooter->cur_unit ]->unit_flags & UNIT_STEADIED )
    accuracy += STEADY_BONUS;
  
  for( i = 0; i < _weapon_list[ weapon ].shots; i ++ )
  {
    if( irandom() < accuracy )
    {
      take_damage( _enemy->slaves[ _target ], 3 );
      log( TRACE, "Hit" );
    }
    else
    {
      log( TRACE, "miss" );
      /* missed */
    }
  }
  
  _enemy->slaves[ _target ]->unit_flags &= ~UNIT_SELECTED;
  shooter->slaves[ shooter->cur_unit ]->unit_flags |= UNIT_FINISHED;
  next_unit( shooter );
  exit_attack_cmds( NULL );
}


void free_weapons()
{
  
}


/* eof */