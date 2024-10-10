#include"ctext.h"
#include"../../ui_manager.h"
#include<wchar.h>

//static constants
const SDL_Color CText::s_DEFAULT_TEXT_COLOR = {0xFF, 0xFF, 0xFF, 0xFF};
const UINT32 CText::s_DEFAULT_WRAP_LENGTH = UIManager::DEFAULT_WINDOW_WIDTH;
const INT32 CText::s_DEFAULT_FONT_SIZE = UIManager::DEFAULT_FONT_SIZE;

CText::CText(const WCHAR *pWstr)
{
    this->setText(pWstr);
}

CText::CText(const WCHAR *pWstr, INT32 font_size)
{
    setFontSize(font_size);
    this->setText(pWstr);
}

CText::~CText()
{
    ;
}

void CText::update(SDL_Event *pEvent)
{
    ;
}

void CText::setText(const WCHAR *pWstr)
{    
    if(!pWstr)
    {        
        fatalError("parameter is a NULL-pointer", "CText::CText");
    }
    wcsncpy(text, pWstr, CText::s_MAX_TEXT_LENGTH);

    TTF_SetFontSize(UIComponent::pFont, font_size);
    SDL_Surface *pSurface = TTF_RenderUNICODE_Blended_Wrapped(UIComponent::pFont, (const UINT16 *)text, *pTextColor, wrap_length);
    if(!pSurface)
    {        
        fatalError(TTF_GetError(), "CText::setText");
    }

    setSize(pSurface->w, pSurface->h);

    if(pTextTexture)
    {        
        SDL_DestroyTexture(pTextTexture);
    }
    pTextTexture = SDL_CreateTextureFromSurface(UIComponent::getRenderer(), pSurface);
    if(!pTextTexture)
    {    
        fatalError(SDL_GetError(), "CText::setText");
    }

    pTexture = pTextTexture;
}

void CText::setWrapLength(UINT32 wrap_length)
{
    this->wrap_length = wrap_length;
}

void CText::setFontSize(INT32 font_size)
{
    this->font_size = font_size;    
}