#ifndef UI_MENU_MAIN_MENU_H_
#define UI_MENU_MAIN_MENU_H_

#include"../menu_context.h"
#include"../framework/common.h"
#include"../../database/database.h"

typedef struct
{    
    CSuperImage *icon;
    CText *name;
    CText *rank;
    CText *id;
    CText *size;
    CText *species;
    CText *max_hp_value;
    CText *max_mp_value;
    CText *max_atk_value;    
    CText *max_def_value;
    CText *max_spd_value;
    CText *max_int_value;
    CText *size_trait_id;   //added
    CText *size_trait;
    CText *trait_ids[MAX_MONSTER_TRAITS];   //added
    CText *traits[MAX_MONSTER_TRAITS];
    CText *resistance[NUM_RESISTANCE_TYPES];
    CText *resistance_values[NUM_RESISTANCE_TYPES];
    CImage *resistance_values_bg[NUM_RESISTANCE_TYPES];
    CText *skill;    
}MonsterDisplayInfo;

class MainMenu;

class TestButton : public CButton
{
    public:        
        TestButton(const CHAR *pPathIdle, const CHAR *pPathClicked, MainMenu *pMenuObj);
        virtual ~TestButton();
        void onClick() override;
    private:
        MainMenu *pMenuObj = NULL;
};

class GotoSearchButton : public CButton
{
    public:        
        GotoSearchButton(const CHAR *pPathIdle, const CHAR *pPathClicked, MainMenu *pMenuObj);
        virtual ~GotoSearchButton();
        void onClick() override;
    private:        
        MainMenu *pMenuObj = NULL;
};

class SearchButton : public CButton
{
    public:
        SearchButton(MainMenu *pMenuObj);
        virtual ~SearchButton();
        void onClick() override;
    private:
        const INT32 SEARCH_BUTTON_WIDTH = 200;
        const INT32 SEARCH_BUTTON_HEIGHT = 100;

        MainMenu *pMenuObj = NULL;
};

class Window : public CSuperImage
{
    public:
        static const INT32 MINIMUM_WIDTH = 200;
        static const INT32 MINIMUM_HEIGHT = 200;
        enum WindowType {WINDOW_TYPE_BASIC, WINDOW_TYPE_SQUARE};

        Window(INT32 w, INT32 h);
        Window(INT32 w, INT32 h, WindowType type, bool decorate, std::wstring title);
        ~Window();
    private:
        std::wstring title;
        WindowType type;
        bool decorate;
        void createWindow();
};

class Line : public CSuperImage
{
    public:
        Line(INT32 length);
        ~Line();
    private:
        ;
};

class Table : public CSuperImage
{
    public:
        UINT32 rows, cols;
        INT32 cell_w, cell_h;        
        INT32 total_w, total_h;

        Table(INT32 cell_w, INT32 cell_h, UINT32 rows, UINT32 cols);
        Table(INT32 cell_w, INT32 cell_h, UINT32 rows, UINT32 cols, bool doBackground);
        ~Table();
    private:
        void drawBackground();
        void drawFrame();      
};

class Box : public CSuperImage
{
    public:
        Box(INT32 w, INT32 h);
        ~Box();
    private:
        void drawBackground();
        void drawFrame();  
};

class Cursor : public CImage
{
    public:
        Cursor();
        ~Cursor();
        void update(SDL_Event *pEvent) override;
    private:
        ;
};

class MonsterList : public CSuperImage
{
    public:
        MonsterList(INT32 w, INT32 h, INT32 rows, INT32 gap, MainMenu *pMenuObj);
        ~MonsterList();
        void setTopMonsterID(UINT16 monster_id);
        void onClick() override;
        void update(SDL_Event *pEvent) override;                
    private:        
        UINT32 row_focus = 0;
        UINT32 last_row_focus;
        
        INT32 row_w, row_h;
        INT32 rows, gap;        
        UINT16 top_monster_id = 1;
        MainMenu *pMenuObj = NULL;
        std::vector<UINT16> vMonsterIDs;        

        void updateTexture();
};

class TraitList : public CSuperImage
{
    public:
        TraitList(INT32 row_w, INT32 row_h, INT32 rows, INT32 gap, MainMenu *pMenuObj, UINT16 top_trait_id);
        ~TraitList();
        void setTopTraitID(UINT16 trait_id);
        void onClick() override;
        void update(SDL_Event *pEvent) override;                
    private:        
        UINT32 row_focus = 0;
        UINT32 last_row_focus;
        
        INT32 row_w, row_h;
        INT32 rows, gap;        
        UINT16 top_trait_id = 1;
        MainMenu *pMenuObj = NULL;
        std::vector<UINT16> vTraitIDs;        

        void updateTexture();
};

class DebugInfo: public CSuperImage
{
    public:
        DebugInfo();
        ~DebugInfo();

        void update(SDL_Event *pEvent) override;        
    private:
        const INT32 DEBUG_INFO_WIDTH = 400;
        const INT32 DEBUG_INFO_HEIGHT = 400;
};

class MainMenu : public MenuContext
{
    public:
        MainMenu();
        ~MainMenu();

        //give these classes access to addComponent()
        friend class TestButton;
        friend class GotoSearchButton;
        friend class SearchButton;
        friend class MonsterList;
        friend class TraitList;
    private:                
        UINT16 monster_id = 0x0000;   
        UINT16 monster_id_last  = 0x02BD;          
        UINT16 monster_id_first = 0x0001;          
        const WCHAR DEFAULT_TEXT[0x10] = L"EMPTY"; 
        const INT32 RESISTANCE_TABLE_CELL_WIDTH = 50;
        const INT32 RESISTANCE_TABLE_CELL_HEIGHT = 25;
        const INT32 ICON_BASE_LENGTH = 80;

        MonsterDisplayInfo monster_info;
        MonsterList *monster_list;        
        CGroup group_search;
        CGroup group_debug_info;

        void buttonCallback();
        void gotoSearchButtonCallback();
        void searchButtonCallback();

        void initComponents();                
        void loadMonsterInfo(UINT16 monster_id);
        std::string getIconPathFromID(UINT16 id);    
        UINT16 getNextMonsterID(UINT16 id);    
        UINT16 getPrevMonsterID(UINT16 id); 
        stats::Size getMonsterSize(UINT16 id);
};

#endif // UI_MENU_MAIN_MENU_H_