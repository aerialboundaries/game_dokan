// Game dokan reversi
// console setting
// font 72, screen width 22, height 11

/* settings for ncurses */
#define _XOPEN_SOURCE_EXTENDED // for gcc to undrestand ncurse header
#include <locale.h>            // for ncurses
#include <ncursesw/curses.h>   // printwを使うために必要

void init_console(void) // ncurses 初期化
{
  /* 最初にJapanese multi byte を ncursesで使えるようにlocaleを設定 */
  setlocale(LC_ALL, "");

  initscr(); /* ncursesを開始 */
  cbreak();  /* Enter待ちを無効化 winのconio.hでは標準 */
  noecho();  /* 入力文字を表示しない winのconio.hでは標準 */
  keypad(stdscr, TRUE); /* 特殊キーの取得を有効化 *winのconio.hでは標準 */
  /* [追加] カーソルを非表示にする */
  /* 0:非表示, 1:通常, 2:強調表示 */
  curs_set(0);
}

void close_console(void) { endwin(); /* ncursesを終了 */ }

/* setting for ncurses up to here */

/* programs of game_dokan */
// [1] headers
// [2] constants
#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

// [3] enums
enum {
  TURN_BLACK, // [3-1-1] 黒
  TURN_WHITE, // [3-1-2] 白
  TURN_NONE,  // [3-1-3] なし
  TURN_MAX    // [3-1-4] ターンの数
};

// [4] structs
// [4-1] ベクトル構造体を宣言する
typedef struct {
  int x, y; // [4-1-1] 座標
} VEC2;

// [5] variables
const char *diskAA[TURN_MAX] = {
    "⚫️", // [5-1-1]TURN_BLACK 黒い石が置かれている
    "⚪️", // [5-1-2]TURN_WHITE 白い石が置かれている
    "・"  // [5-1-3]TURN_NONE 石が置かれていない
};

// [5-5] 盤面の各マスの状態を宣言する
int board[BOARD_HEIGHT][BOARD_WIDTH];

VEC2 cursorPosition; // [5-6] カーソルの座標を宣言する

// [6] functions
// [6-5] 画面を描画する関数を宣言する
void DrawScreen(void) {
  // 画面を消去して左上(0, 0)にカーソルを戻す  -- ncursesのため
  clear();

  // [6-5-2] すべての行を反復する
  for (int y = 0; y < BOARD_HEIGHT; y++) {
    // [6-5-3] すべての列を反復する
    for (int x = 0; x < BOARD_WIDTH; x++) {
      printw("%s", diskAA[board[y][x]]); // [6-5-4] 石を描画する
    }

    if (y == cursorPosition.y) {
      printw("←"); //[6-5-7] カーソルを描画する
    }

    printw("\n"); // [6-5-8] 行の描画の最後に改行する
  }
  refresh(); // ncurses
}

// [6-7] ゲームを初期化する関数を宣言する
void init(void) {
  // [6=7-1} 盤面のすべての列を反復する
  for (int y = 0; y < BOARD_HEIGHT; y++) {
    // [6-7-2] 盤面のすべての行を反復する
    for (int x = 0; x < BOARD_WIDTH; x++) {
      // [6-7-3] 対象のマスを石が置かれていない状態にする
      board[y][x] = TURN_NONE;
    }
  }
  // [6-7-4] 盤面中央の右上と左下に黒い石を置く
  board[4][3] = board[3][4] = TURN_BLACK;

  // [6-7-5] 盤面中央の左上と右下に白い石を置く
  board[3][3] = board[4][4] = TURN_WHITE;

  DrawScreen(); // [6-7-8] 画面を描画する関数を呼び出す
}

// [6-9] プログラムの開始点を宣言する
int main(void) {
  // ncurses をスタート
  init_console();

  // [6-9-6] メインループ
  while (1) {
    init(); // [6-9-5] ゲームを初期化する関数を呼び出す
  }

  return 0;
}
