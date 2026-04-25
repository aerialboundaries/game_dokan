/* console_manage.c
 * 2026-04-23
 * by Gemnini
 */

#include "console_manager.h"
#include <ncurses.h>

void init_console(void) {
  initscr(); /* ncursesを開始 */
  cbreak();  /* Enter待ちを無効化 winのconio.hでは標準 */
  noecho();  /* 入力文字を表示しない winのconio.hでは標準 */
  keypad(stdscr, TRUE); /* 特殊キーの取得を有効化 *winのconio.hでは標準 */
}

void close_console(void) { endwin(); /* ncursesを終了 */ }
