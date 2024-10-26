#pragma once

#include"../common.h"
#include"component.h"

//WORK IN PROGRESS

class CGroup
{
    public:
        CGroup();   
        virtual ~CGroup();        
        void add(UIComponent *pComponent);
        bool isVisible();
        void setVisible(bool visible);
    private:     
        bool visible;
        std::vector<UIComponent *> vComponents;
};