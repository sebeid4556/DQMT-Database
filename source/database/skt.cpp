#include<stdio.h>
#include<stdlib.h>

#include"../util/util.h"
#include"skt.h"

const CHAR *kSktErrorMessages[NUM_SKT_ERRORS] = 
{
    "SKTEntry id out of bounds"
};

SKTParser::SKTParser(CHAR *pPath)
{
    INT32 r = loadFileIntoBuffer((CHAR *)kSktPath, &pBuffer, &size);
    if(r != FILE_RET_OK)
    {
        perror(NULL);
        fatalError(kFileErrorMessages[FILE_ERROR_FOPEN_FAILED], "SKTParser::SKTParser");
    }

    SktHeader *pHeader = (SktHeader *)pBuffer;    
    SktEntry *offset;
    for(UINT32 i = 0;i < pHeader->num_entries;i++)
    {
        offset = (SktEntry *)(pBuffer + sizeof(SktHeader) + (i * sizeof(SktEntry)));
        vEntries.push_back(offset);
    }
}

SKTParser::~SKTParser()
{
    if(pBuffer) free(pBuffer);
}

SktHeader *SKTParser::getSktHeader()
{
    return (SktHeader *)pBuffer;
}

SktEntry *SKTParser::getSktEntry(UINT32 index)
{
    if(index >= vEntries.size()) fatalError(kSktErrorMessages[SKT_INDEX_OUT_OF_BOUNDS], "SKTParser::getSktEntry");
    return vEntries.at(index);
}