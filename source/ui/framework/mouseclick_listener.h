#ifndef UI_FRAMEWORK_MOUSECLICK_LISTENER_H_
#define UI_FRAMEWORK_MOUSECLICK_LISTENER_H_

#include"common.h"
#include"subject.h"

class MouseClickListener : public UIFrameworkSubject
{
    public: 
        MouseClickListener();
        virtual ~MouseClickListener();
    private:
        ;
};

#endif // UI_FRAMEWORK_MOUSECLICK_LISTENER_H_