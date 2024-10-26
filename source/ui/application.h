#ifndef UI_APPLICATION_H_
#define UI_APPLICATION_H_

#include"framework/common.h"
#include"ui_manager.h"
#include"event_manager.h"

typedef struct
{
    UINT8 state;
}AppState;

class Application 
{
    public:        
        Application();
        ~Application();           
        void run();        
    private:
        AppState sAppState;
        UIManager* pUI;
        EventManager* pEvents;
};

#endif // UI_APPLICATION_H_