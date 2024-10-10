#ifndef UI_APPLICATION_H_
#define UI_APPLICATION_H_

#include"framework/common.h"
#include"ui_manager.h"
#include"event_manager.h"

typedef struct AppState
{
    UINT8 state;
};

class Application 
{
    public:        
        //enum APP_STATES {APP_RUN = 0, APP_STOP};
        Application();
        ~Application();
        void initAllMenus();        
        void run();        
    private:
        AppState sAppState;
        UIManager* pUI;
        EventManager* pEvents;
};

#endif // UI_APPLICATION_H_