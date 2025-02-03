#include"img2tex.h"
#include"component/component.h"
#include"bclim.h"

#include"../resource_manager.h"

SDL_Texture *loadPNG(const CHAR *pPath)
{
    SDL_Renderer *pRenderer = UIComponent::getRenderer();

    if(!checkExtension(pPath, ".png"))
    {
        fatalError("expected .png", "loadPNG");
    }

    SDL_Texture *pTexture = IMG_LoadTexture(pRenderer, pPath);
    if(!pTexture)
    {
        fatalError("IMG_LoadTexture() failed", "loadPNG");
    }
    return pTexture;
}

SDL_Texture *img2tex(const CHAR *pPath)
{
    if(!UIComponent::getRenderer())
    {
        fatalError("UIComponent::pRenderer not initialized yet", "loadPNG");
    }

    if(strlen(pPath) > MAX_PATH)
    {
        fatalError("File path is too long", "loadImageTexture");
    }

    CHAR *pFileExt = strchr(pPath, '.');

    if(!pFileExt)
    {
        fatalError("File extension missing?", "loadImageTexture");
    }

    if(strncmp(pFileExt, ".png", strlen(pFileExt)) == 0)
    {
        return loadPNG(pPath);
    }
    else if(strncmp(pFileExt, ".bclim", strlen(pFileExt)) == 0)
    {
        //Load BCLIM into surface
        //loadBCLIM(pPath);
        return NULL;
    }
    else
    {
        fatalError("image file extension needs to be either .png or .bclim", "img2tex");    //exit application     
    }    
    return NULL;    //never reaches 
}

SDL_Texture *img2tex(const CHAR *pPath, SDL_Surface **pSurfaceOut)
{
    if(!UIComponent::getRenderer())
    {
        fatalError("UIComponent::pRenderer not initialized yet", "img2tex");
    }    
    if(!pSurfaceOut)
    {
        fatalError("pSurfaceOut is NULL", "img2tex");
    }

    SDL_Surface *pSurface = NULL;

    pSurface = img2surface(pPath);

    if(!pSurface)
    {
        fatalError("pSurface is NULL because nothing was loaded", "img2tex");
    }

    *pSurfaceOut = pSurface;

    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(UIComponent::getRenderer(), pSurface);
    if(!pTexture)
    {
        fatalError(SDL_GetError(), "img2tex");
    }
    return pTexture;
}

SDL_Surface *img2surface(const CHAR *pPath)
{
    /*if(strlen(pPath) > MAX_PATH)
    {
        fatalError("File path is too long");
    }
    if(!pPath)
    {
        fatalError("Path is NULL");
    }
    SDL_Surface *pSurface = NULL;
    if(checkExtension(pPath, ".png"))
    {
        pSurface = IMG_Load(pPath);
        if(!pSurface)
        {
            fatalError(IMG_GetError(), "img2surface");
        }
    }
    else if(checkExtension(pPath, ".bclim"))
    {
        pSurface = loadBCLIMSurface(pPath);
    }
    else
    {
        LOG_ERROR("expected .png or .bclim");
        fatalError("unsupported file extention");
    }

    return pSurface;*/    

    return ResourceManager::getInstance()->getImage(std::string(pPath))->getCopySurface();
}