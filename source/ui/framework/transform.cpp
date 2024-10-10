#include"transform.h"

/*

All right, so here's the game plan:

-make overloaded constructor for CImage that takes flip dir. as a parameter
-have it do transformations on the surface before it gets converted to a texture
-figure out the math for matrix transformations
-FUCK
*/

void _flipPixelArrayVertical(UINT32 *pPixels)
{
    ;
}

void _flipPixelArrayHorizontal(UINT32 *pPixels)
{
    ;
}

void flipTexture(SDL_Texture *pTexture, INT32 flip)
{
    if(flip == FLIP_HORIZONTAL)
    {
        ;
    }
    else if(flip == FLIP_VERTICAL)
    {
        ;
    }
    else
    {
        error("invalid flip direction", "flipTexture");
    }
}