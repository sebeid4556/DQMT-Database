#ifndef UI_FRAMEWORK_TRANSFORM_H_
#define UI_FRAMEWORK_TRANSFORM_H_

#include"common.h"

enum FLIP_DIRECTIONS {FLIP_HORIZONTAL = 1, FLIP_VERTICAL};

void _flipPixelArrayVertical(UINT32 *pPixels);
void _flipPixelArrayHorizontal(UINT32 *pPixels);

void flipSurface(SDL_Surface *pSurface, INT32 flip);

#endif // UI_FRAMEWORK_TRANSFORM_H_