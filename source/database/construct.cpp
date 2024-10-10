#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#include"construct.h"
#include"../util/util.h"
#include"ekt.h"
#include"binj.h"
#include"monster.h"
#include"trait.h"
#include"move.h"
#include"skill.h"
#include"skt.h"

const CHAR *kConstructErrorMessages[] = 
{
    "EKT file must be smaller than 2,000,000,000 bytes",
    "EKT file magic does not match"
    "SKT file magic does not match"
};

const CHAR *kMonsterNameBinJPath = "ROM/raw/romfs/data/Message/msg_monstername.binJ";   //names of all monsters
const CHAR *kTraitBinJPath = "ROM/raw/romfs/data/Message/msg_tokusei.binJ"; //names of all traits
const CHAR *kLibraryBinJPath = "ROM/raw/romfs/data/Message/msg_library.binJ";   //help messages for all traits
const CHAR *kMoveNameBinJPath = "ROM/raw/romfs/data/Message/msg_actionname.binJ";   //names of all moves
const CHAR *kMoveHelpBinJPath = "ROM/raw/romfs/data/Message/msg_actionhelp.binJ";   //help messages for all moves
const CHAR *kSkillNameBinJPath = "ROM/raw/romfs/data/Message/msg_skillname.binJ";   //help messages for all moves

const CHAR *kNewMonsterDatabasePath = "data/monsters.bin";
const CHAR *kNewTraitDatabasePath = "data/traits.bin";
const CHAR *kNewMoveDatabasePath = "data/moves.bin";
const CHAR *kNewSkillDatabasePath = "data/skills.bin";

//==============================================================================================================================
// MONSTER
//==============================================================================================================================

void addNewMonsterEntry(FILE *pFp, EktEntry *pEktEntry, BinJParser *pMonsterNameBinJParser, UINT16 n)
{
    MonsterDatabaseEntry monster;

    memset(&monster, 0x00, sizeof(MonsterDatabaseEntry));   //for good measure

    monster.id = n;
    memcpy(monster.name, pMonsterNameBinJParser->getLine(n), (MAX_MONSTER_NAME_LENGTH * sizeof(UINT16)));
    monster.size = LOW(pEktEntry->size);
    monster.rank_number = pEktEntry->rank_number;
    monster.rank = LOW(pEktEntry->species_and_rank);
    monster.species = HIGH(pEktEntry->species_and_rank);
    monster.max_hp = pEktEntry->max_hp;
    monster.max_mp = pEktEntry->max_mp;
    monster.max_atk = pEktEntry->max_atk;
    monster.max_def = pEktEntry->max_def;
    monster.max_spd = pEktEntry->max_spd;
    monster.max_int = pEktEntry->max_int;
    for(UINT32 i = 0; i < MAX_MONSTER_TRAITS;i++) monster.traits[i] = pEktEntry->traits[i];
    for(UINT32 i = 0; i < NUM_RESISTANCE_TYPES;i+=2)
    {
        monster.resistance[i] = LOW(pEktEntry->resistance[i/2]);
        monster.resistance[i+1] = HIGH(pEktEntry->resistance[i/2]);
    }
    monster.equippable_weapons = pEktEntry->equippable_weapons;
    monster.skill = pEktEntry->skill;
    monster.levelup_table = pEktEntry->levelup_table;

    if(fwrite((const void *)&monster, sizeof(MonsterDatabaseEntry), 1, pFp) == 0)
    {
        fatalError(kFileErrorMessages[FILE_ERROR_FWRITE_FAILED], "addNewMonsterEntry");
    }
}

