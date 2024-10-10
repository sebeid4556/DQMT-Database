#ifndef DATABASE_PATHS_H_
#define DATABASE_PATHS_H_

#include"../util/util.h"

/*THIS IS BAD PRACTICE; Make a config file instead so that you don't have to build every time you want to change a path*/

const static CHAR *kTraitBinPath = "data/traits.bin";
const static CHAR *kMonstersBinPath = "data/monsters.bin";

const static CHAR *kMonsterNameBinJPath = "ROM/raw/romfs/data/Message/msg_monstername.binJ";   //names of all monsters
const static CHAR *kTraitBinJPath = "ROM/raw/romfs/data/Message/msg_tokusei.binJ"; //names of all traits
const static CHAR *kLibraryBinJPath = "ROM/raw/romfs/data/Message/msg_library.binJ";   //help messages for all traits

const static CHAR *kNewMonsterDatabasePath = "data/monsters.bin";
const static CHAR *kNewTraitDatabasePath = "data/traits.bin";

const static CHAR *kBinJDecodeTablePath = "binJDecodeTable.txt";

const static CHAR *kEktPath = "ROM/raw/romfs/data/Param/EnmyKindTbl.bin";

#endif // DATABASE_PATHS_H_