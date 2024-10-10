#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"../util/util.h"
#include"binj.h"

const CHAR *kBinJDecodeTablePath = "binJDecodeTable.txt";

const CHAR *kBinJErrorMessages[] = 
{
    "Data Block entry exceeded mex length (0xFF bytes)"
};

/*Convert Unicode UTF-8 encoded array of bytes into 16-bit WCHAR*/
UINT32 getCodepointFromUTF_8(UINT8 *pUnicode)
{    
    UINT32 unicode_size = 0;        //value between 1-4
    UINT32 i = 0;
    UINT8 bit;  //used to determine size of unicode character
    
    /*determine length of utf-8 encoding*/
    while(true)
    {
        bit = BIT(pUnicode[0], 7-i);     //work from left to right, or most significant to least significant bit               
        if(bit == 0 && i == 0) //1 byte
        {
            unicode_size = 1;
            break;
        }
        else
        {
            if(bit == 0) break;
        }
        unicode_size++;
        i++;
    }
        
    UINT32 result = 0x00000000;
    UINT8 byte;
    UINT32 shifts;

    /*handle first byte*/
    byte = pUnicode[0];
    if(unicode_size > 1)    //if size > 1, so 2, 3, & 4 bytes
    {
        /*equation to find the necessary # of left shifts is: y = x-2(x-2)*/
        shifts = (unicode_size - (2 * (unicode_size - 2)));
        byte ^= (0b11110000 << shifts);
    }    
    result |= byte;

    for(UINT32 j = 1;j < unicode_size;j++)  //start from second byte if it exists
    {
        result <<= 6;
        byte = pUnicode[j];
        byte &= 0b00111111; //disregard the highest 2 bits
        result |= byte;        
    }
    return result;
}

BinJParser::BinJParser(const CHAR *pPath)
{    
    INT32 r = loadFileIntoBuffer((CHAR *)pPath, &pBuffer, &size);
    if(r != FILE_RET_OK) fatalError(kFileErrorMessages[r], "BinJParser::BinJParser");    

    _populateDecodeTable();
    _parse();
    _decode();
}

BinJParser::~BinJParser()
{
    /*Free memory that was malloc'd*/
    for(UINT32 i = 0;i < vDecodedLines.size();i++)
    {
        free(vDecodedLines.at(i));
    }
}

void BinJParser::_populateDecodeTable()
{
    FILE *pDecodeFp = fopen(kBinJDecodeTablePath, "r");
    if(!pDecodeFp) fatalError(kFileErrorMessages[FILE_ERROR_FOPEN_FAILED], "BinJParser::BinJParser");

    CHAR line[0x10];    //0x10 is an arbitrary limit that I chose
    UINT32 index;
    CHAR character[0x10];   //same here
    CHAR *pUnicode;
    UINT32 unicode_buffer_size;
    while(fgets(line, sizeof(line), pDecodeFp))
    {
        memset(character, 0x00, sizeof(character));
        sscanf(line, "%06X;%s\x0A", &index, character);
                
        unicode_buffer_size = strlen(character) + 1;    //+1 for the NULL-terminator
        pUnicode = (CHAR *)malloc(unicode_buffer_size);
        strncpy(pUnicode, character, unicode_buffer_size);

        mDecodeTable.insert({index, getCodepointFromUTF_8((UINT8 *)pUnicode)});

        free(pUnicode);
    }

    fclose(pDecodeFp);
}

void BinJParser::_parse()
{
    header_size = WORD(pBuffer + 0) * 4;

    num_entries = 0;
    for(UINT32 i = 0;i < (header_size/4);i++)   //calculate total # of entries
    {
        num_entries += WORD(pBuffer + 4 + (i * 4));
    }
    pPointerBlock = (UINT32 *)(pBuffer + (4 + header_size));    

    UINT32 next_offset;
    for(UINT32 i = 0;i < num_entries;i++)   //populate vDataBlock
    {
        next_offset = *(pPointerBlock + i);        
        vDataBlock.push_back(pBuffer + next_offset);
    }
}

void BinJParser::_decode()
{    
    UINT8 *pRawLine;
    CHAR pEncodedLine[0x100];   //0x100 is an arbitrary limit that I chose    
    UINT16 *pDecodedLine = NULL;
    UINT32 n;   //offset into Data Block entry
    UINT32 t;   //offset into pDecodedLine    
    UINT8 byte;
    UINT32 char_code;

    for(UINT32 i = 0;i < num_entries;i++)
    {
        pRawLine = vDataBlock.at(i);
        
        memset(pEncodedLine, 0x00, sizeof(pEncodedLine));   //clear pEncodedLine

        pDecodedLine = (UINT16 *)malloc(0x100); //allocate 0x100 bytes (that should be enough right?)
        memset(pDecodedLine, 0x00, 0x100);   //clear pDecodedLine

        n = 0;
        t = 0;
        char_code = 1;  //Default char_code

        while(LE16(SHORT(pRawLine + n)) != BINJ_SEPARATOR)  //fix endianness
        {            
            byte = BYTE(pRawLine + n);
            
            if(byte == 0xE0 || byte == 0xE1 || byte == 0xE2 || byte == 0xE3)    //signifies two-byte characters
            {                
                char_code = byte << 8;
                byte = BYTE(pRawLine + n + 1);
                char_code |= byte;
                pDecodedLine[t] = mDecodeTable[char_code];
                n += 2;                                
            }
            else if(byte == 0xE4)   //three-byte characters
            {
                char_code = byte << 16;
                byte = BYTE(pRawLine + n + 1);
                char_code |= byte << 8;
                byte = BYTE(pRawLine + n + 2);
                char_code |= byte;
                pDecodedLine[t] = mDecodeTable[char_code];
                n += 3;                
            }
            else    //single-byte characters
            {
                char_code = byte;
                pDecodedLine[t] = mDecodeTable[char_code];
                n++;                
            }
            t++;    //advance offset into pDecodedLine
            
            if(n >= (BINJ_MAX_DECODED_LENGTH - 1))  //-1 for the NULL-terminator
            {
                fatalError(kBinJErrorMessages[BINJ_ERROR_DATA_TOO_LONG], "BinJParser::_decode");
            }
        }
        vDecodedLines.push_back(pDecodedLine);
    }
}

UINT32 BinJParser::getNumEntries()
{
    return num_entries;
}

UINT16 *BinJParser::getLine(UINT32 line)
{        
    return vDecodedLines.at(line);
}