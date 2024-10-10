#include<stdio.h>
#include<stdlib.h>

#include"../util/util.h"
#include"ekt.h"

#define NUM_EKT_ERRORS 1

typedef enum 
{
    EKT_INDEX_OUT_OF_BOUNDS
}EKT_ERRORS;

const CHAR *kEktErrorMessages[NUM_EKT_ERRORS] = 
{
    "EKTEntry id out of bounds"
};

EKTParser::EKTParser(CHAR *pPath)
{
    INT32 r = loadFileIntoBuffer((CHAR *)kEktPath, &pBuffer, &size);
    if(r != FILE_RET_OK)
    {
        perror(NULL);
        fatalError(kFileErrorMessages[FILE_ERROR_FOPEN_FAILED], "EKTParser::EKTParser");
    }

    EktHeader *pHeader = (EktHeader *)pBuffer;    
    EktEntry *offset;
    for(UINT32 i = 0;i < pHeader->num_entries;i++)
    {
        offset = (EktEntry *)(pBuffer + sizeof(EktHeader) + (i * sizeof(EktEntry)));
        vEntries.push_back(offset);
    }
}

EKTParser::~EKTParser()
{
    if(pBuffer) free(pBuffer);
}

EktHeader *EKTParser::getEktHeader()
{
    return (EktHeader *)pBuffer;
}

EktEntry *EKTParser::getEktEntry(UINT32 index)
{
    if(index >=vEntries.size()) fatalError(kEktErrorMessages[EKT_INDEX_OUT_OF_BOUNDS], "EKTParser::getEktEntry");
    return vEntries.at(index);
}