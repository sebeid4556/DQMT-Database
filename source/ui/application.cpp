#include"application.h"
#include"state.h"
#include"menu/all.h"

#include<exception>

Application::Application()
{
    pUI = new UIManager();
    pEvents = new EventManager();    

    sAppState.state = APP_RUN;
    
    pUI->start();
    OK("Start UI");
    
    OK("Add Menus");    
}

//close UI and free UI & Events objects
Application::~Application()
{        
    OK("End UI");

    LOG(std::cout, "Freeing Event Handler");
    delete pEvents;

    LOG(std::cout, "Freeing UI Manager");    
    delete pUI;

    OK("End App");
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
        pUI->update();
        pUI->draw();  //draw the updated scene
    }
}