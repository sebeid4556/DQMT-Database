#pragma once

#include"common.h"

typedef struct __attribute__((packed, aligned(1)))
{
    UINT8 signature[4];

}BclimHeader;

typedef struct __attribute__((packed, aligned(1)))
{
    UINT8 signature[4];
    UINT32 header_size;
    UINT16 width;
    UINT16 height;
    UINT32 format;
    UINT32 image_size;
}ImageHeader;

typedef struct __attribute__((packed, aligned(1)))
{
    UINT8 R : 4;
    UINT8 G : 4;
    UINT8 B : 4;
    UINT8 A : 4;
}RGBA4444;

#define BCLIM_BLOCK_SIZE 64

const UINT8 kBclimBlockIndexTable[BCLIM_BLOCK_SIZE] = 
{
	 0,  1,  4,  5, 16, 17, 20, 21,
	 2,  3,  6,  7, 18, 19, 22, 23,
	 8,  9, 12, 13, 24, 25, 28, 29,
	10, 11, 14, 15, 26, 27, 30, 31,
	32, 33, 36, 37, 48, 49, 52, 53,
	34, 35, 38, 39, 50, 51, 54, 55,
	40, 41, 44, 45, 56, 57, 60, 61,
	42, 43, 46, 47, 58, 59, 62, 63
};

class BclimParser
{
    public:
        BclimParser(const CHAR *pPath);
        ~BclimParser();
        RGBA4444 *getPixel(UINT16 x, UINT16 y);        
        UINT16 getWidth();
        UINT16 getHeight();
        
    private:
        UINT32 align(UINT32 n);
        void _parseHeaders();
        void _decode();        
    
        UINT8 *pBuffer = NULL;
        UINT32 size;
        UINT16 width;
        UINT16 height;
        UINT16 aligned_width;
        UINT16 aligned_height;
        UINT32 total_aligned_pixels;

        BclimHeader *bclim_header;
        ImageHeader *image_header;
                
        UINT16 *pTemp = NULL;
        std::vector<RGBA4444 *> vPixelArray;
};

SDL_Surface *loadBCLIMSurface(const CHAR *pPath);

SDL_Texture *loadBCLIMTexture(const CHAR *pPath);
SDL_Texture *loadBCLIMTextureEX(const CHAR *pPath, SDL_Surface **pSurfaceOut);