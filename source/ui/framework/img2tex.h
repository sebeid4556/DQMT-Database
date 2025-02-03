#pragma once
#include"common.h"

SDL_Texture *loadPNG(const CHAR *pPath);
SDL_Surface *loadBCLIM(const CHAR *pPath);
SDL_Texture *img2tex(const CHAR *pPath);
SDL_Texture *img2tex(const CHAR *pPath, SDL_Surface **pSurfaceOut);

SDL_Surface *img2surface(const CHAR *pPath);