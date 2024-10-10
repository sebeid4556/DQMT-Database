#include"cimage.h"
#include"../img2tex.h"

CImage::CImage(const CHAR *pPath)
{    
    pTexture = img2tex(pPath);

    if(SDL_QueryTexture(pTexture, NULL, NULL, &w, &h))   //get width and height of image
    {
        fatalError(SDL_GetError(), "CImage::CImage");
    }
    this->setSize(w, h);    
}

CImage::~CImage()
{
    if(pTexture) SDL_DestroyTexture(pTexture);
}

void CImage::update(SDL_Event *pEvent)
{   
    printf("CImage::update(): texture = 0x%08X\n", (UINT32)pTexture);
}