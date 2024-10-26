#include"cgroup.h"

CGroup::CGroup()
{
    visible = true; //default
}

CGroup::~CGroup()
{
    ;
}

void CGroup::add(UIComponent *pComponent)
{
    if(!pComponent)
    {
        LOG_ERROR("pComponent is NULL");
        fatalError("NULL pointer passed");
    }
    vComponents.push_back(pComponent);
}

bool CGroup::isVisible()
{
    return visible;
}

void CGroup::setVisible(bool visible)
{
    this->visible = visible;
    for(auto const component : vComponents)
    {
        component->setVisible(this->visible);
    }
}