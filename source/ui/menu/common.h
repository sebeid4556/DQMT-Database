#ifndef UI_MENU_COMMON_H_
#define UI_MENU_COMMON_H_

#include"../framework/common.h"

namespace menu
{
    enum MenuID
    {
        ID_MENU_NONE = 0, ID_MENU_TEST, ID_MENU_MAIN, ID_MENU_START
    };
}

namespace stats
{
    enum Size {SMALL=0, NORMAL, MEGA, GIGA};
    const double ULTIMATE_MULTIPLIER = 1.2;
}

namespace resistance
{
    const UINT32 NUM_TYPES = 28;
    const UINT32 NUM_VALUES = 12;   //to account for gap between NLHI and NHAI
    enum ResistanceValue {WEAK = 0, NORMAL, LIGHT, HALF, ALMOST, IMMUNE, HEAL, REFLECT, NLHI = 8, NHAI = 11};
    
    extern const WCHAR *TYPE_NAMES[NUM_TYPES];
    extern const INT32 ORDER[NUM_TYPES];
    extern const WCHAR *VALUES[NUM_VALUES];
}

#endif // UI_MENU_COMMON_H_