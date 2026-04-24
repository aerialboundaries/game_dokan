/* console_manage.c
 * 2026-04-23
 * by Gemnini
 */

#include <ncurses.h>
#include "console_manager.h"

void init_console(void) {
    initscr();            /* ncursesを開始 */
    cbreak();             /* Enter待ちを無効化 */
    noecho();             /* 入力文字を表示しない */
    keypad(stdscr, TRUE); /* 特殊キーの取得を有効化 */
}

void close_console(void) {
    endwin();             /* ncursesを終了 */
}
