#include"bits.h"
#include"types.h"

//return low nibble
UINT8 LOW(UINT8 n)
{
    return (n & 0b00001111);
}

//return high nibble
UINT8 HIGH(UINT8 n)
{
    return ((n & 0b11110000) >> 4);
}

//flip bytes ("convert little endian to big endian")
UINT16 LE16(UINT16 n)
{
    UINT8 r = ((n & 0xFF00) >> 8);
    return (n << 8) | r;
}

//flip endianness of 32bit unsigned int
UINT32 LE32(UINT32 n)
{
    UINT32 top;    
    UINT32 r = 0;
    for(UINT32 i = 0;i < 4;i++)
    {
        top = ((n >> (i * 8)) & 0xFF);
        top <<= (24 - (i * 8));
        r = r | top;        
    }
    return r;
}

//get a certain bit from a byte
UINT8 BIT(UINT8 n, UINT32 bit)
{
    return ((n & (1 << bit)) >> bit);
}

UINT16 BIT(UINT16 n, UINT32 bit)
{
    return ((n & (1 << bit)) >> bit);
}

UINT32 BIT(UINT32 n, UINT32 bit)
{
    return ((n & (1 << bit)) >> bit);
}

UINT8 BYTE(UINT8 *pBuffer)
{
    return *((UINT8 *)pBuffer);
}

UINT16 SHORT(UINT8 *pBuffer)
{
    return *((UINT16 *)pBuffer);
}

UINT32 WORD(UINT8 *pBuffer)
{
    return *((UINT32 *)pBuffer);
}