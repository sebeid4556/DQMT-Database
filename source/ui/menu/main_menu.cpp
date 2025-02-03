#include"main_menu.h"
#include"../framework/component/all.h"
#include"../ui_manager.h"
#include"../framework/img2tex.h"

//=====================================================================================================================

TestButton::TestButton(const CHAR *pPathIdle, const CHAR *pPathClicked, MainMenu *pMenuObj) : CButton(pPathIdle, pPathClicked)
{
    this->pMenuObj = pMenuObj;
}
TestButton::~TestButton() {}

void TestButton::onClick()
{    
    this->pMenuObj->buttonCallback();    
}

GotoSearchButton::GotoSearchButton(const CHAR *pPathIdle, const CHAR *pPathClicked, MainMenu *pMenuObj) : CButton(pPathIdle, pPathClicked)
{
    this->pMenuObj = pMenuObj;
}
GotoSearchButton::~GotoSearchButton() {}

void GotoSearchButton::onClick()
{
    pMenuObj->gotoSearchButtonCallback();
}

//=====================================================================================================================

SearchButton::SearchButton(MainMenu *pMenuObj) : CButton("test_button3.png", "test_button2.png")
{
    this->pMenuObj = pMenuObj;
    setSize(SEARCH_BUTTON_WIDTH, SEARCH_BUTTON_HEIGHT);
}
SearchButton::~SearchButton() {}

void SearchButton::onClick()
{
    pMenuObj->searchButtonCallback();
}

//=====================================================================================================================

Window::Window(INT32 w, INT32 h) : CSuperImage(w, h)
{       
    this->type = WINDOW_TYPE_BASIC;
    decorate = false;
    title = L"";
    createWindow();
}

Window::Window(INT32 w, INT32 h, WindowType type, bool decorate, std::wstring title) : CSuperImage(w, h)
{       
    this->type = type;
    this->decorate = decorate;    
    this->title = title;
    createWindow();
}

Window::~Window()
{
    ;
}

void Window::createWindow()
{
    if(w < MINIMUM_WIDTH || h < MINIMUM_HEIGHT)
    {
        LOG_ERROR("Window size too small");
        fatalError("failed to create Window object");
    }

    INT32 hori_len = w - MINIMUM_WIDTH;
    INT32 vert_len = h - MINIMUM_HEIGHT;

    std::string img_corner = "";
    INT32 flip_top_left = (INT32)NULL;
    INT32 flip_bottom_right = (INT32)NULL;

    switch(type)
    {
        case WINDOW_TYPE_BASIC:
            img_corner += "popup_corner1.png";
            flip_top_left = (INT32)NULL;
            flip_bottom_right = FLIP_HORIZONTAL | FLIP_VERTICAL;
            break;
        case WINDOW_TYPE_SQUARE:
            img_corner += "popup_corner2.png";            
            flip_top_left = FLIP_HORIZONTAL;
            flip_bottom_right = FLIP_VERTICAL;
            break;
        default:
            LOG_ERROR("invalid window type");
            fatalError("invalid window type");
            break;
    }
    addImage(img_corner.c_str(), {0, 0, 100, 100}, flip_top_left);    //top left
    addImage("popup_side1.png", {100, 0, hori_len, 100});    //top side
    addImage("popup_corner2.png", {100+hori_len, 0, 100, 100});  //top right
    addImage("popup_side2.png", {0, 100, 100, vert_len});    //left side
    addImage("popup_pane1.png", {100, 100, hori_len, vert_len});  //middle section
    addImage("popup_side2.png", {100+hori_len, 100, 100, vert_len}, FLIP_HORIZONTAL); //right side
    addImage("popup_corner2.png", {0, 100+vert_len, 100, 100}, FLIP_HORIZONTAL | FLIP_VERTICAL); //bottom left
    addImage("popup_side1.png", {100, 100+vert_len, hori_len, 100}, FLIP_VERTICAL);   //bottom side
    addImage(img_corner.c_str(), {100+hori_len, 100+vert_len, 100, 100}, flip_bottom_right);   //bottom right       

    if(decorate)
    {
        addImage("top_text_part1_dark.png", {10, 10, (INT32)(MINIMUM_WIDTH * 1.5), 80});
        addImage("top_text_part2_dark.png", {10+(INT32)(MINIMUM_WIDTH * 1.5), 10, w-(INT32)(MINIMUM_WIDTH * 1.5)-20, 35});

        if(title != L"")
        {
            addText(title.c_str(), {20, 50, (INT32)(MINIMUM_WIDTH * 1.5), 80}, 30, (INT32)(MINIMUM_WIDTH * 1.5));
        }
    }

}

//=====================================================================================================================

Line::Line(INT32 length) : CSuperImage(length, 10)
{
    addImage("text_line1.png", {0, 0, 10, 10});
    addImage("text_line2.png", {10, 3, length-20, 4});
    addImage("text_line1.png", {length-10, 0, 10, 10});
}

Line::~Line()
{
    ;
}

//=====================================================================================================================

Table::Table(INT32 cell_w, INT32 cell_h, UINT32 rows, UINT32 cols) : CSuperImage(cols * (cell_w) + 4, rows * (cell_h) + 4)
{
    this->rows = rows;
    this->cols = cols;
    this->cell_w = cell_w;
    this->cell_h = cell_h;
    total_w = cols * (cell_w) + 4;
    total_h = rows * (cell_h) + 4;

    drawBackground();
    drawFrame();
}

