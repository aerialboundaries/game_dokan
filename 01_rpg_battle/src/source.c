/* battle.c */
/* 2026-04-23 */

/* Headers */
#include "console_manager.h"
#include "input_handler.h"
#include <ncurses.h> // printwを使うために必要
#include <stdio.h>

/* Constants */

/* enums */
// monsters
enum {
  MONSTER_PLAYER, // player
  MONSTER_MAX     // kinds of monster
};

// kinds of characters
enum { CHARACTER_PLAYER, CHARACTER_MONSTER, CHARACTER_MAX };

/* structs */
// struct of characters
typedef struct {
  int hp;               // HP
  int maxHP;            // Max HP
  int mp;               // MP
  int maxMP;            // Max MP
  char name[4 * 3 + 1]; // name 4文字 x 全角3バイト(utf8) + '\0'
} CHARACTER;

// variables
// monster's status
CHARACTER monsters[MONSTER_MAX] = {
    // MONSTER_PLAYER
    {
        15,         // int hp HP
        15,         // int maxHP  MaxHP
        15,         // int mp MP
        15,         // int Max HP
        "ゆうしゃ", // char name name
    },
};

// array of characters
CHARACTER characters[CHARACTER_MAX];

/* functions prototypes */
void Battle(); // battle scene

/* main */
int main(void) {
  /* --- 最初に一度だけ初期化 --- */
  init_console();

  printw("Console Initialized.\n");
  printw("Press any key (Press 'q' to quit)...\n");
  refresh();

  //   int ch;
  //   while (1) {
  //     /* input_handlerから _getch() を呼び出す */
  //     ch = _getch();
  //
  //     if (ch == 'q')
  //       break;
  //
  //     clear();
  //     printw("Key: %c (Code: %d)\n", ch, ch);
  //     printw("Keep pressing or press 'q' to quit.");
  //
  //     refresh();
  //   }

  /* ここにプログラムを書いてみる */
  Battle();

  /* ここまでプログラム */

  /* --- 最後に必ず終了処理 --- */
  close_console();

  printf("Program ended safely.\n");
  return 0;
}

// function implement
void Battle() { _getch(); }
