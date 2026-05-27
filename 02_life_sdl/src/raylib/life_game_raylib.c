#include "raylib.h"
#include <stdbool.h>
#include <string.h>


/* [1] 定数定義 */
#define FIELD_WIDTH 60  /* フィールドの横幅（セル数） */
#define FIELD_HEIGHT 40 /* フィールドの縦幅（セル数） */
#define CELL_SIZE 15    /* 1セルの描画サイズ（ピクセル） */

#define WINDOW_WIDTH (FIELD_WIDTH * CELL_SIZE)
#define WINDOW_HEIGHT (FIELD_HEIGHT * CELL_SIZE)

/* [2] グローバル変数 */
bool field[FIELD_HEIGHT][FIELD_WIDTH] = {0};

/* [3] 関数宣言 */


/* 隣接する生きたセルを数える（アルゴリズムは元のものを完全踏襲） */
int GetLivingCellsCount(int _x, int _y) {
  int count = 0;
  for (int y = _y - 1; y <= _y + 1; y++) {
    int loopedY = (FIELD_HEIGHT + y) % FIELD_HEIGHT;
    for (int x = _x - 1; x <= _x + 1; x++) {
      int loopedX = (FIELD_WIDTH + x) % FIELD_WIDTH;

      if (loopedX == _x && loopedY == _y)
        continue;
      count += field[loopedY][loopedX];
    }
  }
  return count;

}


/* 1世代進める */
void StepSimulation() {

  bool nextField[FIELD_HEIGHT][FIELD_WIDTH] = {false};
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      int livingCellCount = GetLivingCellsCount(x, y);
      if (livingCellCount <= 1) {
        nextField[y][x] = false;

      } else if (livingCellCount == 2) {
        nextField[y][x] = field[y][x];
      } else if (livingCellCount == 3) {
        nextField[y][x] = true;
      } else {
        nextField[y][x] = false;
      }
    }
  }
  memcpy(field, nextField, sizeof(field));
}


/* メイン関数 */
int main(void) {
  /* ウィンドウの初期化 */
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib Life Game");

  /* 元のコードの SDL_Delay(100) に合わせて、FPSを10に設定（1秒間に10回更新） */
  SetTargetFPS(10);


  /* 初期配置（グライダーなど） */
  field[1][2] = true;
  field[2][3] = true;
  field[3][1] = true;
  field[3][2] = true;
  field[3][3] = true;


  bool paused = false;

  /* メインループ（ESCキーまたはウィンドウの閉じるボタンで自動終了） */
  while (!WindowShouldClose()) {
    /* イベント処理（スペースキーで一時停止/再開） */
    if (IsKeyPressed(KEY_SPACE)) {
      paused = !paused;
    }


    /* シミュレーション更新 */
    if (!paused) {
      StepSimulation();
    }

    /* 描画処理 */
    BeginDrawing();
    ClearBackground(BLACK); /* 画面を黒でクリア */

    /* セルの描画 */
    for (int y = 0; y < FIELD_HEIGHT; y++) {
      for (int x = 0; x < FIELD_WIDTH; x++) {
        if (field[y][x]) {
          /* 生きているセルは鮮やかな緑色（LIME）で塗る */
          /* グリッド感（隙間）を出すためにサイズを-1しています */
          DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1, LIME);
        }
      }
    }


    /* 一時停止中の場合は画面にテキストを表示（raylibならではの簡単表示） */
    if (paused) {
      DrawText("PAUSED", 10, 10, 20, RAYWHITE);
    }

    EndDrawing();
  }

  /* 終了処理 */
  CloseWindow();

  return 0;
}
