#ifndef DATABASE_DATABASE_H_
#define DATABASE_DATABASE_H_

#include"../util/types.h"
#include"ekt.h"
#include"monster.h"
#include"trait.h"
#include"move.h"
#include"skill.h"

#define NUM_DATABASE_ERRORS 0

const extern CHAR *kDatabaseErrorMessages[NUM_DATABASE_ERRORS];

class Database 
{
    public:
        Database();
        MonsterDatabase Monsters;
        TraitDatabase Traits;
        MoveDatabase Moves;
        SkillDatabase Skills;
    private:
        ;
};

#endif //DATABASE_DATABASE_H_