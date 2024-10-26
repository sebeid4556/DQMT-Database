#include"transform.h"

/*

All right, so here's the game plan:

-make overloaded constructor for CImage that takes flip dir. as a parameter
-have it do transformations on the surface before it gets converted to a texture
-figure out the math for matrix transformations
*/

//UINT32 for w and h to prevent integer underflow, because SDL allows negative width and height values
void _flipPixelArrayVertical(UINT32 *pPixels, UINT32 w, UINT32 h)
{
    UINT32 size = w * h * sizeof(UINT32);
    UINT32 temp[w * h] = {0};

    for(UINT32 i = 0;i < h;i++)
    {
        for(UINT32 j = 0;j < w;j++)
        {
            UINT32 index = (i * w) + j;
            UINT32 temp_index = ((h - i - 1) * w) + j;

            temp[temp_index] = pPixels[index];
        }
    }
    memcpy(pPixels, temp, size);
}

void _flipPixelArrayHorizontal(UINT32 *pPixels, UINT32 w, UINT32 h)
{
    UINT32 size = w * h * sizeof(UINT32);
    UINT32 temp[w * h] = {0};

    for(UINT32 i = 0;i < w;i++)
    {
        for(UINT32 j = 0;j < h;j++)
        {
            UINT32 index = (j * w) + i;
            UINT32 temp_index = (j * w) + (w - i - 1);

            temp[temp_index] = pPixels[index];
        }
    }
    memcpy(pPixels, temp, size);
}

void flipSurface(SDL_Surface *pSurface, INT32 flip)
{
    if(pSurface->format->BytesPerPixel != 4)
    {
        error("surface to be flipped must be in 4 bytes per pixel format", "flipSurface");
        return;
    }    
    if(flip & FLIP_HORIZONTAL)
    {        
        _flipPixelArrayHorizontal((UINT32 *)pSurface->pixels, pSurface->w, pSurface->h);
    }
    if(flip & FLIP_VERTICAL)
    {        
        _flipPixelArrayVertical((UINT32 *)pSurface->pixels, pSurface->w, pSurface->h);
    }
}