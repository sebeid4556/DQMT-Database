#include<stdio.h>
#include<stdlib.h>

#define SDL_MAIN_HANDLED
#include<SDL2/SDL.h>

#include"util/util.h"
#include"database/database.h"
#include"database/construct.h"

#include<string.h>
#include"database/binj.h"
#include<locale.h>
#include<wchar.h>
#include<iostream>
#include"ui/test.hpp"

void showMonsterInfo(MonsterDatabaseEntry *pMonster)
{
    printf("ID: %d\n", pMonster->id);
    printf("RANK #: %d\n", pMonster->rank_number);
    printf("SPECIES: %d\n", pMonster->species);
    printf("RANK: %d\n", pMonster->rank);
    printf("SIZE: %d\n", pMonster->size);
    printf("HP: %d\n", pMonster->max_hp);
    printf("MP: %d\n", pMonster->max_mp);
    printf("ATK: %d\n", pMonster->max_atk);
    printf("DEF: %d\n", pMonster->max_def);
    printf("SPD: %d\n", pMonster->max_spd);
    printf("INT: %d\n", pMonster->max_int);    
    printf("SKILL: %d\n", pMonster->skill);    
}

void lookUpMonster(Database *pDb)
{
    UINT32 id;
    LINE();
    while(true)
    {        
        printf("Enter ID> ");
        scanf("%d", &id);
        showMonsterInfo(pDb->Monsters.getByID((UINT16)id));
        LINE();
    }
}

int main(int argc, char *argv[])
{    
    //constructDatabase();    

    FrameworkTEST();
    //TEST();
    return 0;

    Database Db;
    
    lookUpMonster(&Db);    

    return 0;
}