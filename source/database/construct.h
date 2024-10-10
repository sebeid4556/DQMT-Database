#ifndef DATABASE_CONSTRUCT_H_
#define DATABASE_CONSTRUCT_H_

#include"../util/types.h"
#include"ekt.h"
#include"binj.h"
#include"skt.h"

#define NUM_CONSTRUCT_ERRORS 3
#define CONSTRUCT_ERROR_EKT_FILE_TOO_BIG 0
#define CONSTRUCT_ERROR_EKT_WRONG_MAGIC 1
#define CONSTRUCT_ERROR_SKT_WRONG_MAGIC 2

const extern CHAR *kConstructErrorMessages[NUM_CONSTRUCT_ERRORS];

#define CONSTRUCT_RET_OK -1

void addNewMonsterEntry(FILE *pFp, EktEntry *pEktEntry, BinJParser *pMonsterNameBinJParser, UINT16 n);
void createNewMonsterDatabaseFile(UINT8 *pBuffer);
void constructMonsterDatabase();

void addNewTraitEntry(FILE *pFp, BinJParser *pTraitNameBinJParser, BinJParser *pTraitHelpBinJParser, UINT16 n);
void createNewTraitDatabaseFile(BinJParser *pTraitNameBinJParser, BinJParser *pTraitHelpBinJParser);
void constructTraitDatabase();

void addNewMoveEntry(FILE *pFp, BinJParser *pMoveNameBinJParser, BinJParser *pMoveHelpBinJParser, UINT16 n);
void createNewMoveDatabaseFile(BinJParser *pMoveNameBinJParser, BinJParser *pMoveHelpBinJParser);
void constructMoveDatabase();

void addNewSkillEntry(FILE *pFp, SktEntry *pSktEntry, BinJParser *pSkillNameBinJParser, UINT16 n);
void createNewSkillDatabaseFile(SKTParser *pSkt, BinJParser *pSkillNameBinJParser);
void constructSkillDatabase();

void constructDatabase();

#endif // DATABASE_CONSTRUCT_H_