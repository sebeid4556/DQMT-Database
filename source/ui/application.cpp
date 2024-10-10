#include"application.h"
#include"state.h"
#include"menu/all.h"

Application::Application()
{
    pUI = new UIManager();
    pEvents = new EventManager();

    sAppState.state = APP_RUN;
    
    pUI->start();
    OK("Start UI");
    
    initAllMenus();
    OK("Add Menus");    
}

//close UI and free UI & Events objects
Application::~Application()
{    
    pUI->end();
    OK("End UI");

    delete pUI;
    delete pEvents;

    OK("End App");
}

void Application::initAllMenus()
{
    pUI->addMenu(new MainMenu());
}

void Application::run()
{
    OK("Start App");

    sAppState.state = APP_RUN;

    while(sAppState.state != APP_STOP)
    {
        pEvents->handleEventQueue();  //respond to user input and update components 
        if(pEvents->appStateChanged())
        {
            sAppState.state = pEvents->getNewAppState();
        }
        pUI->draw();  //draw the updated scene
    }
}