#include"event_manager.h"
#include"state.h"

EventManager::EventManager()
{
    newAppState = APP_RUN;
    didStateChange = false;
}

EventManager::~EventManager()
{
    ;
}

void EventManager::handleEventQueue()
{
    didStateChange = false;
    while(SDL_PollEvent(&event_queue))
    {
        switch(event_queue.type)
        {
            case SDL_QUIT:                
                didStateChange = true;
                newAppState = APP_STOP;
                break;
            case SDL_MOUSEBUTTONDOWN:
                MouseClickEvent.notify(&event_queue);
                break;
            default:
                break;
        }
    }
}

bool EventManager::appStateChanged()
{
    return didStateChange;
}

UINT8 EventManager::getNewAppState()
{
    return newAppState;
}