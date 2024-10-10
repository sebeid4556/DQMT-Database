#ifndef DATABASE_MONSTER_H_
#define DATABASE_MONSTER_H_

#include<vector>

#include"../util/types.h"

#define MAX_MONSTER_NAME_LENGTH 0x10
#define MAX_MONSTER_TRAITS 6
#define NUM_RESISTANCE_TYPES 28

typedef struct {
    UINT16 id;
    UINT16 name[MAX_MONSTER_NAME_LENGTH];
    UINT8 size;
    UINT16 rank_number;
    UINT8 rank;
    UINT8 species;
    UINT16 max_hp;
    UINT16 max_mp;
    UINT16 max_atk;
    UINT16 max_def;
    UINT16 max_spd;
    UINT16 max_int;
    UINT16 traits[MAX_MONSTER_TRAITS];
    UINT8 resistance[NUM_RESISTANCE_TYPES];
    UINT8 equippable_weapons;
    UINT16 skill;
    UINT8 levelup_table;
}MonsterDatabaseEntry;

class MonsterDatabase
{
    public:
        MonsterDatabase();
        UINT32 getNumEntries();
        MonsterDatabaseEntry *getByID(UINT16 id);
    private:
        std::vector<MonsterDatabaseEntry> vMonsters;
        UINT32 num_entries;
};

#endif // DATABASE_MONSTER_H_