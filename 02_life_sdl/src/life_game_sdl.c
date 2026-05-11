#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
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

/* 隣接する生きたセルを数える（アルゴリズムは以前のものを踏襲） */
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

int main(int argc, char *argv[]) {
  /* SDLの初期化 */
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL初期化失敗: %s", SDL_GetError());
    return 1;
  }

  /* ウィンドウとレンダラー（描画器）の作成 */
  SDL_Window *window = NULL;

  SDL_Renderer *renderer = NULL;
  if (!SDL_CreateWindowAndRenderer("SDL3 Life Game", WINDOW_WIDTH,
                                   WINDOW_HEIGHT, 0, &window, &renderer)) {
    SDL_Log("ウィンドウ作成失敗: %s", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  /* 初期配置（グライダーなど） */
  field[1][2] = true;
  field[2][3] = true;
  field[3][1] = true;
  field[3][2] = true;
  field[3][3] = true;

  bool quit = false;
  bool paused = false;

  SDL_Event event;

  /* メインループ */
  while (!quit) {
    /* イベント処理（入力を受け付ける） */
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        quit = true;
      } else if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_SPACE) {
          paused = !paused; /* スペースキーで一時停止/再開 */
        }
      }
    }

    /* シミュレーション更新 */
    if (!paused) {
      StepSimulation();
    }

    /* 描画処理 */
    /* 画面を黒でクリア */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer);

    /* セルの描画 */

    for (int y = 0; y < FIELD_HEIGHT; y++) {
      for (int x = 0; x < FIELD_WIDTH; x++) {
        if (field[y][x]) {
          /* 生きているセルは緑色で塗る */

          SDL_SetRenderDrawColor(renderer, 50, 255, 50, 255);
          SDL_FRect rect = {(float)x * CELL_SIZE, (float)y * CELL_SIZE,
                            (float)CELL_SIZE - 1, (float)CELL_SIZE - 1};
          SDL_RenderFillRect(renderer, &rect);
        }
      }
    }

    /* 画面に反映 */

    SDL_RenderPresent(renderer);

    /* 速度調整（ミリ秒） */
    SDL_Delay(100);
  }

  /* 終了処理 */
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