Table::Table(INT32 cell_w, INT32 cell_h, UINT32 rows, UINT32 cols, bool doBackground) : CSuperImage(cols * (cell_w) + 4, rows * (cell_h) + 4)
{
    this->rows = rows;
    this->cols = cols;
    this->cell_w = cell_w;
    this->cell_h = cell_h;
    total_w = cols * (cell_w) + 4;
    total_h = rows * (cell_h) + 4;

    if(doBackground) drawBackground();
    drawFrame();
}

void Table::drawBackground()
{
    addImage("popup_pane1_dark.png", {0, 0, total_w, total_h});
}

void Table::drawFrame()
{
    for(INT32 row = 0;row <= rows;row++)
    {
        INT32 y_offset = row * (cell_h);
        addImage("text_line2.png", {0, y_offset, total_w, 4});
    }
    for(INT32 col = 0;col <= cols;col++)
    {
        INT32 x_offset = col * (cell_w);
        addImage("text_line3.png", {x_offset, 0, 4, total_h});
    }
}

Table::~Table()
{
    ;
}

//=====================================================================================================================

Box::Box(INT32 w, INT32 h) : CSuperImage(w, h)
{
    drawBackground();
    drawFrame();
}

Box::~Box()
{
    ;
}

void Box::drawBackground()
{
    addImage("popup_pane1_dark.png", {0, 0, w,  h});
}

void Box::drawFrame()
{
    addImage("text_line2.png", {0, 0, w, 4});
    addImage("text_line2.png", {0, h-4, w, 4});
    addImage("text_line3.png", {0, 0, 4, h});
    addImage("text_line3.png", {w-4, 0, 4, h});
}

//=====================================================================================================================

MonsterList::MonsterList(INT32 row_w, INT32 row_h, INT32 rows, INT32 gap, MainMenu *pMenuObj) : CSuperImage(40+row_w, (row_h+gap)*rows)
{
    this->rows = rows;
    this->gap = gap;
    this->row_w = row_w;
    this->row_h = row_h;

    this->pMenuObj = pMenuObj;

    UIComponent::mEventListeners->at(EventManager::EVENT_LISTENER_MOUSEWHEEL)->attach(this);
    UIComponent::mEventListeners->at(EventManager::EVENT_LISTENER_MOUSECLICK)->attach(this);
    UIComponent::mEventListeners->at(EventManager::EVENT_LISTENER_MOUSEMOTION)->attach(this);

    setTopMonsterID(pMenuObj->monster_id);
}

MonsterList::~MonsterList()
{
    ;
}

void MonsterList::updateTexture()
{
    reset();

    //UINT16 next_monster_id = top_monster_id;

    const static std::string base_path = "";
    const static std::string normal_paths[2] = {"popup2_side1.png", "popup2_side2.png"};
    const static std::string focus_paths[2] = {"popup2_side1_focus2.png", "popup2_side2_focus2.png"};

    std::string path_sides;
    std::string path_middle;

    for(INT32 i = 0;i < rows;i++)    
    { 
        UINT16 monster_id = vMonsterIDs.at(i);

        path_sides =  base_path + ((i == row_focus) ? focus_paths[0] : normal_paths[0]);
        path_middle = base_path + ((i == row_focus) ? focus_paths[1] : normal_paths[1]);

        addImage(path_sides.c_str(), {0, (row_h+gap)*i, 20, row_h});
        addImage(path_middle.c_str(), {20, (row_h+gap)*i, row_w-40, row_h});
        addImage(path_sides.c_str(), {20+row_w-40, (row_h+gap)*i, 20, row_h}, FLIP_HORIZONTAL | FLIP_VERTICAL);        
                
        //addImage("iconbase_blue.png", {20, (row_h+gap)*i+5+4, 40, 40});              
        addImage("iconbase_blue.png", {20, (row_h+gap)*i+((row_h - 40) / 2), 40, 40});              
        
        UINT32 monster_size = pMenuObj->getMonsterSize(monster_id);                
        //addImage(pMenuObj->getIconPathFromID(monster_id).c_str(), {20, (row_h+gap)*i+5+4, 0, 0}, {0, 0, 40, 40});  //only show top tile
        addImage(pMenuObj->getIconPathFromID(monster_id).c_str(), {20, (row_h+gap)*i+((row_h - 40) / 2), 0, 0}, {0, 0, 40, 40});  //only show top tile

        MonsterDatabaseEntry *pMonster = Database::getInstance()->Monsters.getByID(monster_id);
        addText((WCHAR *)pMonster->name, {80, (row_h+gap)*i+5+20, 200, 40}, 20, 250);
    }
}

void MonsterList::setTopMonsterID(UINT16 monster_id)
{
    this->top_monster_id = monster_id;

    vMonsterIDs.clear();

    UINT16 next_monster_id = top_monster_id;
    for(INT32 i = 0;i < rows;i++)
    {        
        vMonsterIDs.push_back(next_monster_id);
        next_monster_id = pMenuObj->getNextMonsterID(next_monster_id);
    }

    updateTexture();
}

