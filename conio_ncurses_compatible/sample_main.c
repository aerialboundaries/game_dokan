#include "console_manager.h"
#include "input_handler.h"
#include <ncurses.h> // printwを使うために必要
#include <stdio.h>

int main(void) {
  /* --- 最初に一度だけ初期化 --- */
  init_console();

  printw("Console Initialized.\n");
  printw("Press any key (Press 'q' to quit)...\n");
  refresh();

  int ch;
  while (1) {
    /* input_handlerから _getch() を呼び出す */
    ch = _getch();

    if (ch == 'q')
      break;

    clear();
    printw("Key: %c (Code: %d)\n", ch, ch);
    printw("Keep pressing or press 'q' to quit.");

    refresh();
  }

  /* --- 最後に必ず終了処理 --- */
  close_console();

  printf("Program ended safely.\n");
  return 0;
}
