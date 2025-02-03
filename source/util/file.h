#ifndef UTIL_FILE_H_
#define UTIL_FILE_H_

#include"types.h"

#include<string>

#define NUM_FILE_ERRORS 4
#define FILE_ERROR_PATH_TOO_LONG 0
#define FILE_ERROR_PATH_INVALID 1
#define FILE_ERROR_FOPEN_FAILED 2
#define FILE_ERROR_FREAD_FAILED 3
#define FILE_ERROR_FWRITE_FAILED 4

#define FILE_RET_OK -1

#define MAX_PATH 256

const extern CHAR *kFileErrorMessages[NUM_FILE_ERRORS];

INT32 loadFileIntoBuffer(CHAR *pPath, UINT8 **pBuffer, UINT32 *pSize);
UINT8 *loadFileIntoBufferEX(const CHAR *pPath, UINT32 *pSize);

INT32 getExtentionIndex(const CHAR *pPath);

bool checkExtension(const CHAR *pPath, const CHAR *pExtension); //BUGGY -- DO NOT USE
bool checkExtension(const std::string& path, const std::string& extension);

#endif // UTIL_FILE_H_