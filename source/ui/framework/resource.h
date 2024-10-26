#ifdef NEVER_DEFINED
#pragma once

#include"common.h"

//WORK IN PROGRESS

namespace resource
{
    enum ResourceID
    {
        IMAGE = 0, FONT, AUDIO
    };
};

class Resource
{
    public:
        Resource(const std::string& name);
        ~Resource();
    protected:
        std::string name;
};

class ResourceImage : public Resource
{
    public:
        ResourceImage(const std::string &name);
        ~ResourceImage();
        SDL_Surface *getSurface();
        SDL_Texture *getTexture();        
    private:        
        SDL_Surface *pSurface = NULL;
        SDL_Texture *pTexture = NULL;
};
#endif