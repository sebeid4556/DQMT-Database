#ifndef DATABASE_SKT_H_
#define DATABASE_SKT_H_

#include<stdio.h>
#include<vector>

#include"../util/util.h"

/*SKT: stands for SkillTbl.bin*/

#define SKT_MAGIC 0x534B494C //"SKIL"

#define NUM_SKT_ERRORS 1

typedef enum 
{
    SKT_INDEX_OUT_OF_BOUNDS
}SKT_ERRORS;

#define SKILL_MAX_MOVES 10

const CHAR kSktPath[] = "ROM/raw/romfs/data/Param/SkillTbl.bin";

typedef struct
{
    UINT32 magic;
    UINT32 num_entries;
}SktHeader;

typedef struct __attribute__((packed, aligned(1)))
{
    UINT16 id;
    UINT16 unknown;
    UINT32 padding;
}SktMoveSubEntry;

typedef struct __attribute__((packed, aligned(1)))
{
    UINT8 req_sp[SKILL_MAX_MOVES];
    SktMoveSubEntry moves[SKILL_MAX_MOVES];
    UINT16 traits[SKILL_MAX_MOVES];
}SktEntry;

class SKTParser
{
    public:
        SKTParser(CHAR *pPath);
        ~SKTParser();
        SktHeader *getSktHeader();
        SktEntry *getSktEntry(UINT32 index);
    private:
        UINT8 *pBuffer = NULL;
        UINT32 size;        
        
        std::vector<SktEntry *> vEntries;
};


#endif // DATABASE_SKT_H_