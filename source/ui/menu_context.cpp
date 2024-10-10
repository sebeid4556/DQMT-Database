#include"menu_context.h"

MenuContext::MenuContext()
{
    ;
}

//free each component
MenuContext::~MenuContext()
{
    for(UINT32 i = 0;i < vComponents.size();i++)
    {
        if(vComponents.at(i))
        {
            delete vComponents.at(i);
        }
    }
}

void MenuContext::addComponent(UIComponent *pComponent)
{
    vComponents.push_back(pComponent);
}

/*return a copy of the list of components*/
const std::vector<UIComponent *> &MenuContext::getContext()
{
    return vComponents;
}

bool MenuContext::shouldGoToNextMenu()
{
    return gotoNextMenu;
}

UINT8 MenuContext::getNextMenuID()
{
    return nextMenuID;
}

void MenuContext::reset()
{
    gotoNextMenu = false;
    nextMenuID = DEFAULT_MENU_ID;
}