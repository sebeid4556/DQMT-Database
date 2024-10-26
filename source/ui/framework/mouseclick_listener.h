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

class MouseWheelListener : public UIFrameworkSubject
{
    public:
        MouseWheelListener();
        virtual ~MouseWheelListener();
    private:
        ;
};

class MouseMotionListener : public UIFrameworkSubject
{
    public: 
        MouseMotionListener();
        virtual ~MouseMotionListener();
    private:
        ;
};

#endif // UI_FRAMEWORK_MOUSECLICK_LISTENER_H_