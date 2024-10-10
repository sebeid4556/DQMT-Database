#ifndef UI_EVENT_MANAGER_H_
#define UI_EVENT_MANAGER_H_

#include"framework/common.h"
#include"framework/subject.h"
#include"framework/observer.h"
#include"framework/mouseclick_listener.h"

class EventManager
{
    public:
        EventManager();
        ~EventManager();
        void handleEventQueue();
        bool appStateChanged();
        UINT8 getNewAppState();
    private:
        bool didStateChange;
        UINT8 newAppState;
        SDL_Event event_queue;

        MouseClickListener MouseClickEvent;
};

#endif // UI_EVENT_MANAGER_H_