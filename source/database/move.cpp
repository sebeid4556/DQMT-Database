#include<stdio.h>
#include<stdlib.h>

#include"../util/util.h"
#include"move.h"

const CHAR *kMoveBinPath = "data/moves.bin";

MoveDatabase::MoveDatabase()
{
    INT32 r = loadFileIntoBuffer((CHAR *)kMoveBinPath, &pBuffer, &size);
    if(r != FILE_RET_OK) fatalError(kFileErrorMessages[r], "TraitDatabase::TraitDatabase");

    num_entries = size / sizeof(MoveDatabaseEntry);    

    MoveDatabaseEntry *pMove;

    for(UINT32 i = 0;i < num_entries;i++)
    {
        pMove = (MoveDatabaseEntry *)(pBuffer + (sizeof(MoveDatabaseEntry) * i));        
        vMoves.push_back(pMove);
    }
}

MoveDatabase::~MoveDatabase()
{
    if(pBuffer) free(pBuffer);
}

MoveDatabaseEntry *MoveDatabase::getByID(UINT16 id)
{
    if(id >= num_entries) return NULL;
    return vMoves.at(id);
}