void createNewMonsterDatabaseFile(EKTParser *pEkt, BinJParser *pMonsterNameBinJParser)
{        
    printf("\t\t-[+]Creating %s...\n", kNewMonsterDatabasePath);
    
    EktHeader *pEktHeader = pEkt->getEktHeader();
    if(pEktHeader->magic != LE32(EKT_MAGIC)) fatalError(kConstructErrorMessages[CONSTRUCT_ERROR_EKT_WRONG_MAGIC], "createNewMonsterDatabaseFile");

    FILE *pFp = fopen(kNewMonsterDatabasePath, "wb");
    if(!pFp) fatalError(kFileErrorMessages[FILE_ERROR_FOPEN_FAILED], "createNewMonsterDatabaseFile");

    for(UINT32 i = 0; i < pEktHeader->num_entries; i++)
    {
        addNewMonsterEntry(pFp, pEkt->getEktEntry(i), pMonsterNameBinJParser, i);        
    }
        
    fclose(pFp);
}

void constructMonsterDatabase()
{
    printf("\t-[+]Constructing Monster database\n");

    LINE();

    printf("sizeof(EktEntry) = 0x%X(%d)\n", sizeof(EktEntry), sizeof(EktEntry));

    LINE();

    EKTParser Ekt((CHAR *)kEktPath);

    BinJParser MonsterNameBinJ(kMonsterNameBinJPath);

    createNewMonsterDatabaseFile(&Ekt, &MonsterNameBinJ);    
}

//==============================================================================================================================
// TRAIT
//==============================================================================================================================

void addNewTraitEntry(FILE *pFp, BinJParser *pTraitNameBinJParser, BinJParser *pTraitHelpBinJParser, UINT16 n)
{    
    TraitDatabaseEntry trait;    
    memcpy(trait.name, pTraitNameBinJParser->getLine(n), sizeof(trait.name));
    memcpy(trait.help, pTraitHelpBinJParser->getLine(n), sizeof(trait.help));
    
    if(!fwrite(&trait, sizeof(TraitDatabaseEntry), 1, pFp))
    {
        fatalError(kFileErrorMessages[FILE_ERROR_FWRITE_FAILED], "addNewTraitEntry");
    }
}

void createNewTraitDatabaseFile(BinJParser *pTraitNameBinJParser, BinJParser *pTraitHelpBinJParser)
{
    printf("\t\t-[+]Creating %s...\n", kNewTraitDatabasePath);

    FILE *pFp = fopen(kNewTraitDatabasePath, "wb");
    if(!pFp) fatalError(kFileErrorMessages[FILE_ERROR_FOPEN_FAILED], "createNewTraitDatabaseFile"); 
    
    for(UINT16 i = 0; i < NUM_TOTAL_TRAITS;i++)    
    {
        addNewTraitEntry(pFp, pTraitNameBinJParser, pTraitHelpBinJParser, i);
    }

    fclose(pFp);
}

void constructTraitDatabase()
{
    printf("\t-[+]Constructing Trait database\n");

    BinJParser TraitNameBinJParser(kTraitBinJPath);  
    BinJParser TraitHelpBinJParser(kLibraryBinJPath);
    createNewTraitDatabaseFile(&TraitNameBinJParser, &TraitHelpBinJParser);
}

//==============================================================================================================================
// MOVE
//==============================================================================================================================

void addNewMoveEntry(FILE *pFp, BinJParser *pMoveNameBinJParser, BinJParser *pMoveHelpBinJParser, UINT16 n)
{
    MoveDatabaseEntry move;    
    memcpy(move.name, pMoveNameBinJParser->getLine(n), sizeof(move.name));
    memcpy(move.help, pMoveHelpBinJParser->getLine(n), sizeof(move.help));
    
    if(!fwrite(&move, sizeof(MoveDatabaseEntry), 1, pFp))
    {
        fatalError(kFileErrorMessages[FILE_ERROR_FWRITE_FAILED], "addNewMoveEntry");
    }
}

void createNewMoveDatabaseFile(BinJParser *pMoveNameBinJParser, BinJParser *pMoveHelpBinJParser)
{
    printf("\t\t-[+]Creating %s...\n", kNewMoveDatabasePath);

    FILE *pFp = fopen(kNewMoveDatabasePath, "wb");
    if(!pFp) fatalError(kFileErrorMessages[FILE_ERROR_FOPEN_FAILED], "createNewMoveDatabaseFile"); 
    
    for(UINT16 i = 0; i < pMoveNameBinJParser->getNumEntries();i++)    
    {
        addNewTraitEntry(pFp, pMoveNameBinJParser, pMoveHelpBinJParser, i);
    }

    fclose(pFp);
}

