#ifndef UI_FRAMEWORK_TRANSFORM_H_
#define UI_FRAMEWORK_TRANSFORM_H_

#include"common.h"

enum FLIP_DIRECTIONS {FLIP_HORIZONTAL = 0, FLIP_VERTICAL};

void _flipPixelArrayVertical(UINT32 *pPixels);

void flipTexture(SDL_Texture *pTexture, INT32 flip);

#endif // UI_FRAMEWORK_TRANSFORM_H_