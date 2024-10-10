#ifndef UI_FRAMEWORK_COMPONENT_H_
#define UI_FRAMEWORK_COMPONENT_H_

#include"../common.h"
#include"../observer.h"

class UIComponent : public UIFrameworkObserver
{
    public:
        static const INT32 DEFAULT_FONT_SIZE = 20;
        static const INT32 FONT_SIZE_CAP = 100; //should never be this big

        UIComponent();
        virtual ~UIComponent();
        static SDL_Renderer *getRenderer();
        static void setRenderer(SDL_Renderer *pRenderer);
        SDL_Rect *getRect();
        void setPosition(INT32 x, INT32 y);
        void setSize(INT32 w, INT32 h);        
        SDL_Texture *getTexture();        
        static void setFont(TTF_Font *pFont);
    private:
        ;        
    protected:
        SDL_Texture *pTexture = NULL;
        INT32 x=0, y=0, w=0, h=0;        
        SDL_Rect rect = {0, 0, 0, 0};   //editing the rect has no effect; it only mirrors the real positon and size values

        static TTF_Font *pFont; //font shared across all components        
        static SDL_Renderer *pRenderer; //shared across all child classes
};

#endif // UI_FRAMEWORK_COMPONENT_H_