void MonsterList::onClick()
{
    printf("Now displaying Monster ID 0x%04dX (%d)\n", vMonsterIDs.at(row_focus), row_focus);
    pMenuObj->loadMonsterInfo(vMonsterIDs.at(row_focus));
}

void MonsterList::update(SDL_Event *pEvent)
{    
    INT32 x, y;
    SDL_GetMouseState(&x, &y);     
    if(!isCoordInside(x, y, rect) || !isVisible())  //if the wheel was scrolled **AND** the mouse is on the button
    {
        return;
    }    

    UINT32 event_type = pEvent->type;
    if(event_type == SDL_MOUSEMOTION)
    {        
        row_focus = (y - this->y) / (row_h+gap);

        if(row_focus != last_row_focus)
        {
            updateTexture();
        }

        last_row_focus = row_focus;        
    }
    else if(event_type == SDL_MOUSEBUTTONDOWN)
    {
        ;
    }
    else if(event_type == SDL_MOUSEBUTTONUP)
    {        
        onClick();
    }
    else if(event_type == SDL_MOUSEWHEEL)
    {
        UINT16 next_monster_id = top_monster_id;    //if the conditionals dont evaluate to true, then default to same monster
        INT32 isGoingUp = pEvent->wheel.y > 0;
        if(isGoingUp)
        {                
            if(top_monster_id > pMenuObj->monster_id_first) //if monster shown at the top is monster ID 1, then don't scroll
            {
                next_monster_id = pMenuObj->getPrevMonsterID(top_monster_id);
            }
        }
        else
        {        
            UINT16 bottom_monster_id = next_monster_id;
            for(INT32 i = 0;i < rows;i++)    //check if the 7th monster from the current one is the last monster or not
            {
                bottom_monster_id = pMenuObj->getNextMonsterID(bottom_monster_id);
                if(!bottom_monster_id) break;   //last monster id reached
            }
            if(bottom_monster_id != 0)   //scroll down if there are 7 more monsters to show
            {
                next_monster_id = pMenuObj->getNextMonsterID(top_monster_id);
            }
        }
        setTopMonsterID(next_monster_id);
    }    
}

//=====================================================================================================================

TraitList::TraitList(INT32 row_w, INT32 row_h, INT32 rows, INT32 gap, MainMenu *pMenuObj, UINT16 top_trait_id) : CSuperImage(40+row_w, (row_h+gap)*rows)
{
    this->rows = rows;
    this->gap = gap;
    this->row_w = row_w;
    this->row_h = row_h;

    this->pMenuObj = pMenuObj;

    UIComponent::mEventListeners->at(EventManager::EVENT_LISTENER_MOUSEWHEEL)->attach(this);
    UIComponent::mEventListeners->at(EventManager::EVENT_LISTENER_MOUSECLICK)->attach(this);
    UIComponent::mEventListeners->at(EventManager::EVENT_LISTENER_MOUSEMOTION)->attach(this);

    //setTopTraitID(top_trait_id);

    Database *pDb = Database::getInstance();
    LINE();
    printf("Trait db size: %d entries\n", pDb->Traits.getNumEntries());
    printf("Trait id 0: length %d\n", wcslen(pDb->Traits.getByID(2)->name));
    LINE();
}

TraitList::~TraitList()
{
    ;
}

void TraitList::updateTexture()
{
    reset();    

    const static std::string base_path = "";
    const static std::string normal_paths[2] = {"popup2_side1.png", "popup2_side2.png"};
    const static std::string focus_paths[2] = {"popup2_side1_focus2.png", "popup2_side2_focus2.png"};

    std::string path_sides;
    std::string path_middle;

    for(INT32 i = 0;i < rows;i++)    
    { 
        UINT16 monster_id = vTraitIDs.at(i);

        path_sides =  base_path + ((i == row_focus) ? focus_paths[0] : normal_paths[0]);
        path_middle = base_path + ((i == row_focus) ? focus_paths[1] : normal_paths[1]);

        addImage(path_sides.c_str(), {0, (row_h+gap)*i, 20, row_h});
        addImage(path_middle.c_str(), {20, (row_h+gap)*i, row_w-40, row_h});
        addImage(path_sides.c_str(), {20+row_w-40, (row_h+gap)*i, 20, row_h}, FLIP_HORIZONTAL | FLIP_VERTICAL);        
                
        //addImage("iconbase_blue.png", {20, (row_h+gap)*i+5+4, 40, 40});              
        addImage("iconbase_blue.png", {20, (row_h+gap)*i+((row_h - 40) / 2), 40, 40});              
        
        UINT32 monster_size = pMenuObj->getMonsterSize(monster_id);                
        //addImage(pMenuObj->getIconPathFromID(monster_id).c_str(), {20, (row_h+gap)*i+5+4, 0, 0}, {0, 0, 40, 40});  //only show top tile
        addImage(pMenuObj->getIconPathFromID(monster_id).c_str(), {20, (row_h+gap)*i+((row_h - 40) / 2), 0, 0}, {0, 0, 40, 40});  //only show top tile

        MonsterDatabaseEntry *pMonster = Database::getInstance()->Monsters.getByID(monster_id);
        addText((WCHAR *)pMonster->name, {80, (row_h+gap)*i+5+20, 200, 40}, 20, 250);
    }
}

