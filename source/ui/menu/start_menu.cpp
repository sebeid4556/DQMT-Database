#include"start_menu.h"
#include"../framework/component/all.h"
#include"../ui_manager.h"

TestButton2::TestButton2(const CHAR *pPathIdle, const CHAR *pPathClicked, StartMenu *pMenuObj) : CButton(pPathIdle, pPathClicked)
{
    this->pMenuObj = pMenuObj;
}
TestButton2::~TestButton2() {}

void TestButton2::onClick()
{
    //LOG(std::cout, "TestButton::onClick()");
    this->pMenuObj->buttonCallback();
}

StartMenu::StartMenu()
{    
    CImage *bg = new CImage("bg1.png");
    bg->setPosition(0, 0);
    bg->setSize(UIManager::DEFAULT_WINDOW_WIDTH, UIManager::DEFAULT_WINDOW_HEIGHT);
    addComponent(bg);
    
    CImage *top_part1 = new CImage("top_text_part1.png");
    top_part1->setPosition(0, 0);
    addComponent(top_part1);

    CImage *top_part2 = new CImage("top_text_part2.png");
    top_part2->setPosition(top_part1->getRect()->w, 0);
    top_part2->setSize(UIManager::DEFAULT_WINDOW_WIDTH - top_part1->getRect()->w, top_part2->getRect()->h);
    addComponent(top_part2);

    CImage *bottom_part = new CImage("top_text_part2.png");
    bottom_part->flip(FLIP_VERTICAL);
    bottom_part->setPosition(0, UIManager::DEFAULT_WINDOW_HEIGHT - bottom_part->getRect()->h);
    bottom_part->setSize(UIManager::DEFAULT_WINDOW_WIDTH, bottom_part->getRect()->h);
    addComponent(bottom_part);

    //=====================================================================================================================

    TestButton2 *button = new TestButton2("test_button1.png", "test_button2.png", this);
    button->setPosition(400, 400);
    addComponent(button);

    //=====================================================================================================================

    CSuperImage *filter_screen = new CSuperImage(UIManager::DEFAULT_WINDOW_WIDTH, UIManager::DEFAULT_WINDOW_HEIGHT);
    filter_screen->addImage("filter1.png", {0, 0, UIManager::DEFAULT_WINDOW_WIDTH, 100});
    filter_screen->addImage("filter1.png", {0, 100, UIManager::DEFAULT_WINDOW_WIDTH, 100});
    filter_screen->addImage("filter1.png", {0, 200, UIManager::DEFAULT_WINDOW_WIDTH, 100});
    filter_screen->addImage("filter1.png", {0, 300, UIManager::DEFAULT_WINDOW_WIDTH, 100});
    filter_screen->addImage("filter1.png", {0, 400, UIManager::DEFAULT_WINDOW_WIDTH, 100});
    filter_screen->addImage("filter1.png", {0, 500, UIManager::DEFAULT_WINDOW_WIDTH, 100});
    filter_screen->addImage("filter1.png", {0, 600, UIManager::DEFAULT_WINDOW_WIDTH, 100});    
    addComponent(filter_screen);

    CSuperImage *filter_blur = new CSuperImage(UIManager::DEFAULT_WINDOW_WIDTH, UIManager::DEFAULT_WINDOW_HEIGHT);
    filter_blur->addImage("filter2.png", {0, 0, UIManager::DEFAULT_WINDOW_WIDTH, 100});
    filter_blur->addImage("filter2.png", {0, 600, UIManager::DEFAULT_WINDOW_WIDTH, 100}, FLIP_VERTICAL);
    addComponent(filter_blur);    
}

StartMenu::~StartMenu()
{
    ;
}

void StartMenu::buttonCallback()
{
    setNextMenuID(menu::ID_MENU_MAIN);
}