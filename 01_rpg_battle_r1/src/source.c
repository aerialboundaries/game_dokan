/* battle.c */
/* 2026-04-23 */
/* console setting
 * font size = 72
 * font = 美咲ゴシック第2
 * widh 32
 * hight 10
 * write in alacritty-game.toml
 */

/* [1] Headers */
#include "console_manager.h"
#include <locale.h>  // for ncurses
#include <ncurses.h> // printwを使うために必要
// #include <stdio.h> // [1-1] 標準入出力ヘッダーをインクルードする
// ncursesではprintwを使うので不要
#include <stdlib.h> // [1-2] 標準ライブラリヘッダをインクルードする（srandのため）::
#include <time.h>   // [1-4] 時間管理ヘッダーをインクルードする

// [1-1] My headers
#include "battle_function.h" // Battle_functionの関数をインクルードする
#include "types.h"           // 定数の定義

/* [6-6] main */
int main(void) {

  /* to use Japanese mult byte for ncurses */
  setlocale(LC_ALL, "");
  /* --- 最初に一度だけ初期化 ncurses--- */
  init_console();

  /* ここからゲーム道館プログラム */
  // [6-6-1] 乱数をシャッフルする
  srand((unsigned int)time(NULL));

  // [6-6-2] ゲームを初期化する関数を呼び出す
  Init();

  // [6-6-3] 戦闘シーンの関数を呼び出す call battle
  Battle(MONSTER_BOSS);

  /* ここまでプログラム */

  /* --- ncurses 最後に必ず終了処理 --- */
  close_console();

  printw("Program ended safely.\n");
  return 0;
}
