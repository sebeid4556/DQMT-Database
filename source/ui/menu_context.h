#ifndef UI_MENU_CONTEXT_H_
#define UI_MENU_CONTEXT_H_

#include"framework/common.h"
#include"framework/component/all.h"
#include"framework/callback.h"
#include"menu/common.h"

class MenuContext
{
    public:
        MenuContext();
        ~MenuContext();        
        const std::vector<UIComponent *> &getContext();        
        menu::MenuID getNextMenuID();
        void addComponent(UIComponent *pComponent);
        void setNextMenuID(menu::MenuID id);
        void reset();
    protected:        
        menu::MenuID nextMenuID = menu::ID_MENU_NONE;

        std::vector<UIComponent *> vComponents;        
};

#endif // UI_MENU_CONTEXT_H_