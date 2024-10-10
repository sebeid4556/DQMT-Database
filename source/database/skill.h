#ifndef DATABASE_SKILL_H_
#define DATABASE_SKILL_H_

#include<vector>

#include"../util/util.h"

#define SKILL_NAME_MAX_LENGTH 0x10
#define SKILL_MAX_MOVES_OR_TRAITS 10

typedef struct
{
    WCHAR name[SKILL_NAME_MAX_LENGTH];
    UINT16 moves[SKILL_MAX_MOVES_OR_TRAITS];
    UINT16 traits[SKILL_MAX_MOVES_OR_TRAITS];
    UINT8 req_sp[SKILL_MAX_MOVES_OR_TRAITS];
}SkillDatabaseEntry;


class SkillDatabase
{
    public:
        SkillDatabase();
        ~SkillDatabase();
        SkillDatabaseEntry *getByID(UINT16 id);
        UINT32 getNumEntries();
    private:
        UINT8 *pBuffer;
        UINT32 size;
        UINT32 num_entries;

        std::vector<SkillDatabaseEntry *> vSkills;
};

#endif // DATABASE_SKILL_H_