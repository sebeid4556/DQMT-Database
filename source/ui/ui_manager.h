#ifndef UI_UI_MANAGER_H_
#define UI_UI_MANAGER_H_

#include<chrono>

#include"framework/common.h"
#include"menu_context.h"
#include"menu/all.h"

class UIManager
{
    public:
        //const CHAR DEFAULT_FONT_PATH[MAX_PATH] = "../resource/font/KosugiMaru-Regular.ttf";
        const std::string DEFAULT_FONT_PATH = "../resource/font/KosugiMaru-Regular.ttf";
        const static INT32 DEFAULT_FONT_SIZE = 20;
        const static UINT32 DEFAULT_WINDOW_WIDTH = 1600;
        const static UINT32 DEFAULT_WINDOW_HEIGHT = 900;
        const static UINT32 TIME_SECOND_MS = 1000;
        const static UINT32 DEFAULT_FPS = 60;

        UIManager();
        ~UIManager();
        void start();        
        void addMenu(MenuContext *pMenu, menu::MenuID id);        
        void update();
        void draw();
        void end();        
    private:
        SDL_Window *pWindow = NULL;
        SDL_Renderer *pRenderer = NULL;
        TTF_Font *pFont = NULL;
        
        std::map<menu::MenuID, MenuContext *> mMenuList;
        MenuContext *pMenu = NULL;  //current menu   
        menu::MenuID menu_id = menu::ID_MENU_MAIN;  //default menu id

        UINT32 fps = DEFAULT_FPS;
        std::chrono::time_point<std::chrono::high_resolution_clock> last;        

        void initSDL();
        void addAllMenus();
        void loadMenu(menu::MenuID id);
        void loadFont(const CHAR *pPath, INT32 size);        
        void waitFrame();
};

#endif // UI_UI_MANAGER_H_