#ifndef DATABASE_BINJ_H_
#define DATABASE_BINJ_H_

#include<stdio.h>
#include<vector>
#include<map>

#include"../util/util.h"

#define BINJ_MAX_DECODED_LENGTH 0x100   //0x100 is an arbitrary limit that I chose

#define BINJ_SEPARATOR 0xE31B

#define BINJ_ONE_BYTE_CHAR_START 0x01
#define BINJ_TWO_BYTE_CHAR_START 0xEO00
#define BINJ_THREE_BYTE_CHAR_START 0xE44E00

#define BINJ_ERROR_DATA_TOO_LONG 0

UINT32 getCodepointFromUTF_8(UINT8 *pUnicode);

class BinJParser
{
    public:
        BinJParser(const CHAR *pPath);
        ~BinJParser();
        UINT32 getNumEntries();   
        UINT16 *getLine(UINT32 line);
    private:
        void _populateDecodeTable();   //only meant to be called inside the constructor        
        void _parse();
        void _decode();                //only meant to be called inside the constructor           

        /*Stores raw .binJ file*/ 
        UINT8 *pBuffer = NULL;  //initialize to NULL to be able to see if malloc() was called
        UINT32 size;    //byproduct of loadFileIntoBuffer()        

        /*Used for parsing*/
        UINT32 header_size;
        UINT32 num_entries;
        UINT32 *pPointerBlock;
        UINT8 *pDataBlock;

        /*Hold decoding table*/
        std::map<UINT32, UINT16> mDecodeTable;
        /*Hold decoded lines in wchar_t(UINT16) format*/        
        std::vector<UINT16 *> vDecodedLines;
        /*Hold array of pointers to each raw data block entry*/
        std::vector<UINT8 *> vDataBlock;
};

#endif // DATABASE_BINJ_H_