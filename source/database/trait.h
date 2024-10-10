#ifndef DATABASE_TRAIT_H_
#define DATABASE_TRAIT_H_

#include<vector>

#include"../util/util.h"

#define MAX_TRAIT_NAME_LENGTH 0x10
#define MAX_TRAIT_HELP_LENGTH 0x40

#define NUM_TOTAL_TRAITS 292

typedef struct 
{
    WCHAR name[MAX_TRAIT_NAME_LENGTH];
    WCHAR help[MAX_TRAIT_HELP_LENGTH];
}TraitDatabaseEntry;

class TraitDatabase
{
    public:
        TraitDatabase();
        ~TraitDatabase();
        UINT32 getNumEntries();
        TraitDatabaseEntry *getByID(UINT16 id);
    private:
        UINT8 *pBuffer = NULL;
        UINT32 size;
        std::vector<TraitDatabaseEntry *> vTraits;
        UINT32 num_entries;
};

#endif // DATABASE_TRAIT_H_