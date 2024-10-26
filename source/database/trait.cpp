#include<stdio.h>
#include<stdlib.h>
#include<vector>

#include"trait.h"
#include"../util/util.h"

const CHAR *kTraitBinPath = "../data/traits.bin";

TraitDatabase::TraitDatabase()
{
    INT32 r = loadFileIntoBuffer((CHAR *)kTraitBinPath, &pBuffer, &size);
    if(r != FILE_RET_OK) fatalError(kFileErrorMessages[r], "TraitDatabase::TraitDatabase");

    num_entries = size / sizeof(TraitDatabaseEntry);    

    TraitDatabaseEntry *pTrait;

    for(UINT32 i = 0;i < num_entries;i++)
    {
        pTrait = (TraitDatabaseEntry *)(pBuffer + (sizeof(TraitDatabaseEntry) * i));        
        vTraits.push_back(pTrait);
    }
}

TraitDatabase::~TraitDatabase()
{
    if(pBuffer) free(pBuffer);
}

TraitDatabaseEntry *TraitDatabase::getByID(UINT16 id)
{
    if(id >= vTraits.size()) return NULL;
    return vTraits.at(id);
}