#include"common.h"

namespace resistance
{
    //const UINT32 NUM_TYPES = 28;
    //enum ResistanceValue {WEAK = 0, NORMAL, LIGHT, HALF, ALMOST, IMMUNE, HEAL, REFLECT};
    const WCHAR *TYPE_NAMES[NUM_TYPES] = {
        L"メラ", L"イオ", L"バギ", L"ヒャド",
        L"デイン", L"ドルマ", L"炎ブレス", L"吹雪ブレス",
        L"ザキ", L"マヌーサ", L"どく", L"マホトラ",
        L"マホトーン", L"息封じ", L"踊り封じ", L"こんらん",
        L"マインド", L"マヒ", L"ねむり", L"ダウン",
        L"ルカニ", L"ボミエ", L"フール", L"ギラ",
        L"ハック", L"体技封じ", L"斬撃封じ", L"ベタン"
    };

    const INT32 ORDER[NUM_TYPES] = {
        0, 1, 2, 3, 23, 4, 5, 27, 6, 7, 16, 17, 18, 15, 
        10, 8, 12, 26, 25, 13, 14, 19, 20, 21, 22, 9, 11, 24
    };

    const WCHAR *VALUES[NUM_VALUES] = {
        L"弱い", L"  ", L"軽減", L"半減", L"激減", L"無効", L"回復", L"反射", L"通軽半無", L"", L"", L"通半激無"    //the two blanks are 9 & 10
    };
}