#include"subject.h"

UIFrameworkSubject::~UIFrameworkSubject()
{
    ;
}

void UIFrameworkSubject::attach(UIFrameworkObserver *pObserver)
{
    lObservers.push_back(pObserver);
}

void UIFrameworkSubject::detach(UIFrameworkObserver *pObserver)
{
    lObservers.remove(pObserver);
}

void UIFrameworkSubject::notify(SDL_Event *pEvent)
{
    for(auto const& observer : lObservers)
    {
        observer->update(pEvent);
    }
}