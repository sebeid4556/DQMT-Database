#ifndef DATABASE_EKT_H_
#define DATABASE_EKT_H_

#include<stdio.h>
#include<stdlib.h>
#include<vector>

#include"../util/types.h"

//EKT: stands for EnmyKindTbl.bin

#define EKT_MAGIC 0x454B5400 //"EKT\x00"

const UINT32 kEktMagic = 0x454B5400;
const CHAR kEktPath[] = "ROM/raw/romfs/data/Param/EnmyKindTbl.bin";

typedef struct {
    UINT32 magic;
    UINT32 num_entries;
}EktHeader;

typedef struct __attribute__((packed, aligned(1))){
    UINT8 padding_0[0x6];
    UINT8 species_and_rank;
    UINT8 size;
    UINT16 rank_number;
    UINT16 monster_id;
    UINT8 padding_1[0x4];
    UINT16 max_hp;
    UINT16 max_mp;
    UINT16 max_atk;
    UINT16 max_def;
    UINT16 max_spd;
    UINT16 max_int;
    UINT8 padding_2[0xC];
    UINT8 resistance[0xE];
    UINT16 equippable_weapons;
    UINT16 traits[0x6];
    UINT8 padding_3[0x4];
    UINT8 levelup_table;
    UINT8 padding_4[0x1A];
    UINT16 skill;
    UINT8 padding_5[0x2];
}EktEntry;

class EKTParser
{
    public:
        EKTParser(CHAR *pPath);
        ~EKTParser();
        EktHeader *getEktHeader();
        EktEntry *getEktEntry(UINT32 index);
    private:
        UINT8 *pBuffer = NULL;  //initialize to NULL so that we can tell later if it has been malloc'd
        UINT32 size;

        std::vector<EktEntry *> vEntries;
};

#endif // DATABASE_EKT_H_