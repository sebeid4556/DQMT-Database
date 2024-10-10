#include<stdio.h>
#include<stdlib.h>

#include"../util/util.h"
#include"skill.h"

const CHAR *kSkillBinPath = "data/skills.bin";

SkillDatabase::SkillDatabase()
{
    INT32 r = loadFileIntoBuffer((CHAR *)kSkillBinPath, &pBuffer, &size);
    if(r != FILE_RET_OK) fatalError(kFileErrorMessages[r], "SkillDatabase::SkillDatabase");

    num_entries = size / sizeof(SkillDatabaseEntry);    

    SkillDatabaseEntry *pSkill;

    for(UINT32 i = 0;i < num_entries;i++)
    {
        pSkill = (SkillDatabaseEntry *)(pBuffer + (sizeof(SkillDatabaseEntry) * i));        
        vSkills.push_back(pSkill);
    }
}

SkillDatabase::~SkillDatabase()
{
    if(pBuffer) free(pBuffer);
}

SkillDatabaseEntry *SkillDatabase::getByID(UINT16 id)
{
    if(id >= vSkills.size()) return NULL;
    return vSkills.at(id);
}

UINT32 SkillDatabase::getNumEntries()
{
    return vSkills.size();
}