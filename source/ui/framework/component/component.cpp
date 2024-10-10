#include"component.h"

SDL_Renderer *UIComponent::pRenderer = NULL;
TTF_Font *UIComponent::pFont = NULL;

UIComponent::UIComponent()
{
    ;
}

UIComponent::~UIComponent()
{
    ;
}

SDL_Renderer *UIComponent::getRenderer()
{    
    return UIComponent::pRenderer;
}

void UIComponent::setRenderer(SDL_Renderer *pRendererNew)
{
    UIComponent::pRenderer = pRendererNew;
}

SDL_Rect *UIComponent::getRect()
{
    return &rect;
}

void UIComponent::setPosition(INT32 x, INT32 y)
{
    this->x = x;
    this->y = y;

    rect.x = x;
    rect.y = y;
}

void UIComponent::setSize(INT32 w, INT32 h)
{
    this->w = w;
    this->h = h;

    rect.w = w;
    rect.h = h;
}

SDL_Texture *UIComponent::getTexture()
{
    if(!pTexture) fatalError("texture has not yet been initialiazed", "UIComponent::getTexture");
    return pTexture;
}

void UIComponent::setFont(TTF_Font *pFont)
{
    UIComponent::pFont = pFont;
}