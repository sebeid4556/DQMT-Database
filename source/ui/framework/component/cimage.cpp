#include"cimage.h"
#include"../img2tex.h"

CImage::CImage(const CHAR *pPath)
{    
    name = "CImage";

    setImage(pPath);
}

CImage::~CImage()
{
    ;
}

void CImage::setImage(const CHAR *pPath)
{
    if(pSurface) SDL_FreeSurface(pSurface);
    if(pTexture) SDL_DestroyTexture(pTexture);

    pTexture = img2tex(pPath, &pSurface);

    if(SDL_QueryTexture(pTexture, NULL, NULL, &w, &h))   //get width and height of image
    {
        fatalError(SDL_GetError(), "CImage::CImage");
    }
    this->setSize(w, h);
}

void CImage::update(SDL_Event *pEvent)
{   
    printf("CImage::update(): texture = 0x%08X\n", pTexture);
}