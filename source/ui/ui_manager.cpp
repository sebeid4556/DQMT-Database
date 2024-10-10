#include"ui_manager.h"
#include"framework/component/component.h"

UIManager::UIManager()
{    
    init();
    loadFont(DEFAULT_FONT_PATH, DEFAULT_FONT_SIZE);
    UIComponent::setFont(pFont);

    OK("Initialize UI");
}

//free each menu
UIManager::~UIManager()
{
    for(UINT32 i = 0;i < vMenuList.size();i++)
    {
        if(vMenuList.at(i))
        {
            delete vMenuList.at(i);
        }
    }    

    TTF_CloseFont(pFont);
    SDL_Quit();

    OK("Uninitialize UI");
}

void UIManager::start()
{
    if(SDL_CreateWindowAndRenderer(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &pWindow, &pRenderer))
    {
        fatalError(SDL_GetError(), "UIManager::start");
    }
    
    UIComponent::setRenderer(pRenderer);    //set renderer to be shared across all components
    OK("Set UIComponent::pRenderer");
}

void UIManager::addMenu(MenuContext *pMenu)
{
    if(!pMenu)
    {
        fatalError("NULL is an invalid argument", "UIManager::addMenu");
    }
    
    //if this is the first menu to be added, then set it as the default menu
    if(vMenuList.size() == 0)
    {
        this->pMenu = pMenu;
    }

    vMenuList.push_back(pMenu);
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
    for(UINT32 i = 0;i < vContext.size();i++)
    {
        if(SDL_RenderCopy(UIComponent::getRenderer(), vContext.at(i)->getTexture(), NULL, vContext.at(i)->getRect()))
        {
            fatalError(SDL_GetError(), "UIManager::draw");
        }
    }

    SDL_RenderPresent(UIComponent::getRenderer());
}

void UIManager::end()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
}

void UIManager::init()
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