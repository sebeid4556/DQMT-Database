#include"csuperimage.h"
#include"../ctext.h"
#include"../../img2tex.h"
#include"../../bclim.h"   //for setSurfacePixel

CSuperImage::CSuperImage(INT32 w, INT32 h)
{
    init(w, h, SDL_PIXELFORMAT_RGBA8888);
}


CSuperImage::CSuperImage(INT32 w, INT32 h, SDL_PixelFormatEnum format)
{
    init(w, h, format);
}

void CSuperImage::init(INT32 w, INT32 h, SDL_PixelFormatEnum format)
{
    name = "CSuperImage";    

    if(format == SDL_PIXELFORMAT_RGBA4444)
    {
        //printf("RGBA4444\n");
        pSurface = SDL_CreateRGBSurface(0, w, h, 16, 0xF000, 0x0F00, 0x00F0, 0x000F);
    }
    else if(format == SDL_PIXELFORMAT_RGBA8888)
    {
        //printf("rgba8888\n");
        pSurface = SDL_CreateRGBSurface(0, w, h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    }
    else{
        LOG_ERROR("format has to be either RGBA4444 or RGBA8888");
        fatalError("wrong surface format");
    }
    if(!pSurface)
    {
        LOG_ERROR("Failed to create surface");
        fatalError(SDL_GetError());
    }

    //printf("pSurface (w, h) = (%d, %d)\n", pSurface->w, pSurface->h);

    setSize(w, h);

    updateTexture();
}

CSuperImage::~CSuperImage()
{
    ;
}

void CSuperImage::addImage(const CHAR *pPath, SDL_Rect rect)
{
    SDL_Surface *pNewSurface = img2surface(pPath);

    SDL_BlitScaled(pNewSurface, NULL, pSurface, &rect);

    SDL_FreeSurface(pNewSurface);

    updateTexture();
}

void CSuperImage::addImage(const CHAR *pPath, SDL_Rect rect, INT32 flip)
{
    SDL_Surface *pNewSurface = img2surface(pPath);

    flipSurface(pNewSurface, flip);

    SDL_BlitScaled(pNewSurface, NULL, pSurface, &rect);

    SDL_FreeSurface(pNewSurface);

    updateTexture();
}

void CSuperImage::addImage(const CHAR *pPath, SDL_Rect rect, SDL_Rect clip_rect)
{        
    SDL_Surface *pNewSurface = img2surface(pPath);    
    
    SDL_BlitSurface(pNewSurface, &clip_rect, pSurface, &rect);    

    SDL_FreeSurface(pNewSurface);

    updateTexture();
}

void CSuperImage::clipSurface(SDL_Surface *pSrc, SDL_Rect src_rect, SDL_Surface *pDst, SDL_Rect dst_rect)
{
    if(pSrc->format->BytesPerPixel != 2 || pSrc->format->BytesPerPixel != pDst->format->BytesPerPixel)
    {
        error("pSrc and pDst formats have to match in order to clip", "CSuperImage::clipSurface");
        return;
    }

    for(INT32 y = 0;y < src_rect.h;y++)
    {
        for(INT32 x = 0;x < pSrc->pitch;x++)
        {
            if(x >= src_rect.w) break;
            UINT32 src_offset = (y * pSrc->pitch) + (x * pSrc->format->BytesPerPixel);
            UINT8 *src_pixel = (UINT8 *)pSrc->pixels + src_offset;

            UINT32 dst_offset = (y * pDst->pitch) + (x * pDst->format->BytesPerPixel);
            UINT8 *dst_pixel = (UINT8 *)pDst->pixels + dst_offset;

            *(UINT16*)dst_pixel = *(UINT16*)src_pixel;
        }
    }
}

void CSuperImage::addText(const WCHAR *pWstr, SDL_Rect rect, INT32 font_size, UINT32 wrap_length)
{
    if(!pWstr)
    {        
        fatalError("parameter is a NULL-pointer", "CText::CText");
    }
    WCHAR text[CText::s_MAX_TEXT_LENGTH] = {0};
    wcsncpy(text, pWstr, CText::s_MAX_TEXT_LENGTH);

    TTF_SetFontSize(UIComponent::pFont, font_size);
    SDL_Surface *pTextSurface = TTF_RenderUNICODE_Blended_Wrapped(UIComponent::pFont, (const UINT16 *)text, CText::s_DEFAULT_TEXT_COLOR, wrap_length);
    if(!pTextSurface)
    {        
        fatalError(TTF_GetError(), "CText::setText");
    }

    //SDL_BlitScaled(pTextSurface, NULL, pSurface, &rect);
    SDL_BlitSurface(pTextSurface, NULL, pSurface, &rect);

    SDL_FreeSurface(pTextSurface);

    updateTexture();
}

void CSuperImage::reset()
{    
    if(pSurface) SDL_FreeSurface(pSurface);
    if(pTexture) SDL_DestroyTexture(pTexture);
    pSurface = SDL_CreateRGBSurface(0, w, h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);    
    if(!pSurface)
    {
        LOG_ERROR("Failed to create surface");
        fatalError(SDL_GetError());
    }
    updateTexture();
}

void CSuperImage::updateTexture()
{
    if(pTexture)
    {
        SDL_DestroyTexture(pTexture);
    }

    pTexture = SDL_CreateTextureFromSurface(UIComponent::getRenderer(), pSurface);
    if(!pTexture)
    {
        LOG_ERROR("Failed to create texture from surface");
        fatalError(SDL_GetError());
    }    
}