void TraitList::setTopTraitID(UINT16 trait_id)
{
    this->top_trait_id = trait_id;

    vTraitIDs.clear();

    UINT16 next_trait_id = top_trait_id;
    for(INT32 i = 0;i < rows;i++)
    {        
        vTraitIDs.push_back(next_trait_id);
        next_trait_id = pMenuObj->getNextMonsterID(next_trait_id);
    }

    updateTexture();
}

void TraitList::onClick()
{
    printf("Now displaying Monster ID 0x%04dX (%d)\n", vTraitIDs.at(row_focus), row_focus);
    pMenuObj->loadMonsterInfo(vTraitIDs.at(row_focus));
}

void TraitList::update(SDL_Event *pEvent)
{    
    INT32 x, y;
    SDL_GetMouseState(&x, &y);     
    if(!isCoordInside(x, y, rect) || !isVisible())  //if the wheel was scrolled **AND** the mouse is on the button
    {
        return;
    }    

    UINT32 event_type = pEvent->type;
    if(event_type == SDL_MOUSEMOTION)
    {        
        row_focus = (y - this->y) / (row_h+gap);

        if(row_focus != last_row_focus)
        {
            updateTexture();
        }

        last_row_focus = row_focus;        
    }
    else if(event_type == SDL_MOUSEBUTTONDOWN)
    {
        ;
    }
    else if(event_type == SDL_MOUSEBUTTONUP)
    {        
        onClick();
    }
    else if(event_type == SDL_MOUSEWHEEL)
    {
        UINT16 next_monster_id = top_trait_id;    //if the conditionals dont evaluate to true, then default to same monster
        INT32 isGoingUp = pEvent->wheel.y > 0;
        if(isGoingUp)
        {                
            if(top_trait_id > pMenuObj->monster_id_first) //if monster shown at the top is monster ID 1, then don't scroll
            {
                next_monster_id = pMenuObj->getPrevMonsterID(top_trait_id);
            }
        }
        else
        {        
            UINT16 bottom_monster_id = next_monster_id;
            for(INT32 i = 0;i < rows;i++)    //check if the 7th monster from the current one is the last monster or not
            {
                bottom_monster_id = pMenuObj->getNextMonsterID(bottom_monster_id);
                if(!bottom_monster_id) break;   //last monster id reached
            }
            if(bottom_monster_id != 0)   //scroll down if there are 7 more monsters to show
            {
                next_monster_id = pMenuObj->getNextMonsterID(top_trait_id);
            }
        }
        setTopTraitID(next_monster_id);
    }    
}

//=====================================================================================================================

Cursor::Cursor() : CImage("cursor1.png")
{
    UIComponent::mEventListeners->at(EventManager::EVENT_LISTENER_MOUSEMOTION)->attach(this);
}

Cursor::~Cursor()
{
    ;
}

void Cursor::update(SDL_Event *pEvent)
{
    INT32 rel_x, rel_y;
    INT32 new_x, new_y;

    SDL_GetMouseState(&new_x, &new_y);
    rel_x = pEvent->motion.xrel;
    rel_y = pEvent->motion.yrel;

    //hide if off screen
    if(new_x <= 0 && rel_x < 0) setVisible(false);
    else if(new_y <= 0 && rel_y < 0) setVisible(false);
    else setVisible(true);    

    setPosition(new_x, new_y);
}

//=====================================================================================================================

DebugInfo::DebugInfo() : CSuperImage(600, 300)
{
    UIComponent::mEventListeners->at(EventManager::EVENT_LISTENER_MOUSEMOTION)->attach(this);
}

DebugInfo::~DebugInfo()
{
    ;
}

void DebugInfo::update(SDL_Event *pEvent)
{
    INT32 x, y;
    SDL_GetMouseState(&x, &y);

    reset();

    WCHAR wstr[64];
    snwprintf(wstr, sizeof(wstr), L"MOUSE (X, Y): (%d, %d)", x, y);

    addText(wstr, {0, 0, 0, 0}, 25, DEBUG_INFO_WIDTH);
}

//=====================================================================================================================

MainMenu::MainMenu()
{   
    monster_id = 0x20;
    //monster_id = 690;

    initComponents();
        
    loadMonsterInfo(monster_id);
}

MainMenu::~MainMenu()
{
    ;    
}

std::string MainMenu::getIconPathFromID(UINT16 id)
{
    std::stringstream icon_path;
    //icon_path << "../ROM/raw/romfs/data/MonsterIcon/" << "ic_" << std::setfill('0') << std::setw(4) << id << ".bclim";
    icon_path << "ic_" << std::setfill('0') << std::setw(4) << id << ".bclim";
    return icon_path.str();
}

UINT16 MainMenu::getNextMonsterID(UINT16 id)
{    
    Database *pDb = Database::getInstance();
    MonsterDatabaseEntry *pMonster;

    std::wstring name;
    UINT16 i = 0;
    UINT16 next_id;

    do
    {
        next_id = id + ++i;
        if(next_id > monster_id_last)  //reached last monster ID
        {
            return 0;   //return 0, and invalid ID
        }
        pMonster = pDb->Monsters.getByID(next_id);
        name = std::wstring((const WCHAR *)pMonster->name);
    }while((name == L""));  //if the monster for this entry exists, there will be a name

    return next_id;
}

