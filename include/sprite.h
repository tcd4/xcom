#ifndef __SPRITE__
#define __SPRITE__

#include "graphics3d.h"
#include "types.h"
#include <SDL.h>

#define MAXSPRITEFILENAME 512

typedef struct Sprite_T
{
    SDL_Surface *image;               /**<pointer to the actual image in memory*/
    GLuint texture;
    char  filename[MAXSPRITEFILENAME]; /**<the name of the file, keep them short*/
    int   w, h;                         /**<the width and height of the frames of the sprites, not the file itself*/
    int   framesperline;                /**<default is 16*/
    int   color1,color2,color3;         /**<if the file was palette swapped these are the colors that were changed*/
    Uint8 used;                         /**<used by the maintanenc functions to keep track of how many times a single sprite is being used*/
}Sprite;


/**
 * @brief initializes internal sprite system
 */
void InitSpriteList();

/**
 * @brief Decriments the reference count for the sprite passed.
 * frees the sprite when no longer used
 * 
 * @param img the sprite to free
 */
void FreeSprite(Sprite *img);


Sprite *LoadSprite(char *filename,int sizex, int sizey);

/**
 * @brief draws a sprite to a surface
 * 
 * @param sprite a pointer to the sprite to draw
 * @param position the position to draw the sprite at
 * @param scale the scale to draw the sprite
 * @param rotation the rotation to draw the sprite
 * @param frame the sprite frame to draw
 */
void draw_sprite( Sprite *sprite, vec2_t position, vec2_t scale, vec2_t rotation, uint32 frame );

/**
 * @brief clears all loaded sprites in system.  Called before program exit
 */
void CloseSprites();



#endif
