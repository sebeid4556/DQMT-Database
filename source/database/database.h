#ifndef DATABASE_DATABASE_H_
#define DATABASE_DATABASE_H_

#include"../util/types.h"
#include"ekt.h"
#include"monster.h"
#include"trait.h"
#include"move.h"
#include"skill.h"

class Database 
{
    public:                
        MonsterDatabase Monsters;
        TraitDatabase Traits;
        MoveDatabase Moves;
        SkillDatabase Skills;

        static Database *getInstance();
    private:
        static Database *s_pInstance;

        Database();
        Database(const Database&) = delete;
        Database& operator=(const Database&) = delete;
        virtual ~Database();
};

#endif //DATABASE_DATABASE_H_