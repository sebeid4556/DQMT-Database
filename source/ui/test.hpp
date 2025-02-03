#include<stdio.h>
#include<stdlib.h>
#include<wchar.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

#include"../database/binj.h"
#include"../database/database.h"

#include"ui.h"

void createMonsterStatWString(Database *pDb, WCHAR *pOut, UINT16 id)
{    
    MonsterDatabaseEntry *pMonster = pDb->Monsters.getByID(id);        
    const WCHAR *types[] = {L"", L"スライム", L"ドラゴン", L"自然", L"魔獣", L"物質", L"悪魔", L"ゾンビ", L"???"};
    const WCHAR *ranks[] = {L"", L"F", L"E", L"D", L"C", L"B", L"A", L"S", L"SS"};        
    swprintf(pOut, L"NAME: %ls   %ls係   RANK: %ls   位階: %3ld\n==========================================================================================\n\nステータス:\n__________________\n\n  最大HP: %4ld\n\n  最大MP: %4ld\n\n  攻撃力: %4ld\n\n  守備力: %4ld\n\nすばやさ: %4ld\n\nかしこさ: %4ld", 
        pMonster->name,
        types[pMonster->species],
        ranks[pMonster->rank],        
        pMonster->rank_number,
        pMonster->max_hp,
        pMonster->max_mp,
        pMonster->max_atk,
        pMonster->max_def,
        pMonster->max_spd,
        pMonster->max_int        
    );
}

void createMonsterTraitWString(Database *pDb, WCHAR *pOut, UINT16 id)
{
    MonsterDatabaseEntry *pMonster = pDb->Monsters.getByID(id);    
    swprintf(pOut, L"\n\n\n特性:\n__________________\n\n");
    UINT16 size_trait_id = 0;
    switch(pMonster->size)
    {
        case 0:
            size_trait_id = 0x108;
            break;
        case 1: case 2:
            size_trait_id = 0x107;
            break;
        case 3: case 4: case 5:
            size_trait_id = 0x1C;
            break;
        case 6: case 7: case 8:
            size_trait_id = 0x1D;
            break;
        default:            
            break;
    }
    swprintf((pOut + wcslen(pOut)), L"[%3ld] %ls\n\n", size_trait_id, pDb->Traits.getByID(size_trait_id)->name);
    for(UINT32 i = 0;i < MAX_MONSTER_TRAITS;i++)
    {
        if(!pMonster->traits[i]) break;
        swprintf((pOut + wcslen(pOut)), L"[%3ld] %ls\n\n", pMonster->traits[i], pDb->Traits.getByID(pMonster->traits[i])->name);        
    }
}

void createMonsterSkillWString(Database *pDb, WCHAR *pOut, UINT16 id)
{
    UINT16 skill_id = pDb->Monsters.getByID(id)->skill;
    SkillDatabaseEntry *pSkill = pDb->Skills.getByID(skill_id);
    swprintf(pOut, L"\n\n\nスキル:\n__________________\n\n[%3ld] %ls\n__________________\n\n", skill_id, pSkill->name);
    UINT16 move, trait;
    UINT8 req_sp;
    for(UINT32 i = 0;i < SKILL_MAX_MOVES_OR_TRAITS;i++)
    {
        move = pSkill->moves[i];
        trait = pSkill->traits[i];
        req_sp = pSkill->req_sp[i];

        //printf("entry (%2d): move=0x%4X, trait=0x%4X, req_sp=%d\n", i, move, trait, req_sp);

        if(move != 0x0000)
        {
            swprintf(pOut + wcslen(pOut), L"[%3ldpt] %ls\n", req_sp, pDb->Moves.getByID(move)->name);
            //swprintf(pOut + wcslen(pOut), L"[%3ld] %ls\n", move, pDb->Moves.getByID(move)->name);
            //swprintf(pOut + wcslen(pOut), L"[特技] %ls\n", pDb->Moves.getByID(move)->name);
        }
        else if(trait != 0x0000)
        {
            swprintf(pOut + wcslen(pOut), L"[%3ldpt] %ls\n", req_sp, pDb->Traits.getByID(trait)->name);
            //swprintf(pOut + wcslen(pOut), L"[%3ld] %ls\n", trait, pDb->Traits.getByID(trait)->name);
            //swprintf(pOut + wcslen(pOut), L"[特性] %ls\n", pDb->Traits.getByID(trait)->name);
        }
        else    //no more moves in this skill
        {
            //printf("This skill has %d entries!\n", i + 1);
            break;
        }
    }
}

void FrameworkTEST()
{
    LINE();
    printf("[+]FRAMEWORK TEST()\n");

    Application App;
    App.run();
}

void TEST()
{        
    FrameworkTEST();
    return;


    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_CreateWindowAndRenderer(1000, 600, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "DQMT - Database");

    TTF_Font *font = TTF_OpenFont("resource/font/KosugiMaru-Regular.ttf", 20);

    Database *Db = Database::getInstance();
    //UINT16 monster_id = 349;
    //UINT16 monster_id = 358;
    UINT16 monster_id = 243;
    //UINT16 monster_id = 1;

    WCHAR wstat[0x100];
    WCHAR wtrait[0x100];
    WCHAR wskill[0x100];
    createMonsterStatWString(Db, wstat, monster_id);
    createMonsterTraitWString(Db, wtrait, monster_id);
    createMonsterSkillWString(Db, wskill, monster_id);    

    SDL_Surface *pStatSurface = TTF_RenderUNICODE_Blended_Wrapped(font, (const Uint16 *)wstat, SDL_Color{255, 255, 255, 255}, 920);
    SDL_Surface *pTraitSurface = TTF_RenderUNICODE_Blended_Wrapped(font, (const Uint16 *)wtrait, SDL_Color{255, 255, 255, 255}, 300);
    SDL_Surface *pSkillSurface = TTF_RenderUNICODE_Blended_Wrapped(font, (const Uint16 *)wskill, SDL_Color{255, 255, 255, 255}, 300);

    SDL_Rect StatRect{40, 20, pStatSurface->w, pStatSurface->h};
    SDL_Rect TraitRect{540, 20, pTraitSurface->w, pTraitSurface->h};
    SDL_Rect SkillRect{250, 20, pSkillSurface->w, pSkillSurface->h};

    SDL_Texture *pStatTexture = SDL_CreateTextureFromSurface(renderer, pStatSurface);
    SDL_Texture *pTraitTexture = SDL_CreateTextureFromSurface(renderer, pTraitSurface);
    SDL_Texture *pSkillTexture = SDL_CreateTextureFromSurface(renderer, pSkillSurface);
    SDL_FreeSurface(pStatSurface);
    SDL_FreeSurface(pTraitSurface);
    SDL_FreeSurface(pSkillSurface);

    SDL_Event event;
    bool done = false;

    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    done = 1;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, pStatTexture, NULL, &StatRect);
        SDL_RenderCopy(renderer, pTraitTexture, NULL, &TraitRect);
        SDL_RenderCopy(renderer, pSkillTexture, NULL, &SkillRect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(pStatTexture);
    SDL_DestroyTexture(pTraitTexture);
    SDL_DestroyTexture(pSkillTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);    

    LINE();
}