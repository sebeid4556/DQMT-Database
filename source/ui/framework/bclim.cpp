#include"bclim.h"
#include"component/component.h"

BclimParser::BclimParser(const CHAR *pPath)
{
    pBuffer = loadFileIntoBufferEX(pPath, &size);
    //printf("pBuffer: \x1b[33m0x%08X\x1b[39m (0x%X bytes)\n", (UINT32)pBuffer, size);
    //printf("pBuffer ends at 0x%08X\n", (UINT32)pBuffer + size);    

    _parseHeaders();
    _decode();
}

BclimParser::~BclimParser()
{
    if(pBuffer != NULL)
    {
        //printf("FREEING pBuffer(0x%08X)...", (UINT32)pBuffer);        
        free(pBuffer);        
        //printf("[ %sOK%s ]\n", CONSOLE_GREEN, CONSOLE_WHITE);
    }
    if(pTemp)
    {
        //printf("FREEING pTemp(0x%08X)...", (UINT32)pTemp);        
        free(pTemp);        
        //printf("[ %sOK%s ]\n", CONSOLE_GREEN, CONSOLE_WHITE);
    }
}

UINT32 BclimParser::align(UINT32 n)
{
    UINT32 s = 8;
    while(s < n)
    {
        s *= 2;
    }
    return s;
}

void BclimParser::_parseHeaders()
{
    bclim_header = (BclimHeader *)(pBuffer + (size - sizeof(BclimHeader) - sizeof(ImageHeader)));
    image_header = (ImageHeader *)(pBuffer + (size - sizeof(ImageHeader)));

    width = image_header->width;
    height = image_header->height;

    aligned_width = align(width);
    aligned_height = align(height);

    total_aligned_pixels = aligned_width * aligned_height;

    //printf("TOTAL ALIGNED PIXELS: 0x%X (%d)\n", total_aligned_pixels, total_aligned_pixels);

    //printf("BCLIM format: %d\n", image_header->format);

    //if(image_header->format != 8) fatalError("Unsupported BCLIM format", "BclimParser::_parseHeaders");
    if(image_header->format != 8)
    {
        LINE();
        std::cout << "unsupported? BCLIM format " << image_header->format << std::endl;
        LINE();
    }
}

void BclimParser::_decode()
{
    pTemp = (UINT16 *)malloc(aligned_width * aligned_height * sizeof(RGBA4444));
    if(!pTemp) fatalError("malloc() failed", "BclimParser::_decode");
    //printf("pTemp: %s0x%08X%s\n", CONSOLE_GREEN, (UINT32)pTemp, CONSOLE_WHITE);    

    UINT32 blocks = ((aligned_width * aligned_height) / BCLIM_BLOCK_SIZE);
    //printf("\nBCLIM blocks: 0x%X (%d)\n", blocks, blocks);

    for(UINT32 block = 0;block < ((aligned_width * aligned_height) / BCLIM_BLOCK_SIZE);block++)
    {
        for(UINT32 pixel = 0;pixel < BCLIM_BLOCK_SIZE;pixel++)
        {            
            //printf("pTemp[0x%X] = *(UINT16 *)(pBuffer + 0x%X)\n", (block * BCLIM_BLOCK_SIZE + pixel), (block * BCLIM_BLOCK_SIZE + kBclimBlockIndexTable[pixel]));
            pTemp[block * BCLIM_BLOCK_SIZE + pixel] = *(UINT16 *)(pBuffer + (block * BCLIM_BLOCK_SIZE + kBclimBlockIndexTable[pixel]) * 2);
        }
    }

    //printf("Transferring to vPixelArray...");
    for(UINT16 y = 0;y < aligned_height;y++)
    {
        for(UINT16 x = 0;x < aligned_width;x++)
        {
            vPixelArray.push_back((RGBA4444 *)&pTemp[(((y / 8) * (aligned_width / 8) + (x / 8)) * 64 + y % 8 * 8 + x % 8)]);
        }
    }
    //printf("[ %sOK%s ]\n", CONSOLE_GREEN, CONSOLE_WHITE);
}

RGBA4444 *BclimParser::getPixel(UINT16 x, UINT16 y)
{    
    UINT32 pixel = (y * aligned_width) + x;        
    if(pixel >= aligned_width * aligned_height)
    {
        fatalError("pixel out of range", "BclimParser::getPixel");
    }
    return vPixelArray.at(pixel);
}

UINT16 BclimParser::getWidth()
{
    return width;
}

UINT16 BclimParser::getHeight()
{
    return height;
}

void setSurfacePixel(SDL_Surface *pSurface, UINT16 x, UINT16 y, UINT16 pixel)
{
    UINT8 *pPixel = (UINT8 *)pSurface->pixels + (y * pSurface->pitch) + (x * pSurface->format->BytesPerPixel);    
    *(UINT16 *)pPixel = pixel;
}

SDL_Surface *loadBCLIMSurface(const CHAR *pPath)
{
    BclimParser Icon(pPath);
    
    SDL_Surface *pSur = SDL_CreateRGBSurface(0, Icon.getWidth(), Icon.getHeight(), 16, 0xF000, 0x0F00, 0x00F0, 0x000F);    
    if(!pSur) fatalError(SDL_GetError(), "loadBCLIMSurface");

    SDL_Texture *pTex;       
    UINT16 color; 
    RGBA4444 *pixel;
    UINT32 pos;

    if(SDL_LockSurface(pSur)) fatalError(SDL_GetError(), "loadBCLIMSurface");

    //const char *pFormatName = SDL_GetPixelFormatName(pSur->format->format);
    //printf("PIXEL FORMAT: %s\n", pFormatName);

    //printf("ICON: %d x %d px\n", Icon.getWidth(), Icon.getHeight());

    //printf("pSurface->format->BytesPerPixel = %d\n", pSur->format->BytesPerPixel);

    for(int y = 0;y < Icon.getHeight();y++)
    {
        for(int x = 0;x < Icon.getWidth();x++)
        {                        
            //printf("(%2d, %2d): ", x, y);
            pixel = Icon.getPixel(x, y);   
            //printf("pixel: %s0x%08X%s\n", CONSOLE_GREEN, (UINT32)pixel, CONSOLE_WHITE);         
            
            color = *(UINT16 *)pixel;
            
            setSurfacePixel(pSur, x, y, color);            
        }
    }

    SDL_UnlockSurface(pSur);
    return pSur;
}

SDL_Texture *loadBCLIMTexture(const CHAR *pPath)
{
    SDL_Surface *pSur = loadBCLIMSurface(pPath);
    
    SDL_Texture *pTex = SDL_CreateTextureFromSurface(UIComponent::getRenderer(), pSur);
    if(!pTex) fatalError(SDL_GetError(), "loadBCLIM");    
    
    SDL_FreeSurface(pSur);    
    
    return pTex;
}

SDL_Texture *loadBCLIMTextureEX(const CHAR *pPath, SDL_Surface **pSurfaceOut)
{
    SDL_Surface *pSurface = loadBCLIMSurface(pPath);

    *pSurfaceOut = pSurface;
    
    SDL_Texture *pTex = SDL_CreateTextureFromSurface(UIComponent::getRenderer(), pSurface);
    if(!pTex) fatalError(SDL_GetError(), "loadBCLIM");    
    
    return pTex;
}