#include"cbutton.h"
#include"../img2tex.h"

//if pPathClicked is set to NULL, the idle image will be shown when clicked
CButton::CButton(const CHAR *pPathIdle, const CHAR *pPathClicked)
{   
    name = "CButton"; 

    pTextureIdle = img2tex(pPathIdle, &pSurfaceIdle);

    if(SDL_QueryTexture(pTextureIdle, NULL, NULL, &w, &h))   //get width and height of image
    {
        LOG_ERROR("Could not query texture");
        fatalError(SDL_GetError(), "CButton::CButton");
    }
    this->setSize(w, h);

    if(pPathClicked)
    {
        pTextureClicked = img2tex(pPathClicked, &pSurfaceClicked);

        if(SDL_QueryTexture(pTextureClicked, NULL, NULL, &wClicked, &hClicked))   //get width and height of image
        {
            LOG_ERROR("Could not query texture");
            fatalError(SDL_GetError(), "CButton::CButton");
        }
    }    

    pSurface = pSurfaceIdle;
    //set default texture to idle texture
    pTexture = pTextureIdle;    

    UIComponent::mEventListeners->at(EventManager::EVENT_LISTENER_MOUSECLICK)->attach(this);
}

CButton::~CButton()
{    
    //Set these to NULL to skip uninitialization in ~UIComponent()
    //because pSurface just points to one of the surfaces freed below
    //same for pTexture
    pSurface = NULL;
    pTexture = NULL;
    
    if(pTextureIdle) SDL_DestroyTexture(pTextureIdle);
    if(pTextureClicked) SDL_DestroyTexture(pTextureClicked);
    
    if(pSurfaceIdle) SDL_FreeSurface(pSurfaceIdle);
    if(pSurfaceClicked) SDL_FreeSurface(pSurfaceClicked); 

    if(pTextSurface) SDL_FreeSurface(pTextSurface);   
}

void CButton::update(SDL_Event *pEvent)
{      
    INT32 x, y;
    SDL_GetMouseState(&x, &y); 
    if(!isCoordInside(x, y, rect) || !isVisible())  //if the button was clicked **AND** the mouse is on the button **AND** is visible
    {
        return;
    }
    
    if(pEvent->type == SDL_MOUSEBUTTONDOWN)
    {
        clicked = true;
        //pSurface = pSurfaceClicked;
        pTexture = pTextureClicked;
    }
    else if(pEvent->type == SDL_MOUSEBUTTONUP)
    {
        clicked = false;
        //pSurface = pSurfaceIdle;
        pTexture = pTextureIdle;
        onClick();
    }
}

void CButton::setText(const WCHAR *pWstr, INT32 font_size, SDL_Color text_color)
{
    if(!pWstr)
    {        
        fatalError("parameter is a NULL-pointer", "CText::CText");
    }    
        
    TTF_SetFontSize(UIComponent::pFont, font_size);

    if(pTextSurface) SDL_FreeSurface(pTextSurface);

    pTextSurface = TTF_RenderUNICODE_Blended_Wrapped(UIComponent::pFont, (const UINT16 *)pWstr, text_color, this->w);
    if(!pTextSurface)
    {        
        fatalError(TTF_GetError(), "CText::setText");
    }
    
    updateTexture();
    
}

void CButton::updateTexture()
{
    if(pTextureIdle) SDL_DestroyTexture(pTextureIdle);
    if(pTextureClicked) SDL_DestroyTexture(pTextureClicked);

    SDL_Surface *pIdleDupe = SDL_DuplicateSurface(pSurfaceIdle);
    SDL_Surface *pClickedDupe = SDL_DuplicateSurface(pSurfaceClicked);

    if(!pIdleDupe) fatalError("failed to duplicate pSurfaceIdle");
    if(!pClickedDupe) fatalError("failed to duplicate pSurfaceClicked");
    
    INT32 text_w = pTextSurface->w;
    INT32 text_h = pTextSurface->h;
    SDL_Rect pos_rect;
    
    pos_rect = {(pIdleDupe->w - text_w) / 2, (pIdleDupe->h - text_h) / 2, 0, 0};
    SDL_BlitSurface(pTextSurface, NULL, pIdleDupe, &pos_rect);
    pos_rect = {(pClickedDupe->w - text_w) / 2, (pClickedDupe->h - text_h) / 2, 0, 0};
    SDL_BlitSurface(pTextSurface, NULL, pClickedDupe, &pos_rect);
    
    pTextureIdle = SDL_CreateTextureFromSurface(UIComponent::getRenderer(), pIdleDupe);
    pTextureClicked = SDL_CreateTextureFromSurface(UIComponent::getRenderer(), pClickedDupe);

    SDL_FreeSurface(pIdleDupe);
    SDL_FreeSurface(pClickedDupe);

    if(clicked) pTexture = pTextureClicked;
    else pTexture = pTextureIdle;
}