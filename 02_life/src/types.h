#ifndef TYPES_H
#define TYPES_H

/* [2] Constants */
#define SPELL_COST 3 // [2-1] 呪文の消費MPを定義する

/* [3] enums */
// [3-1] モンスターの種類を定義する
enum {
  MONSTER_PLAYER, // [3-1-1] player
  MONSTER_SLIME,  // [3-1-2] slime
  MONSTER_BOSS,   // [3-1-3] 魔王
  MONSTER_MAX     // [3-1-4] モンスターの種類の数
};

// [3-2] キャラクターの種類を定義する　kinds of characters
enum {
  CHARACTER_PLAYER,  // [3-2-1] プレイヤー
  CHARACTER_MONSTER, // [3-2-2] モンスター
  CHARACTER_MAX      //[3-2-3] キャラクターの種類の数
};

// [3-3] コマンドの種類を定義する
enum {
  COMMAND_FIGHT, // [3-3-1] 戦う　fight
  COMMAND_SPELL, // [3-3-2] 呪文　spell
  COMMAND_RUN,   // [3-3-3] 逃げる　runaway
  COMMAND_MAX    // [3-3-4] コマンドの種類の数　number of commands
};

/* [4] structs */
// [4-1]struct of characters
typedef struct {
  int hp;               // [4-1-1] HP
  int maxHP;            // [4-1-2] Max HP
  int mp;               // [4-1-3] MP
  int maxMP;            // [4-1-4] Max MP
  int attack;           // [4-1-5] 攻撃力
  char name[4 * 3 + 1]; // [4-1-6] name 4文字 x 全角3バイト(utf8) + '\0'
  char aa[256];         // [4-1-7] ASCII art
  int command;          // [4-1-8] command
  int target;           // [4-1-9] 攻撃対象
} CHARACTER;

#endif
