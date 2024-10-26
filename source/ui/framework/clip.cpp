#include"clip.h"

bool isCoordInside(INT32 x, INT32 y, SDL_Rect bounds)
{
    if(x >= bounds.x && x <= bounds.x+bounds.w)
    {
        if(y >= bounds.y && y <= bounds.y+bounds.h)
        {
            return true;
        }
    }
    return false;
}

bool isRectInside(SDL_Rect object, SDL_Rect bounds)
{
    if(object.x >= bounds.x && object.x <= bounds.x+bounds.w)
    {
        if(object.y >= bounds.y && object.y <= bounds.y+bounds.h)
        {
            return true;
        }
    }
    return false;
}