UINT16 MainMenu::getPrevMonsterID(UINT16 id)
{    
    Database *pDb = Database::getInstance();
    MonsterDatabaseEntry *pMonster;

    std::wstring name;
    UINT16 i = 0;
    UINT16 next_id;

    do
    {
        next_id = id + --i;
        if(next_id < monster_id_first)  //could not find next monster
        {
            return 0;
        }
        pMonster = pDb->Monsters.getByID(next_id);
        name = std::wstring((const WCHAR *)pMonster->name);
    }while((name == L""));

    return next_id;
}

stats::Size MainMenu::getMonsterSize(UINT16 id)
{    
    switch(Database::getInstance()->Monsters.getByID(id)->size)
    {
        case 0: //small            
            return stats::NORMAL;   //NORMAL instead of SMALL so that it's not 0
            break;
        case 1: case 2: //normal
            return stats::NORMAL;
            break;
        case 3: case 4: case 5: //mega
            return stats::MEGA;
            break;
        case 6: case 7: case 8: //giga
            return stats::GIGA;
            break;
        default:         
            LOG_ERROR("Invalid value for pMonster->size");
            fatalError("could not resolve monster size");
            break;
    }
    return (stats::Size)NULL;    //should never reach here
}

void MainMenu::initComponents()
{
    //=====================================================================================================================
    // BACKGROUND
    //=====================================================================================================================

    CImage *bg = new CImage("bg1.png");
    bg->setPosition(0, 0);
    bg->setSize(UIManager::DEFAULT_WINDOW_WIDTH, UIManager::DEFAULT_WINDOW_HEIGHT);
    addComponent(bg);
    
    CImage *top_part1 = new CImage("top_text_part1.png");
    top_part1->setPosition(0, 0);
    addComponent(top_part1);

    CImage *top_part2 = new CImage("top_text_part2.png");
    top_part2->setPosition(top_part1->getRect()->w, 0);
    top_part2->setSize(UIManager::DEFAULT_WINDOW_WIDTH - top_part1->getRect()->w, top_part2->getRect()->h);
    addComponent(top_part2);

    CImage *bottom_part = new CImage("top_text_part2.png");
    bottom_part->flip(FLIP_VERTICAL);
    bottom_part->setPosition(0, UIManager::DEFAULT_WINDOW_HEIGHT - bottom_part->getRect()->h);
    bottom_part->setSize(UIManager::DEFAULT_WINDOW_WIDTH, bottom_part->getRect()->h);
    addComponent(bottom_part);

    CText *title = new CText(L"MONSTER", 40);
    title->setPosition(50, 50);
    title->setSize(250, 40);
    addComponent(title);

    //=====================================================================================================================
    // MONSTER WINDOW
    //=====================================================================================================================

    Window *window = new Window(1000, 600);
    window->setPosition(UIManager::DEFAULT_WINDOW_WIDTH-25-window->getRect()->w, 100);
    addComponent(window);    

    CText *name = new CText(L"NAME:", 25);
    name->setRelativePosition(window, 60, 60);    
    addComponent(name);

    monster_info.name = new CText(DEFAULT_TEXT, 25);
    monster_info.name->setRelativePosition(window, 150, 60);        
    addComponent(monster_info.name);    

    monster_info.rank = new CText(DEFAULT_TEXT, 25);
    monster_info.rank->setRelativePosition(window, 500, 60);
    addComponent(monster_info.rank);

    monster_info.id = new CText(DEFAULT_TEXT, 25);
    monster_info.id->setRelativePosition(window, 645, 60);
    addComponent(monster_info.id);
    
    Line *name_line = new Line(350);
    name_line->setRelativePosition(name, -10, 22);
    addComponent(name_line);

    CText *rank = new CText(L"RANK:", 25);
    rank->setRelativePosition(window, 430, 60);    
    addComponent(rank);

    Line *rank_line = new Line(130);
    rank_line->setRelativePosition(rank, -10, 22);
    addComponent(rank_line);

    CText *id = new CText(L"ID:0x", 25);    
    id->setRelativePosition(window, 580, 60);      
    addComponent(id);

    Line *id_line = new Line(180);
    id_line->setRelativePosition(id, -10, 22);
    addComponent(id_line);

    monster_info.icon = new CSuperImage(ICON_BASE_LENGTH, ICON_BASE_LENGTH * 3); //default icon image
    monster_info.icon->setRelativePosition(window, 50, 120);    
    addComponent(monster_info.icon);

    CText *stats = new CText(L"ステータス:", 20);
    stats->setRelativePosition(window, 150, 120);
    addComponent(stats);
    
    Line *stats_line = new Line(130);
    stats_line->setRelativePosition(stats, -10, 18);
    addComponent(stats_line);

    CText *traits = new CText(L"特性:", 20);
    traits->setRelativePosition(window, 520, 120);    
    addComponent(traits);

    CText *size_trait = new CText(DEFAULT_TEXT, 20);
    monster_info.size_trait = size_trait;
    size_trait->setRelativePosition(traits, 0, 30);    
    addComponent(size_trait);

    for(INT32 i = 0;i < MAX_MONSTER_TRAITS;i++)
    {
        CText *trait = new CText(DEFAULT_TEXT, 20);
        monster_info.traits[i] = trait;
        trait->setRelativePosition(size_trait, 0, 30 * (i+1));
        trait->setVisible(false);
        addComponent(trait);
    }

    Line *trait_line = new Line(100);
    trait_line->setRelativePosition(traits, -10, 18);
    addComponent(trait_line);

    CText *resistance = new CText(L"耐性:", 20);
    resistance->setRelativePosition(traits, 220, 0);    
    addComponent(resistance);

    Line *resistance_line = new Line(100);
    resistance_line->setRelativePosition(resistance, -10, 18);
    addComponent(resistance_line);

    CImage *resistance_table_bg = new CImage("popup_pane1_dark.png");
    resistance_table_bg->setRelativePosition(resistance_line, 0, 20);
    resistance_table_bg->setSize(200, 350);
    addComponent(resistance_table_bg);

    Table *resistance_table = new Table(RESISTANCE_TABLE_CELL_WIDTH, RESISTANCE_TABLE_CELL_HEIGHT, 14, 4, false);
    resistance_table->setRelativePosition(resistance_line, 0, 20);

    for(INT32 i = 0;i < NUM_RESISTANCE_TYPES;i++)
    {
        CText *resistance_name = new CText(DEFAULT_TEXT, 15);
        monster_info.resistance[i] = resistance_name;
        resistance_name->setRelativePosition(resistance_table, 5+(i / 14) * (resistance_table->cell_w*2), 5+(i%14) * resistance_table->cell_h);
        addComponent(resistance_name);

        CImage *resistance_value_bg;
        std::string img_path = "res_weak.png";  //default
        resistance_value_bg = new CImage(img_path.c_str());
        resistance_value_bg->setRelativePosition(resistance_table, resistance_table->cell_w + 4 + (i / 14) * (resistance_table->cell_w*2), (i%14) * resistance_table->cell_h);
        resistance_value_bg->setSize(resistance_table->cell_w, resistance_table->cell_h);
        monster_info.resistance_values_bg[i] = resistance_value_bg;
        addComponent(monster_info.resistance_values_bg[i]);

        CText *resistance_value = new CText(DEFAULT_TEXT, 15);
        monster_info.resistance_values[i] = resistance_value;
        resistance_value->setRelativePosition(resistance_table, resistance_table->cell_w + 4 + 8 + (i/14) * (resistance_table->cell_w*2), 5+(i%14) * resistance_table->cell_h);
        resistance_value->setSize(resistance_table->cell_w, resistance_table->cell_h);
        addComponent(resistance_value);
    }
    addComponent(resistance_table);

    Table *name_table = new Table(90, 35, 6, 1);
    name_table->setRelativePosition(window, 140, 160);
    addComponent(name_table);

    Table *stats_table = new Table(60, 35, 6, 4);
    stats_table->setRelativePosition(name_table, 90, 0);
    addComponent(stats_table);

    CText *hp = new CText(L" 最大HP", 20);
    hp->setRelativePosition(name_table, 8, 10);
    addComponent(hp);
    monster_info.max_hp_value = new CText(DEFAULT_TEXT, 20);
    monster_info.max_hp_value->setRelativePosition(hp, 90, 0);
    addComponent(monster_info.max_hp_value);    

    CText *mp = new CText(L" 最大MP", 20);
    mp->setRelativePosition(hp, 0, 35);
    addComponent(mp);
    monster_info.max_mp_value = new CText(DEFAULT_TEXT, 20);
    monster_info.max_mp_value->setRelativePosition(mp, 100, 0);
    addComponent(monster_info.max_mp_value);    

    CText *atk = new CText(L" 攻撃力", 20);
    atk->setRelativePosition(mp, 0, 35);
    addComponent(atk);
    monster_info.max_atk_value = new CText(DEFAULT_TEXT, 20);
    monster_info.max_atk_value->setRelativePosition(atk, 100, 0);
    addComponent(monster_info.max_atk_value);    

    CText *def = new CText(L" 守備力", 20);
    def->setRelativePosition(atk, 0, 35);
    addComponent(def);
    monster_info.max_def_value = new CText(DEFAULT_TEXT, 20);
    monster_info.max_def_value->setRelativePosition(def, 100, 0);
    addComponent(monster_info.max_def_value);    

    CText *spd = new CText(L"すばやさ", 20);
    spd->setRelativePosition(def, 0, 35);
    addComponent(spd);
    monster_info.max_spd_value = new CText(DEFAULT_TEXT, 20);
    monster_info.max_spd_value->setRelativePosition(spd, 100, 0);
    addComponent(monster_info.max_spd_value);    

    CText *intl = new CText(L"かしこさ", 20);
    intl->setRelativePosition(spd, 0, 35);
    addComponent(intl);
    monster_info.max_int_value = new CText(DEFAULT_TEXT, 20);
    monster_info.max_int_value->setRelativePosition(intl, 100, 0);
    addComponent(monster_info.max_int_value);    


    CText *skill = new CText(L"スキル:", 20);
    skill->setRelativePosition(window, 150, 400);
    addComponent(skill);
    Line *skill_line = new Line(300);
    skill_line->setRelativePosition(skill, -10, 18);
    addComponent(skill_line);
    monster_info.skill = new CText(DEFAULT_TEXT, 20);
    monster_info.skill->setRelativePosition(skill, 80, 0);
    addComponent(monster_info.skill);    
    
    //=====================================================================================================================
    // SEARCH RESULT WINDOW
    //=====================================================================================================================

    Window *result_window = new Window(450, 700, Window::WINDOW_TYPE_SQUARE, true, L"SEARCH RESULTS");
    result_window->setPosition(25, 120);
    addComponent(result_window);

    Box *monster_list_box = new Box(410, 500);
    monster_list_box->setRelativePosition(result_window, 20, 100);
    addComponent(monster_list_box);

    /*monster_list = new MonsterList(350, 54, 7, 10, this);
    monster_list->setRelativePosition(monster_list_box, 10, 30);*/
    monster_list = new MonsterList(350, 60, 6, 10, this);
    monster_list->setRelativePosition(monster_list_box, 10, (monster_list_box->getRect()->h - monster_list->getRect()->h) / 2);
    addComponent(monster_list);

    GotoSearchButton *goto_search_button = new GotoSearchButton("test_button3.png", "test_button2.png", this);
    goto_search_button->setRelativePosition(result_window, 150, 620);
    goto_search_button->setText(L"SEARCH", 25, SDL_COLOR_WHITE);
    addComponent(goto_search_button);

    //=====================================================================================================================
    // SEARCH
    //=====================================================================================================================

    CSuperImage *filter_dark = new CSuperImage(UIManager::DEFAULT_WINDOW_WIDTH, UIManager::DEFAULT_WINDOW_HEIGHT);
    filter_dark->addImage("filter3.png", {0, 0, UIManager::DEFAULT_WINDOW_WIDTH, UIManager::DEFAULT_WINDOW_HEIGHT});
    group_search.add(filter_dark);
    addComponent(filter_dark);

    Window *search_window = new Window(1000, 600, Window::WINDOW_TYPE_SQUARE, true, L"SEARCH");
    search_window->setPosition(300, 150);
    group_search.add(search_window);
    addComponent(search_window);

    SearchButton *search_button = new SearchButton(this);
    search_button->setRelativePosition(search_window, 100, 100);
    group_search.add(search_button);
    addComponent(search_button);

    //TraitList *trait_list = new TraitList(100, 100, 5, 5, this, 1);

    group_search.setVisible(false); //hidden by default

    //=====================================================================================================================
    // DEBUG INFO
    //=====================================================================================================================

#ifdef DEBUG
    Window *debug_info_window = new Window(600, 200, Window::WINDOW_TYPE_SQUARE, true, L"DEBUG");
    debug_info_window->setPosition(0, 0);
    addComponent(debug_info_window);

    DebugInfo *debug_info = new DebugInfo();
    debug_info->setRelativePosition(debug_info_window, 20, 100);
    addComponent(debug_info);

    group_debug_info.add(debug_info_window);
    group_debug_info.add(debug_info);

    TestButton *toggle_debug_button = new TestButton("test_button3.png", "test_button1.png", this);
    toggle_debug_button->setText(L"DEBUG", 25, SDL_COLOR_WHITE);
    toggle_debug_button->setPosition(800, 50);
    addComponent(toggle_debug_button);
#endif
    //=====================================================================================================================
    // FILTERS & MISC
    //=====================================================================================================================

    Cursor *cursor = new Cursor();
    addComponent(cursor);

    CSuperImage *filter_screen = new CSuperImage(UIManager::DEFAULT_WINDOW_WIDTH, UIManager::DEFAULT_WINDOW_HEIGHT);
    for(INT32 i = 0;i < (UIManager::DEFAULT_WINDOW_HEIGHT/100);i++)
    {
        filter_screen->addImage("filter1.png", {0, i*100, UIManager::DEFAULT_WINDOW_WIDTH, 100});
    }   
    addComponent(filter_screen);    

    CSuperImage *filter_blur = new CSuperImage(UIManager::DEFAULT_WINDOW_WIDTH, UIManager::DEFAULT_WINDOW_HEIGHT);
    filter_blur->addImage("filter2.png", {0, 0, UIManager::DEFAULT_WINDOW_WIDTH, 100});
    filter_blur->addImage("filter2.png", {0, UIManager::DEFAULT_WINDOW_HEIGHT-100, UIManager::DEFAULT_WINDOW_WIDTH, 100}, FLIP_VERTICAL);
    addComponent(filter_blur);    
}

