#ifndef UI_FRAMEWORK_COMPONENT_CSUPERIMAGE_H_
#define UI_FRAMEWORK_COMPONENT_CSUPERIMAGE_H_

#include"../../common.h"
#include"../component.h"
#include"../cimage.h"

class CSuperImage : public UIComponent
{
    public:
        CSuperImage(INT32 w, INT32 h);
        CSuperImage(INT32 w, INT32 h, SDL_PixelFormatEnum format);
        virtual ~CSuperImage();
        void addImage(const CHAR *pPath, SDL_Rect rect);
        void addImage(const CHAR *pPath, SDL_Rect rect, INT32 flip);        
        void addImage(const CHAR *pPath, SDL_Rect rect, SDL_Rect clip_rect);
        void addText(const WCHAR *pWstr, SDL_Rect rect, INT32 font_size, UINT32 wrap_length);
        void reset();
        //virtual void update(SDL_Event *pEvent);
    private:
        void init(INT32 w, INT32 h, SDL_PixelFormatEnum format);
        void clipSurface(SDL_Surface *pSrc, SDL_Rect src_rect, SDL_Surface *pDst, SDL_Rect dst_rect);
        void updateTexture();
};

#endif // UI_FRAMEWORK_COMPONENT_CSUPERIMAGE_H_