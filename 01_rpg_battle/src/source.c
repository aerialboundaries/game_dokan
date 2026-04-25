/* battle.c */
/* 2026-04-23 */
/* console setting
 * font size = 72
 * font = misaki
 * widh 32
 * hight 10
 * write in alacritty-game.toml
 */

/* [1] Headers */
#include "console_manager.h"
#include "input_handler.h"
#include <locale.h>  // for ncurses
#include <ncurses.h> // printwを使うために必要
// #include <stdio.h>

/* [2] Constants */

/* [3] enums */
// monsters
enum {
  MONSTER_PLAYER, // player
  MONSTER_SLIME,  // slime
  MONSTER_MAX     // kinds of monster
};

enum {
  COMMAND_FIGHT, // [3-3-1] fight
  COMMAND_SPELL, // [3-3-2] spell
  COMMAND_RUN,   // [3-3-3] runaway
  COMMAND_MAX    // [3-3-4] number of commands
};

// kinds of characters
enum { CHARACTER_PLAYER, CHARACTER_MONSTER, CHARACTER_MAX };

/* [4] structs */
// [4-1]struct of characters
typedef struct {
  int hp;               // HP
  int maxHP;            // Max HP
  int mp;               // MP
  int maxMP;            // Max MP
  char name[4 * 3 + 1]; // name 4文字 x 全角3バイト(utf8) + '\0'
  char aa[256];         // [4-1-7] ASCII art
  int command;          // [4-1-8] command
} CHARACTER;

/* [5] variables */
// [5-1] monster's status
CHARACTER monsters[MONSTER_MAX] = {
    // MONSTER_PLAYER
    {
        15,         // int hp HP
        15,         // int maxHP  MaxHP
        15,         // int mp MP
        15,         // int Max HP
        "ゆうしゃ", // char name name
        "",
        0, // doesn't have aa but declare as ""
    },

    // [5-1-8]MONSTER_SLIME
    {
        3,          // int hp
        3,          // int maxHP
        0,          // int mp MP
        0,          // int maxHP
        "スライム", // char name [4 * 3 +1] name
                    // [5-1-15] char aa[256] アスキーアート
        "／・Д・＼\n"
        "～～～～～",
        0,
    },
};

// array of characters
CHARACTER characters[CHARACTER_MAX];

/* [6] functions prototypes */
void Battle(int _monster);   // battle scene
void Init(void);             // initialize the game
void DrawBattleScreen(void); // draw battle sceen

/* [6-6] main */
int main(void) {
  /* to use Japanese mult byte for ncurses */
  setlocale(LC_ALL, "");
  /* --- 最初に一度だけ初期化 ncurses--- */
  init_console();
  // initialize game data (must be before drawing)
  Init();

  //  printw("Console Initialized.\n");
  //  printw("Press any key (Press 'q' to quit)...\n");
  //  refresh();

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
  // [6-6-3] call battle
  Battle(MONSTER_SLIME);

  /* ここまでプログラム */

  /* --- 最後に必ず終了処理 --- */
  close_console();

  printw("Program ended safely.\n");
  return 0;
}

/* [6] function implement */
// [6-4] Battle
void Battle(int _monster) {
  // initialize monster's status
  characters[CHARACTER_MONSTER] = monsters[_monster];

  DrawBattleScreen();

  // [6-4-5] display messages for battel scene
  printw("%sが　あらわれた！\n", characters[CHARACTER_MONSTER].name);

  //[6-4-6] wait for keybord input
  _getch();

  //[6-4-7] loop until battle ends
  while (1) {
    //[6-4-9] repeat characters
    for (int i = 0; i < CHARACTER_MAX; i++) {
      // [6-4-10] refresh battle scene
      DrawBattleScreen();

      // [6-4-11] separate with chosen commmand
      switch (characters[i].command) {
      case COMMAND_FIGHT: // [6-4-12] fight
                          // // [6-4-13] display message to fight
        printw("%sの　こうげき！\n", characters[i].name);

        // [6-4-14] wait for keyboard input
        _getch();
        break;
      case COMMAND_SPELL: // [6-4-22] spell
        break;
      case COMMAND_RUN: // [6-4-35] runaway
        break;
      }
    }
  }

} // battle scene

void Init(void) {
  characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
} // initialize the game

void DrawBattleScreen(void) {
  // [6-2-1] clear screen
  clear(); // ncursesの画面消去

  // display player name
  printw("%s\n", characters[CHARACTER_PLAYER]
                     .name); // ncurses needs printw insted of printf

  printw("ＨＰ : %d / %d  ＭＰ : %d / %d\n", characters[CHARACTER_PLAYER].hp,
         characters[CHARACTER_PLAYER].maxHP, characters[CHARACTER_PLAYER].mp,
         characters[CHARACTER_PLAYER].maxHP);

  printw("\n");

  //[6-2-5] draw ascii art of monster
  printw("%s", characters[CHARACTER_MONSTER].aa);

  //[6-2-6] display monster's hp
  printw("(ＨＰ：%d／%d)\n", characters[CHARACTER_MONSTER].hp,
         characters[CHARACTER_MONSTER].maxHP);

  //[6-2-7] one blank row
  printw("\n");

} // draw battle sceen
