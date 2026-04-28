/* data.c */
#include "types.h"

/* [5] variables */
// [5-1] モンスターのステータスの配列を宣言する　monster's status
CHARACTER monsters[MONSTER_MAX] = {
    // [5-1-1] MONSTER_PLAYER プレイヤー
    {
        100,        // [5-1-2] int hp HP
        100,        // [5-1-3] int maxHP  MaxHP
        15,         // [5-1-4] int mp MP
        15,         // [5-1-5] int Max HP
        30,         // [5-1-6] int attack 攻撃力
        "ゆうしゃ", // [5-1-7] char name name [4 * 3 + 1] name
        "",         // doesn't have aa but declare as ""
        0,          // command initialize as 0
        0,          // target initialize as 0
    },

    // [5-1-8]MONSTER_SLIME
    {
        3,          // [5-1-9] int hp
        3,          // [5-1-10] int maxHP
        0,          // [5-1-11] int mp MP
        0,          // [5-1-12] int maxHP
        2,          // [5-1-13] int attach 攻撃力
        "スライム", // [5-1-14] char name [4 * 3 +1] name
        // [5-1-15] char aa[256] アスキーアート
        "／・Д・＼\n"
        "～～～～～",
        0, // command initialize as 0
        0, // target initialize as 0
    },

    // [5-1-16]MONSTER_BOSS
    {
        255,      // [5-1-17] int hp
        255,      // [5-1-18] int maxHP
        0,        // [5-1-19] int mp MP
        0,        // [5-1-20] int maxHP
        50,       // [5-1-21] int attach 攻撃力
        "まおう", // [5-1-21] char name [4 * 3 +1] name
        // [5-1-23] char aa[256] アスキーアート
        "　Ａ＠Ａ\n"
        "ψ（▼皿▼）ψ",
        0, // command initialize as 0
        0, // target initialize as 0
    },
};

// [5-2] キャラクターの配列を宣言する　array of characters
CHARACTER characters[CHARACTER_MAX];

// [5-3] コマンドの名前を宣言する　declare command names
char commandNames[COMMAND_MAX][4 * 3 + 1] = {
    "たたかう", // [5-3-1]COMMAND_FIGHT
    "じゅもん", // [5-3-2]COMMAND_SPELL
    "にげる"    // [5-3-3]COMMAND_RUN
};
