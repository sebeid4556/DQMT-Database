#ifndef UI_MENU_START_MENU_H_
#define UI_MENU_START_MENU_H_

#include"../menu_context.h"
#include"../framework/common.h"

class StartMenu;

class TestButton2 : public CButton
{
    public:
        TestButton2(const CHAR *pPathIdle, const CHAR *pPathClicked, StartMenu *pMenuObj);
        virtual ~TestButton2();
        void onClick() override;
    private:
        StartMenu *pMenuObj = NULL;
};

class StartMenu : public MenuContext
{
    public:
        StartMenu();
        ~StartMenu();
        void buttonCallback();
    private:
        ;
};

#endif // UI_MENU_START_MENU_H_