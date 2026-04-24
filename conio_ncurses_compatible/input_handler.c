/* input handler.c
 * 2026-04-23
 * by Gemini
 */

#include "input_handler.h"
#include <ncurses.h>

int _getch(void) {

  /* ここでは initscr() は呼びません。
     console_manager によって既に開始されていることを前提とします。
  */
  return getch();
}
