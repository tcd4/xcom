#ifndef __ENEMY__
#define __ENEMY__


/**
 * @file enemy.h
 * 
 * @brief controls enemies
 */

#include "entity.h"


/**
 * @brief creates a new enemy
 * 
 * @param num_units the number of unit the enemy controls
 * @param spawn_positon where to initially spawn the units
 */
Entity* create_enemy( int num_units, vec2_t spawn_position );

/**
 * @brief gets the units under the enemy's control
 * 
 * @return a pointer the enemy's slaves array
 */
Entity* get_enemy_units();

/**
 * @brief frees an enemy entity
 * 
 * @param ent a pointer to the entity
 */
void free_enemy( Entity *ent );


#endif