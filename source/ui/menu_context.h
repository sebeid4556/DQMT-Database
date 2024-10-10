#ifndef UI_MENU_CONTEXT_H_
#define UI_MENU_CONTEXT_H_

#include"framework/common.h"
#include"framework/component/all.h"
#include"menu/common.h"

class MenuContext
{
    public:
        MenuContext();
        ~MenuContext();        
        const std::vector<UIComponent *> &getContext();
        bool shouldGoToNextMenu();
        UINT8 getNextMenuID();
        void reset();
    protected:
        bool gotoNextMenu = false;
        UINT8 nextMenuID = DEFAULT_MENU_ID;

        std::vector<UIComponent *> vComponents;

        void addComponent(UIComponent *pComponent);
};

#endif // UI_MENU_CONTEXT_H_