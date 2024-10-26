#include"event_manager.h"
#include"state.h"
#include"framework/component/component.h"

EventManager::EventManager()
{
    initEventListeners();

    newAppState = APP_RUN;
    didStateChange = false;
}

EventManager::~EventManager()
{
    for(auto const& eventListener : mEventListeners)
    {
        delete eventListener.second;
    }
}

//add event listener objects to the std::map
void EventManager::initEventListeners()
{    
    mEventListeners[EVENT_LISTENER_MOUSECLICK] = new MouseClickListener();
    mEventListeners[EVENT_LISTENER_MOUSEWHEEL] = new MouseWheelListener();
    mEventListeners[EVENT_LISTENER_MOUSEMOTION] = new MouseMotionListener();

    UIComponent::setEventListeners(&mEventListeners);
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
                mEventListeners.at(EVENT_LISTENER_MOUSECLICK)->notify(&event_queue);
            case SDL_MOUSEBUTTONUP:                
                mEventListeners.at(EVENT_LISTENER_MOUSECLICK)->notify(&event_queue);                
                break;
            case SDL_MOUSEWHEEL:
                mEventListeners.at(EVENT_LISTENER_MOUSEWHEEL)->notify(&event_queue);
                break;
            case SDL_MOUSEMOTION:
                mEventListeners.at(EVENT_LISTENER_MOUSEMOTION)->notify(&event_queue);
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