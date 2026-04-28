/* data.h */
#ifndef DATA_H
#define DATA_H

#include "types.h"

/* [5] variables */
// [5-1] モンスターのステータスの配列を宣言する　monster's status
extern CHARACTER monsters[MONSTER_MAX];

// [5-2] キャラクターの配列を宣言する　array of characters
extern CHARACTER characters[CHARACTER_MAX];

// [5-3] コマンドの名前を宣言する　declare command names
extern char commandNames[COMMAND_MAX][4 * 3 + 1];

#endif
