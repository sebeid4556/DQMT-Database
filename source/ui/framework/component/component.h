#ifndef UI_FRAMEWORK_COMPONENT_H_
#define UI_FRAMEWORK_COMPONENT_H_

#include<string>
#include<map>

#include"../common.h"
#include"../observer.h"
#include"../subject.h"
#include"../transform.h"
#include"../../event_manager.h"
#include"../clip.h"

class UIComponent : public UIFrameworkObserver
{
    public:
        static const INT32 DEFAULT_FONT_SIZE = 20;
        static const INT32 FONT_SIZE_CAP = 100; //should never be this big

        UIComponent();
        virtual ~UIComponent();
        static SDL_Renderer *getRenderer();
        static void setRenderer(SDL_Renderer *pRenderer);
        static void setEventListeners(std::map<EventManager::EventListenerID, UIFrameworkSubject*>* mEventListeners);
        SDL_Rect *getRect();
        void setPosition(INT32 x, INT32 y);
        void setRelativePosition(UIComponent *pComponent, INT32 x_offset, INT32 y_offset);
        void setSize(INT32 w, INT32 h);        
        SDL_Texture *getTexture();        
        void flip(INT32 flip);
        bool isVisible();
        void setVisible(bool visible);
        void setOpacity(UINT8 opacity);
        static void setFont(TTF_Font *pFont);    
        virtual void onClick();    

        std::string name;
    private:
        ;        
    protected:
        SDL_Surface *pSurface = NULL;   //used to regenerate texture after flipping
        SDL_Texture *pTexture = NULL;   //texture to be rendered
        INT32 x=0, y=0, w=0, h=0;        
        SDL_Rect rect = {0, 0, 0, 0};   //editing the rect has no effect; it only mirrors the real positon and size values

        bool visible = true;

        static TTF_Font *pFont; //font shared across all components        
        static SDL_Renderer *pRenderer; //shared across all derived classes
        static std::map<EventManager::EventListenerID, UIFrameworkSubject*> *mEventListeners;
};

#endif // UI_FRAMEWORK_COMPONENT_H_