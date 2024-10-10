#include"img2tex.h"
#include"component/component.h"

SDL_Texture *loadPNG(const CHAR *pPath)
{
    SDL_Renderer *pRenderer = UIComponent::getRenderer();

    CHAR ext[4];
    UINT32 len = strlen(pPath);
    if(strncmp(pPath+(len - 4), ".png", sizeof(ext)))
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

SDL_Texture *loadBCLIM(const CHAR *pPath)
{
    fatalError("BCLIM loading not supported yet!", "loadBCLIM");
    return NULL;    //PLACEHOLDER
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
        return loadBCLIM(pPath);
    }
}