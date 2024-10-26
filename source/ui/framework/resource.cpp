#ifdef NEVER_DEFINED
#include"resource.h"

Resource::Resource(const std::string& name)
{
    this->name = name;
}

Resource::~Resource()
{
    ;
}

ResourceImage::ResourceImage(const std::string& name) : Resource(name)
{
    ;
}

const SDL_Surface *ResourceImage::getSurface()
{
    ;
}
#endif