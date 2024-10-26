#include"common.h"

bool checkExtention(const CHAR *pPath, const CHAR *pExtension);

SDL_Texture *loadPNG(const CHAR *pPath);
SDL_Surface *loadBCLIM(const CHAR *pPath);
SDL_Texture *img2tex(const CHAR *pPath);
SDL_Texture *img2tex(const CHAR *pPath, SDL_Surface **pSurfaceOut);

SDL_Surface *img2surface(const CHAR *pPath);