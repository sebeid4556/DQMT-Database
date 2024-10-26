#include"menu_context.h"

MenuContext::MenuContext()
{
    ;
}

//free each component
MenuContext::~MenuContext()
{
    LOG_ERROR("are ya causing the bug, buster?");
    std::cout << "vComponents.size() = " << vComponents.size() << std::endl;
    /*for(UINT32 i = 0;i < vComponents.size();i++)
    {
        if(vComponents.at(i))
        {
            delete vComponents.at(i);
        }
    }*/
    int n = 0;
    for(auto const& component : vComponents)
    {        
        std::cout << "component " << n++ << "\t(" << component->name << ")" <<  std::endl;
        delete component;        
    }
    LOG_ERROR("guess not");
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

menu::MenuID MenuContext::getNextMenuID()
{
    return nextMenuID;
}

void MenuContext::setNextMenuID(menu::MenuID id)
{
    nextMenuID = id;
}

void MenuContext::reset()
{    
    nextMenuID = menu::ID_MENU_NONE;
}