/* Manage console
 * 2026-04-23
 * by Gemini
 */
#ifndef CONSOLE_MANAGER_H
#define CONSOLE_MANAGER_H

/* ncursesの初期設定を一括で行います */
void init_console(void);

/* 終了時にターミナルの設定を元に戻します */
void close_console(void);

#endif
