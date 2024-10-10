#ifndef UI_FRAMEWORK_CIMAGE_H_
#define UI_FRAMEWORK_CIMAGE_H_

#include"../common.h"
#include"component.h"

class CImage : public UIComponent
{
    public:
        CImage(const CHAR *pPath);
        virtual ~CImage();
        void update(SDL_Event *pEvent) override;        
    private:        
};

#endif // UI_FRAMEWORK_CIMAGE_H_