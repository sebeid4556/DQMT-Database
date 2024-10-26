#include<chrono>
#include<thread>

#include"ui_manager.h"
#include"framework/component/component.h"

UIManager::UIManager()
{    
    initSDL();    
    
    loadFont(DEFAULT_FONT_PATH.c_str(), DEFAULT_FONT_SIZE);
    UIComponent::setFont(pFont);

    OK("Initialize UI");

    last = std::chrono::system_clock::now();
}

//free each menu
UIManager::~UIManager()
{
    LOG(std::cout, "deleteing menus");
    for(auto const& menu : mMenuList)
    {
        std::cout << "deleting " << menu.second << std::endl;
        delete menu.second;
    }

    OK("Uninitialize UI");

    end();
}

void UIManager::start()
{
    if(SDL_CreateWindowAndRenderer(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &pWindow, &pRenderer))
    {
        fatalError(SDL_GetError(), "UIManager::start");
    }

    SDL_SetWindowTitle(pWindow, "DQMT-Database");
    //SDL_SetWindowBordered(pWindow, SDL_FALSE);
    //SDL_SetWindowFullscreen(pWindow, SDL_TRUE);    

    UIComponent::setRenderer(pRenderer);    //set renderer to be shared across all components
    OK("Set UIComponent::pRenderer");

    SDL_ShowCursor(SDL_FALSE);

    addAllMenus();

    loadMenu(menu::ID_MENU_MAIN);
}

void UIManager::addMenu(MenuContext *pMenu, menu::MenuID id)
{
    if(!pMenu)
    {
        fatalError("NULL is an invalid argument", "UIManager::addMenu");
    }    
        
    mMenuList.insert(std::pair<menu::MenuID, MenuContext*>(id, pMenu));    
}

void UIManager::addAllMenus()
{        
    addMenu(new MainMenu(), menu::ID_MENU_MAIN);
    addMenu(new StartMenu(), menu::ID_MENU_START);
}

void UIManager::loadMenu(menu::MenuID id)
{
    pMenu = mMenuList.at(id);
    menu_id = id;
}

void UIManager::update()
{
    menu::MenuID next_menu_id = pMenu->getNextMenuID();
    if(next_menu_id != menu::ID_MENU_NONE)
    {
        //LOG(std::cout, "transitioning menus!");
        printf("going from menu %d to %d\n", menu_id, next_menu_id);
        //pMenu->setNextMenuID(menu::ID_MENU_NONE);
        pMenu->reset();
        loadMenu(next_menu_id); //set current menu to one corresponding to next_menu_id
    }
}

void UIManager::draw()
{
    if(SDL_RenderClear(UIComponent::getRenderer()))
    {
        fatalError(SDL_GetError(), "UIManager::draw");
    }

    if(!pMenu)
    {
        fatalError("current menu is NULL", "UIManager::draw");
    }

    const std::vector<UIComponent *> vContext = pMenu->getContext();
    for(const auto& component : vContext)
    {
        if(!component->isVisible()) //only draw visible components
        {
            continue;
        }
        if(SDL_RenderCopy(UIComponent::getRenderer(), component->getTexture(), NULL, component->getRect()))   //render
        {
            fatalError(SDL_GetError(), "UIManager::draw");
        }
    }

    waitFrame();

    SDL_RenderPresent(UIComponent::getRenderer());
}

void UIManager::end()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);

    TTF_CloseFont(pFont);
    SDL_Quit();
}

void UIManager::initSDL()
{    
    if(SDL_Init(SDL_INIT_VIDEO)) fatalError(SDL_GetError(), "UIManager::init");    
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) fatalError(IMG_GetError(), "UIManager::init");    
    if(TTF_Init()) fatalError(TTF_GetError(), "UIManager::init");    
}

void UIManager::loadFont(const CHAR *pPath, INT32 size)
{
    if(strlen(pPath) > MAX_PATH)
    {
        fatalError("font path too long", "UIManager::loadFont");
    }
    pFont = TTF_OpenFont(pPath, size);
    if(!pFont)
    {
        fatalError(TTF_GetError(), "UImanager::laodFont");
    }
}

void UIManager::waitFrame()
{
    if(std::chrono::high_resolution_clock::now() < (last + std::chrono::milliseconds(TIME_SECOND_MS / fps)))
    {
        std::chrono::duration<float> remaining = (last + std::chrono::milliseconds(TIME_SECOND_MS / fps)) - std::chrono::high_resolution_clock::now();        
        std::this_thread::sleep_for(remaining);
    }
    last = std::chrono::high_resolution_clock::now();

}