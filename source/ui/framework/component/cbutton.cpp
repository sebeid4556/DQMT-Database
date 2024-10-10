#include"cbutton.h"
#include"../img2tex.h"

//if pPathClicked is set to NULL, the idle image will be shown when clicked
CButton::CButton(const CHAR *pPathIdle, const CHAR *pPathClicked)
{    
    pTextureIdle = img2tex(pPathIdle);

    if(SDL_QueryTexture(pTextureIdle, NULL, NULL, &w, &h))   //get width and height of image
    {
        fatalError(SDL_GetError(), "CButton::CButton");
    }
    this->setSize(w, h);

    if(pPathClicked)
    {
        pTextureClicked = img2tex(pPathClicked);

        if(SDL_QueryTexture(pTextureClicked, NULL, NULL, &wClicked, &hClicked))   //get width and height of image
        {
            fatalError(SDL_GetError(), "CButton::CButton");
        }
    }

    //set default texture to idle texture
    pTexture = pTextureIdle;

    ;
}

CButton::~CButton()
{    
    if(pTextureIdle) SDL_DestroyTexture(pTextureIdle);
    if(pTextureClicked) SDL_DestroyTexture(pTextureClicked);
}

void CButton::update(SDL_Event *pEvent)
{   
    ;
}