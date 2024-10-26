#include"component.h"

SDL_Renderer *UIComponent::pRenderer = NULL;
TTF_Font *UIComponent::pFont = NULL;
std::map<EventManager::EventListenerID, UIFrameworkSubject*>* UIComponent::mEventListeners = NULL;

UIComponent::UIComponent()
{
    ;
}

UIComponent::~UIComponent()
{    
    if(pSurface) SDL_FreeSurface(pSurface);    
    if(pTexture) SDL_DestroyTexture(pTexture);
}

SDL_Renderer *UIComponent::getRenderer()
{    
    return UIComponent::pRenderer;
}

void UIComponent::setRenderer(SDL_Renderer *pRendererNew)
{
    UIComponent::pRenderer = pRendererNew;
}

void UIComponent::setEventListeners(std::map<EventManager::EventListenerID, UIFrameworkSubject*>* mEventListeners)
{
    UIComponent::mEventListeners = mEventListeners;
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

void UIComponent::setRelativePosition(UIComponent *pComponent, INT32 x_offset, INT32 y_offset)
{
    if(!pComponent)
    {
        LOG_ERROR("pComponent is NULL");
        fatalError("failed to set relative position");
    }
    setPosition(pComponent->getRect()->x + x_offset, pComponent->getRect()->y + y_offset);
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

void UIComponent::flip(INT32 flip)
{
    if(!pSurface)
    {
        fatalError("pSurface has not been initialized yet", "UIComponent::flip");
    }
    flipSurface(pSurface, flip);

    SDL_DestroyTexture(pTexture);
    pTexture = SDL_CreateTextureFromSurface(UIComponent::getRenderer(), pSurface);
    if(!pTexture)
    {
        fatalError(SDL_GetError(), "UIComponent::flip");
    }
}

bool UIComponent::isVisible()
{
    return visible;
}

void UIComponent::setVisible(bool visible)
{
    this->visible = visible;
}

void UIComponent::setOpacity(UINT8 opacity)
{
    if(SDL_SetTextureAlphaMod(pTexture, opacity) == -1)
    {
        LOG_ERROR("could not set alpha value of texture");
        fatalError("alpha mod not supported");
    }
}

void UIComponent::setFont(TTF_Font *pFont)
{
    UIComponent::pFont = pFont;
}

void UIComponent::onClick()
{
    ;
}