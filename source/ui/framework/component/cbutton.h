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
    private:
        SDL_Texture *pTextureIdle = NULL;
        SDL_Texture *pTextureClicked = NULL;
        INT32 wClicked=0, hClicked=0;
};

#endif // UI_FRAMEWORK_COMPONENT_CBUTTON_H_