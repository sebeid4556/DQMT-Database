#ifndef UI_FRAMEWORK_COMPONENT_CBUTTON_H_
#define UI_FRAMEWORK_COMPONENT_CBUTTON_H_

#include"../common.h"
#include"component.h"

class CButton : public UIComponent
{
    public:
        CButton(const CHAR *pPathIdle, const CHAR *pPathClicked);
        virtual ~CButton();        
        void update(SDL_Event *pEvent) override;
        void setText(const WCHAR *pWstr, INT32 font_size, SDL_Color text_color);
    private:
        SDL_Texture *pTextureIdle = NULL;
        SDL_Texture *pTextureClicked = NULL;
        SDL_Surface *pSurfaceIdle = NULL;
        SDL_Surface *pSurfaceClicked = NULL;
        SDL_Surface *pTextSurface = NULL;        
        INT32 wClicked=0, hClicked=0;

        bool clicked = false;              

        void updateTexture();
};

#endif // UI_FRAMEWORK_COMPONENT_CBUTTON_H_