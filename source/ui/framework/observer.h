#ifndef UI_FRAMEWORK_OBSERVER_H_
#define UI_FRAMEWORK_OBSERVER_H_

#include"common.h"

class UIFrameworkObserver
{
    public:
        UIFrameworkObserver();
        virtual ~UIFrameworkObserver();
        virtual void update(SDL_Event *pEvent);
    private:        
        static UINT32 static_id;
        UINT32 id;
};

#endif // UI_FRAMEWORK_OBSERVER_H_