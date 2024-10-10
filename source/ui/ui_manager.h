#ifndef UI_UI_MANAGER_H_
#define UI_UI_MANAGER_H_

#include"framework/common.h"
#include"menu_context.h"
#include"menu/all.h"

class UIManager
{
    public:
        const CHAR DEFAULT_FONT_PATH[MAX_PATH] = "resource/font/KosugiMaru-Regular.ttf";
        const static INT32 DEFAULT_FONT_SIZE = 20;
        const static UINT32 DEFAULT_WINDOW_WIDTH = 1200;
        const static UINT32 DEFAULT_WINDOW_HEIGHT = 700;

        UIManager();
        ~UIManager();
        void start();
        void addMenu(MenuContext *pMenu);
        void draw();
        void end();        
    private:
        SDL_Window *pWindow = NULL;
        SDL_Renderer *pRenderer = NULL;
        TTF_Font *pFont = NULL;

        std::vector<MenuContext *> vMenuList;
        MenuContext *pMenu = NULL;  //current menu

        void init();
        void loadFont(const CHAR *pPath, INT32 size);
};

#endif // UI_UI_MANAGER_H_