void constructMoveDatabase()
{
    printf("\t-[+]Constructing Move database\n");

    BinJParser MoveNameBinJParser(kMoveNameBinJPath);
    BinJParser MoveHelpBinJParser(kMoveHelpBinJPath);

    createNewMoveDatabaseFile(&MoveNameBinJParser, &MoveHelpBinJParser);
}

//==============================================================================================================================
// SKILL
//==============================================================================================================================

void addNewSkillEntry(FILE *pFp, SktEntry *pSktEntry, BinJParser *pSkillNameBinJParser, UINT16 n)
{
    SkillDatabaseEntry skill;    

    UINT16 move;
    UINT16 trait;

    memset(&skill, 0x00, sizeof(SkillDatabaseEntry));   //redundant but for good measure
    memcpy(skill.name, pSkillNameBinJParser->getLine(n), sizeof(skill.name));
    for(UINT32 i = 0;i < SKILL_MAX_MOVES_OR_TRAITS;i++)
    {
        skill.req_sp[i] = pSktEntry->req_sp[i];
        move = pSktEntry->moves[i].id;
        trait = pSktEntry->traits[i];

        skill.moves[i] = move;
        skill.traits[i] = trait;
    }

    if(fwrite((const void *)&skill, sizeof(SkillDatabaseEntry), 1, pFp) == 0)
    {
        fatalError(kFileErrorMessages[FILE_ERROR_FWRITE_FAILED], "addNewSkillEntry");
    }
}

void createNewSkillDatabaseFile(SKTParser *pSkt, BinJParser *pSkillNameBinJParser)
{
    printf("\t\t-[+]Creating %s...\n", kNewSkillDatabasePath);
    
    SktHeader *pSktHeader = pSkt->getSktHeader();
    if(pSktHeader->magic != LE32(SKT_MAGIC)) fatalError(kConstructErrorMessages[CONSTRUCT_ERROR_SKT_WRONG_MAGIC], "createNewSkillDatabaseFile");

    FILE *pFp = fopen(kNewSkillDatabasePath, "wb");
    if(!pFp) fatalError(kFileErrorMessages[FILE_ERROR_FOPEN_FAILED], "createNewSkillDatabaseFile");

    for(UINT32 i = 0; i < pSktHeader->num_entries; i++)
    {
        addNewSkillEntry(pFp, pSkt->getSktEntry(i), pSkillNameBinJParser, i);        
    }
        
    fclose(pFp);
}

void constructSkillDatabase()
{
    printf("\t-[+]Constructing Skill database\n");

    LINE();
    printf("sizeof(SktEntry) = 0x%X(%d)\n", sizeof(SktEntry), sizeof(SktEntry));
    printf("sizeof(SktMoveSubEntry) = 0x%X(%d)\n", sizeof(SktMoveSubEntry), sizeof(SktMoveSubEntry));    

    SktEntry entry;

    printf("sizeof(SktEntry.req_sp) = 0x%X(%d)\n", sizeof(entry.req_sp), sizeof(entry.req_sp));
    printf("sizeof(SktEntry.moves) = 0x%X(%d)\n", sizeof(entry.moves), sizeof(entry.moves));
    printf("sizeof(SktEntry.traits) = 0x%X(%d)\n", sizeof(entry.traits), sizeof(entry.traits));

    LINE();

    SKTParser Skt((CHAR *)kSktPath);

    BinJParser SkillNameBinJParser(kSkillNameBinJPath);    

    createNewSkillDatabaseFile(&Skt, &SkillNameBinJParser);
}

//==============================================================================================================================

void constructDatabase()
{
    printf("[+]Constructing new database...\n");
    constructMonsterDatabase();
    constructTraitDatabase();
    constructMoveDatabase();
    constructSkillDatabase();
    printf("[+]Done.\n");
}