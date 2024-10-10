#ifndef UI_FRAMEWORK_CTEXT_H_
#define UI_FRAMEWORK_CTEXT_H_

#include"../common.h"
#include"component.h"

class CText : public UIComponent
{
    public:
        static const UINT32 s_MAX_TEXT_LENGTH = 256;  //WCHAR is 2 bytes so essentially 512 bytes
        static const SDL_Color s_DEFAULT_TEXT_COLOR;
        static const UINT32 s_DEFAULT_WRAP_LENGTH;
        static const INT32 s_DEFAULT_FONT_SIZE;

        CText(const WCHAR *pWstr);
        CText(const WCHAR *pWstr, INT32 font_size);
        virtual ~CText();
        void update(SDL_Event *pEvent) override;
        void setText(const WCHAR *pWstr);
        void setWrapLength(UINT32 wrap_length);
        void setFontSize(INT32 font_size);
    private:
        WCHAR text[CText::s_MAX_TEXT_LENGTH] = {NULL};
        UINT32 wrap_length = s_DEFAULT_WRAP_LENGTH;     
        INT32 font_size = s_DEFAULT_FONT_SIZE;   
        SDL_Color *pTextColor = (SDL_Color *)&s_DEFAULT_TEXT_COLOR;;
        SDL_Texture *pTextTexture = NULL;
};

#endif // UI_FRAMEWORK_CTEXT_H_