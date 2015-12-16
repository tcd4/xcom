#ifndef __UNIT__
#define __UNIT__


#include "entity.h"


#define BASE_HEALTH 4
#define BASE_ACCURACY 50
#define BASE_DODGE 10
#define MAX_ACTIONS 1

#define HUNKER_BONUS 20
#define STEADY_BONUS 20

#define SELECTED_OFFSET 5

enum unit_flags
{
  UNIT_HUNKERED = 0,
  UNIT_STEADIED = 1,
  UNIT_COVERED = 2,
  UNIT_SELECTED = 4,
  UNIT_FINISHED = 8,
  UNIT_DEAD = 32
};

Entity* create_unit( Entity *owner, vec2_t spawn_position, vec4_t color, char *model, char *texture );
void setup_unit_selection();
void take_damage( Entity *unit, int damage );


#endif