#ifndef UI_FRAMEWORK_SUBJECT_H_
#define UI_FRAMEWORK_SUBJECT_H_

#include"observer.h"

class UIFrameworkSubject
{
    public:
        virtual ~UIFrameworkSubject();
        //not sure if these need to be virtual
        virtual void attach(UIFrameworkObserver *pObserver);
        virtual void detach(UIFrameworkObserver *pObserver);
        virtual void notify(SDL_Event *pEvent);
    private:
    protected:
        std::list<UIFrameworkObserver *> lObservers;
};

#endif // UI_FRAMEWORK_SUBJECT_H_