void MainMenu::buttonCallback()
{
    group_debug_info.setVisible(!group_debug_info.isVisible());    
}

void MainMenu::gotoSearchButtonCallback()
{
    group_search.setVisible(true);
}

void MainMenu::searchButtonCallback()
{
    group_search.setVisible(false);
}

void MainMenu::loadMonsterInfo(UINT16 monster_id)
{
    Database *pDb = Database::getInstance();
    MonsterDatabaseEntry *pMonster = pDb->Monsters.getByID(monster_id);
    SkillDatabaseEntry *pSkill = pDb->Skills.getByID(pMonster->skill);    

    const WCHAR *types[] = {L"", L"スライム", L"ドラゴン", L"自然", L"魔獣", L"物質", L"悪魔", L"ゾンビ", L"???"};
    const WCHAR *ranks[] = {L"", L"F", L"E", L"D", L"C", L"B", L"A", L"S", L"SS"};    

    monster_info.name->setText(((WCHAR *)pMonster->name));  //don't worry there's a null-terminator
    monster_info.rank->setText((ranks[pMonster->rank]));    
    monster_info.id->setText(toHexWString16(pMonster->id).c_str());
    ;   //fix construct.cpp and monster.h so that size member is a value from 0-3 (s, S, M, G)
    monster_info.max_hp_value->setText(std::to_wstring(pMonster->max_hp).c_str());
    monster_info.max_mp_value->setText(std::to_wstring(pMonster->max_mp).c_str());
    monster_info.max_atk_value->setText(std::to_wstring(pMonster->max_atk).c_str());
    monster_info.max_def_value->setText(std::to_wstring(pMonster->max_def).c_str());
    monster_info.max_spd_value->setText(std::to_wstring(pMonster->max_spd).c_str());
    monster_info.max_int_value->setText(std::to_wstring(pMonster->max_int).c_str());
    monster_info.skill->setText(pSkill->name);

    UINT16 size_trait_id = 0;
    stats::Size monster_size;
    switch(pMonster->size)
    {
        case 0: //small
            size_trait_id = 0x108;
            monster_size = stats::NORMAL;   //NORMAL instead of SMALL so that it's not 0
            break;
        case 1: case 2: //normal
            size_trait_id = 0x107;
            monster_size = stats::NORMAL;
            break;
        case 3: case 4: case 5: //mega
            size_trait_id = 0x1C;
            monster_size = stats::MEGA;
            break;
        case 6: case 7: case 8: //giga
            size_trait_id = 0x1D;
            monster_size = stats::GIGA;
            break;
        default:         
            LOG_ERROR("Invalid value for pMonster->size");
            fatalError("could not resolve size trait ID");   
            break;
    }

    monster_info.icon->reset();
    for(INT32 i = 0;i < monster_size;i++)
    {
        monster_info.icon->addImage("iconbase_blue.png", {0, i * ICON_BASE_LENGTH, ICON_BASE_LENGTH, ICON_BASE_LENGTH});
    }
    monster_info.icon->addImage(getIconPathFromID(monster_id).c_str(), {0, 0, ICON_BASE_LENGTH, monster_size * ICON_BASE_LENGTH});
    
    for(INT32 i = 0;i < MAX_MONSTER_TRAITS;i++)
    {
        monster_info.traits[i]->setVisible(false);
    }

    monster_info.size_trait->setText(pDb->Traits.getByID(size_trait_id)->name);    
    for(INT32 i = 0;i < MAX_MONSTER_TRAITS;i++)
    {
        if(!pMonster->traits[i]) break;
        CText *trait = monster_info.traits[i];        
        trait->setText(pDb->Traits.getByID(pMonster->traits[i])->name);
        trait->setVisible(true);
    }

    for(INT32 i = 0;i < NUM_RESISTANCE_TYPES;i++)
    {                
        INT32 type = resistance::ORDER[i];

        resistance::ResistanceValue val = (resistance::ResistanceValue)Database::getInstance()->Monsters.getByID(monster_id)->resistance[type];        
        std::string img_path = "";        
        switch(val)
        {
            case resistance::WEAK:
                img_path += "res_weak.png";
                break;
            case resistance::NORMAL:
                img_path += "res_normal.png";                
                break;
            case resistance::LIGHT:
                img_path += "res_light.png";
                break;
            case resistance::HALF:
                img_path += "res_half.png";
                break;
            case resistance::ALMOST:
                img_path += "res_almost.png";
                break;
            case resistance::IMMUNE:
                img_path += "res_immune.png";
                break;
            case resistance::HEAL:
                img_path += "res_heal.png";
                break;
            case resistance::REFLECT:
                img_path += "res_reflect.png";
                break;
            case resistance::NLHI:
                img_path += "res_nlhi.png";
                break;
            case resistance::NHAI:
                img_path += "res_nhai.png";
                break;
            default:
                LOG_ERROR("unknown resistance value");
                fatalError("invalid resistance value");
                break;
        }                

        monster_info.resistance[i]->setText(resistance::TYPE_NAMES[type]);
        bool tooLong = (wcslen(resistance::TYPE_NAMES[type]) > 3);
        if(tooLong)
        {
            monster_info.resistance[i]->setSize(RESISTANCE_TABLE_CELL_WIDTH-4-2, RESISTANCE_TABLE_CELL_HEIGHT-10);
        }
        SDL_Rect *old_rect = monster_info.resistance[i]->getRect();        
                
        monster_info.resistance_values[i]->setText(resistance::VALUES[val]);          

        //make text skinnier to fit cell if longer than 3 characters
        tooLong = (wcslen(resistance::VALUES[val]) > 3);
        if(tooLong) 
        {            
            monster_info.resistance_values[i]->setSize(RESISTANCE_TABLE_CELL_WIDTH-4, RESISTANCE_TABLE_CELL_HEIGHT-10);
        }        
        monster_info.resistance_values[i]->setRelativePosition(monster_info.resistance[i], RESISTANCE_TABLE_CELL_WIDTH+(tooLong ? 0 : 6), 0);        
        monster_info.resistance_values_bg[i]->setImage(img_path.c_str());        
        monster_info.resistance_values_bg[i]->setSize(RESISTANCE_TABLE_CELL_WIDTH, RESISTANCE_TABLE_CELL_HEIGHT);        
    }
}