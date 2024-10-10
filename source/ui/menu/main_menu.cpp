#include"main_menu.h"
#include"../framework/component/all.h"
#include"../ui_manager.h"

MainMenu::MainMenu()
{
    //CImage *pTest = new CImage("resource/ic_0002.png");
    //addComponent(pTest);

    CImage *bg = new CImage("resource/bg1.png");
    bg->setPosition(0, 0);
    bg->setSize(UIManager::DEFAULT_WINDOW_WIDTH, UIManager::DEFAULT_WINDOW_HEIGHT);
    addComponent(bg);

    CImage *top_part1 = new CImage("resource/top_text_part1.png");
    top_part1->setPosition(0, 0);
    addComponent(top_part1);

    CImage *top_part2 = new CImage("resource/top_text_part2.png");
    top_part2->setPosition(top_part1->getRect()->w, 0);
    top_part2->setSize(UIManager::DEFAULT_WINDOW_WIDTH - top_part1->getRect()->w, top_part2->getRect()->h);
    addComponent(top_part2);

    CImage *ic_base = new CImage("resource/iconbase_blue.png");
    ic_base->setPosition(200, 200);
    ic_base->setSize(200, 200);
    addComponent(ic_base);

    CImage *ic_bubble = new CImage("resource/ic_0002.png");
    ic_bubble->setPosition(200, 200);
    ic_bubble->setSize(200, 200);
    addComponent(ic_bubble);

    CText *hello = new CText(L"Hello DQMT!", 40);
    hello->setPosition(400, 200);    
    addComponent(hello);

    CText *msg = new CText(L"Bubble Slime!");
    msg->setPosition(400, 300);    
    addComponent(msg);
}

MainMenu::~MainMenu()
{
    ;
}