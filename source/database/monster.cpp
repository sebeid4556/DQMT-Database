#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#include"../util/util.h"
#include"monster.h"

const CHAR *kMonstersBinPath = "../data/monsters.bin";

MonsterDatabase::MonsterDatabase()
{        
    UINT32 size;
    UINT8 *pBuffer;

    INT32 r = loadFileIntoBuffer((CHAR *)kMonstersBinPath, &pBuffer, &size);
    if(r != FILE_RET_OK) fatalError(kFileErrorMessages[r], "MonsterDatabase::MonsterDatabase");

    num_entries = size / sizeof(MonsterDatabaseEntry);    

    MonsterDatabaseEntry *pMonsterSrc;
    MonsterDatabaseEntry monsterDst;
    UINT32 offset;

    for(UINT32 i = 0;i < num_entries;i++)
    {
        offset = i * sizeof(MonsterDatabaseEntry);
        pMonsterSrc = (MonsterDatabaseEntry *)(pBuffer + offset);
        memcpy(&monsterDst, pMonsterSrc, sizeof(MonsterDatabaseEntry));
        vMonsters.push_back(monsterDst);
    }
}

UINT32 MonsterDatabase::getNumEntries()
{
    return num_entries;
}

MonsterDatabaseEntry *MonsterDatabase::getByID(UINT16 id)
{
    if(id >= num_entries) return NULL;
    return &vMonsters.at(id);
}