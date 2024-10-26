#include"string.h"

#include<iostream>
#include<iomanip>
#include<sstream>

//template <typename T>
//std::wstring toHexWString(T n)
std::wstring toHexWString16(UINT16 n)
{
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(sizeof(n)*2) << std::hex << n;

    std::string str = stream.str();
    std::wstring ret;
    return ret.assign(str.begin(), str.end());
    //return std::wstring();
}