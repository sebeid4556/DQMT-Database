#ifndef DATABASE_MOVE_H_
#define DATABASE_MOVE_H_

#include<stdio.h>
#include<vector>

#include"../util/util.h"

#define MAX_MOVE_NAME_LENGTH 0x10
#define MAX_MOVE_HELP_LENGTH 0x40

typedef struct
{
    WCHAR name[MAX_MOVE_NAME_LENGTH];
    WCHAR help[MAX_MOVE_HELP_LENGTH];
}MoveDatabaseEntry;

class MoveDatabase
{
    public:
        MoveDatabase();
        ~MoveDatabase();
        UINT32 getNumEntries();
        MoveDatabaseEntry *getByID(UINT16 id);
    private:
        UINT8 *pBuffer = NULL;
        UINT32 size;
        UINT32 num_entries;
        std::vector<MoveDatabaseEntry *> vMoves;
};

#endif // DATABASE_MOVE_H_