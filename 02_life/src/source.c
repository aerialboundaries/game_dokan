/* Life Game */
/* 2026-04-29 */
/* console setting
 * font size = 72
 * font = 美咲ゴシック第2
 * widh 24
 * hight 13
 * write in alacritty-game.toml
 */

/* [1] Headers */
#include <locale.h> // for ncurses
#include <ncursesw/curses.h> // printwを使うために必要
// #include <stdio.h> // [1-1] 標準入出力ヘッダーをインクルードする
// ncursesではprintwを使うので不要
// #include <stdlib.h> // [1-2]
// 標準ライブラリヘッダをインクルードする（srandのため）::
#include <stdbool.h>
#include <string.h> // [1-3] 文字列操作ヘッダーをインクルードする
// #include <time.h> // [1-4] 時間管理ヘッダーをインクルードする
#include "console_manager.h" // ncurses初期化

// [2] 定数を定義する場所
#define FIELD_WIDTH (12) // [2-1] フィールドの幅を定義する
#define FIELD_HEIGHT (12) // [2-2] フィールドの高さを定義する

// [3] 変数を宣言する場所
// [3-1] フィールドを宣言する
bool field[FIELD_HEIGHT][FIELD_WIDTH]
    = { { 0, 1, 0 }, { 0, 0, 1 }, { 1, 1, 1 } };

// [4] 関数を宣言する場所
// [4-1] フィールドを描画する関数を宣言する
void DrawField()
{
    clear(); // [4-1-1] 画面をクリアする ncurse command
    // [4-1-2] フィールドのすべての行を反復する
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        // [4-1-3] フィールドのすべての列を反復する
        for (int x = 0; x < FIELD_WIDTH; x++) {
            // [4-1-4] セルが生きていれば「■」を、死んでいれば「　」を描画する
            // printw("%s", field[y][x] ? "■" : "　");
            printw("%s", field[y][x] ? "#" : " ");
        }
        printw("\n"); // [4-1-15] 1行描画するごとに改行する
    }
    refresh(); // ncurse command
}

// [4-2] 対象のセルと隣接する生きたセルの数を取得する関数を宣言する
int GetLivingCellsCount(int _x, int _y)
{
    int count = 0; // [4-2-1] 生きているセルを数えるカウンターを宣言する

    // [4-2-2] 対象のセルの上下1マスを反復する
    for (int y = _y - 1; y <= _y + 1; y++) {
        /*
        // [4-2-3] 上下にループさせない場合は、行が範囲内かどうかを判定する
        if ((y < 0 || y >= FIELD_HEIGHT)) {
          continue; // [4-2-4] 範囲外の行なのでスキップする
        }
        */

        // [4-2-5] 上下にループしたY座標を宣言する
        int roopedY = (FIELD_HEIGHT + y) % FIELD_HEIGHT;

        // [4-2-6] 対象のセルの左右1マスを反復する
        for (int x = _x - 1; x <= _x + 1; x++) {
            /*
            // [4-2-7] 左右にループさせない場合は、列が範囲内かどうかを判定する
            if ((x < 0) || x >= FIELD_WIDTH) {
              continue; // [4-2-8] 範囲外の列なのでスキップする
            }
            */

            // [4-2-9] 左右にループしたX座標を宣言する
            int roopedX = (FIELD_WIDTH + x) % FIELD_WIDTH;

            // [4-2-10] 対象の座標が、中心のセルと同じかどうかを判定する
            if ((roopedX == _x) && (roopedY == _y)) {
                continue; // [4-2-11] 対象の座標をスキップする
            }
            // [4-2-12] 対象のセルが生きていれば1を、死んでいれば0を加算する
            count += field[roopedY][roopedX];
        }
    }
    return count; // [4-2-13] 生きているセルの数を返す
}

// [4-3] 1ステップ分のシミュレーションを実行する関数を宣言する
void StepSimulation()
{
    // [4-3-1] 次の世代のフィールドを宣言する
    bool nextField[FIELD_HEIGHT][FIELD_WIDTH] = { false };

    // [4-3-2] すべての行を反復する
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        // [4-3-3] すべての列を反復する
        for (int x = 0; x < FIELD_WIDTH; x++) {
            // [4-3-4] 対象のセルと隣接する、生きているセルの数を宣言する
            int livingCellCount = GetLivingCellsCount(x, y);

            // [4-3-5] 隣接する生きたセルの数で分岐する
            if (livingCellCount <= 1) { // [4-3-5] 1個なら
                // [4-3-6] 対象のセルを死滅させる
                nextField[y][x] = false;
            } else if (livingCellCount == 2) {
                // [4-3-7] 2個なら
                // [4-3-8] 現状維持
                nextField[y][x] = field[y][x];
            } else if (livingCellCount == 3) {
                // [4-3-9] 3個なら
                // [4-3-10] 対象のセルを誕生／生存させる
                nextField[y][x] = true;
            } else {
                // [4-3-11] 4つ以上なら
                // [4-3-12] 対象のセルを死滅させる
                nextField[y][x] = false;
            }
        }
    }
    // [4-3-13] 次のステップのフィールドを、現在のフィールドにコピーする
    memcpy(field, nextField, sizeof(field));
}

// [4-5] プログラム実行の開始点を宣言する
int main(void)
{

    /* to use Japanese mult byte for ncurses */
    setlocale(LC_ALL, "");
    /* --- 最初に一度だけ初期化 ncurses--- */
    init_console();

    /* ここからゲーム道館プログラム */
    // [4-5-6] メインループ
    while (1) {
        DrawField(); // [4-5-11] フィールドを描画する関数を呼び出す
        getch(); // [4-5-12] キーボード入力を待つ ncurse command
        StepSimulation(); // [4-5-13] シミュレーションを進める
    }

    /* ここまでゲーム道館プログラム */

    /* --- ncurses 最後に必ず終了処理 --- */
    close_console();

    // nucursesのwindowから抜けて標準出力に戻っているのでprintfを使う
    printf("Program ended safely.\n");
    return 0;
}
