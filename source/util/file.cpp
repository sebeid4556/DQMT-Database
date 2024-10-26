#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"types.h"
#include"file.h"
#include"error.h"

const CHAR *kFileErrorMessages[NUM_FILE_ERRORS] = 
{
    "path is too long",
    "invalid path",
    "fopen() failed",
    "fread() failed"
};

INT32 loadFileIntoBuffer(CHAR *pPath, UINT8 **pBuffer, UINT32 *pSize)
{
    printf("[+]Loading %s...", pPath);

    //check path
    UINT32 len = strlen(pPath);
    if(len == 0) return FILE_ERROR_PATH_INVALID;
    else if(len > MAX_PATH) return FILE_ERROR_PATH_TOO_LONG;

    //open file
    FILE *pFp = fopen(pPath, "rb");
    if(!pFp)
    {
        perror(NULL);
        return FILE_ERROR_FOPEN_FAILED;
    }
    
    //get size    
    int res = fseek(pFp, 0, SEEK_END);    
    if(res != 0)
    {        
        fatalError("fseek() failed\n", "loadFileIntoBuffer");
        perror(NULL);
    }
    UINT32 size = ftell(pFp); 
    rewind(pFp);
    *pSize = size;    

    //read file into buffer    
    *pBuffer = (UINT8 *)malloc(size);     
    INT32 r = fread(*pBuffer, 1, size, pFp);    
    if(r == 0) return FILE_ERROR_FREAD_FAILED;
    
    fclose(pFp);

    printf("Done.\n");

    return FILE_RET_OK;
}

UINT8 *loadFileIntoBufferEX(const CHAR *pPath, UINT32 *pSize)
{
    printf("[+]Loading %s...", pPath);

    //check path
    UINT32 len = strlen(pPath);
    if(len == 0) fatalError(kFileErrorMessages[FILE_ERROR_PATH_INVALID], "loadFileIntoBufferEX");
    else if(len > MAX_PATH) fatalError(kFileErrorMessages[FILE_ERROR_PATH_TOO_LONG], "loadFileIntoBufferEX");

    //open file
    FILE *pFp = fopen(pPath, "rb");
    if(!pFp)
    {
        perror(NULL);
        fatalError(kFileErrorMessages[FILE_ERROR_FOPEN_FAILED], "loadFileIntoBufferEX");
    }
    
    //get size    
    int res = fseek(pFp, 0, SEEK_END);    
    if(res != 0)
    {        
        fatalError("fseek() failed\n", "loadFileIntoBuffer");
        perror(NULL);
    }
    UINT32 size = ftell(pFp); 
    rewind(pFp);  
    *pSize = size;  

    UINT8 *pBuffer = NULL;

    //read file into buffer    
    pBuffer = (UINT8 *)malloc(size);
    if(!pBuffer) fatalError("malloc() failed", "loadFileIntoBufferEX");
    //*pBuffer = new UINT8[size];
    INT32 r = fread(pBuffer, 1, size, pFp);    
    if(r == 0) fatalError(kFileErrorMessages[FILE_ERROR_FREAD_FAILED], "loadFileIntoBufferEX");
    
    fclose(pFp);

    printf("Done.\n");

    //free(*pBuffer);

    return pBuffer;
}

//get the index to the last occurance of "." in the filename
INT32 getExtentionIndex(const CHAR *pPath)
{
    for(UINT32 i = strlen(pPath) - 1;i >= 0;i--)    //work backwards
    {
        if(pPath[i] == '.')
        {
            return i;
        }
    }
    return -1;  //not found
}