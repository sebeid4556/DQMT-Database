#include"menu_context.h"

MenuContext::MenuContext()
{
    ;
}

//free each component
MenuContext::~MenuContext()
{    
    std::cout << "Freeing " << vComponents.size() << " components" << std::endl;
    int n = 0;
    for(auto const& component : vComponents)
    {        
        std::cout << "component " << n++ << "\t(" << component->name << ")" <<  std::endl;
        delete component;        
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