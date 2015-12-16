#ifndef __WEAPON__
#define __WEAPON__


#include "types.h"
#include "entity.h"


enum weapon_enum
{
  SNIPER = 0,
  SHOTGUN,
  ASSAULT,
  SMG
};


typedef struct weapon_s
{
  int accuracy;
  int damage;
  int range;
  int shots;
}Weapon;


uint8 init_weapons( char *weapon_config, Entity *player, Entity *enemy );
void turn_on_weapon_cmds();
void turn_off_weapon_cmds();
void next_target( data param );
void clear_target();
void free_weapons();


#endif