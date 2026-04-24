// [1]ヘッダーをインクルードする場所

#include <stdio.h>  // [1-1]標準入出力ヘッダーをインクルードする
#include <stdlib.h> // [1-2]標準ライブラリヘッダーをインクルードする
#include <string.h> // [1-3]文字列操作ヘッダーをインクルードする
#include <time.h>   // [1-4]時間管理ヘッダーをインクルードする
#include <conio.h>  // [1-5]コンソール入出力ヘッダーをインクルードする

// [2]定数を定義する場所

#define FIELD_WIDTH         (12)            // [2-1]フィールドの幅を定義する
#define FIELD_HEIGHT        (18)            // [2-2]フィールドの高さを定義する

#define BLOCK_WIDTH_MAX     (4)             // [2-3]ブロックの最大幅を定義する
#define BLOCK_HEIGHT_MAX    (4)             // [2-4]ブロックの最大高さを定義する

#define FPS                 (1)             // [2-5]1秒当たりの描画頻度を定義する
#define INTERVAL            (1000 / FPS)    // [2-6]描画間隔（ミリ秒）を定義する

// [3]列挙定数を定義する場所

// [3-1]ブロックの種類を定義する
enum
{
    BLOCK_NONE, // [3-1-1]ブロックなし
    BLOCK_HARD, // [3-1-2]消せないブロック
    BLOCK_SOFT, // [3-1-3]消せるブロック
    BLOCK_FALL, // [3-1-4]落下ブロック
    BLOCK_MAX   // [3-1-5]ブロックの種類の数
};

// [3-2]落下ブロックの種類を定義する
enum
{
    BLOCK_SHAPE_I,  // [3-2-1]I型
    BLOCK_SHAPE_L,  // [3-2-2]L型
    BLOCK_SHAPE_MAX // [3-2-3]落下ブロックの種類の数
};

// [4]構造体を宣言する場所

// [4-1]落下ブロックの形状の構造体を宣言する
typedef struct {
    int size;                                           // [4-1-1]幅と高さ
    bool pattern[BLOCK_HEIGHT_MAX][BLOCK_WIDTH_MAX];    // [4-1-2]形状
} BLOCKSHAPE;

// [4-2]落下ブロックの構造体を宣言する
typedef struct {
    int x, y;           // [4-2-1]座標
    BLOCKSHAPE shape;   // [4-2-2]形状
} BLOCK;

// [5]変数を宣言する場所

// [5-1]落下ブロックの形状を宣言する
const BLOCKSHAPE blockShapes[BLOCK_SHAPE_MAX] =
{
    // [5-1-1]BLOCK_SHAPE_I I型
    {
        3,// [5-1-2]int size    幅と高さ

        // [5-1-3]bool pattern[BLOCK_HEIGHT_MAX][BLOCK_WIDTH_MAX]   形状
        {
            {0,1,0},
            {0,1,0},
            {0,1,0}
        }
    },

    // [5-1-4]BLOCK_SHAPE_L L型
    {
        3,// [5-1-5]int size    幅と高さ

        // [5-1-6]bool pattern[BLOCK_HEIGHT_MAX][BLOCK_WIDTH_MAX]   形状
        {
            {0,1,0},
            {0,1,1},
            {0,0,0}
        }
    },
};

// [5-2]フィールドを宣言する
int field[FIELD_HEIGHT][FIELD_WIDTH];

// [5-3]フィールドの初期状態を宣言する
int defaultField[FIELD_HEIGHT][FIELD_WIDTH] =
{
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,1,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,1,1,1},
    {1,1,1,1,0,0,0,0,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1}
};

BLOCK block;// [5-4]落下ブロックを宣言する

// [6]関数を宣言する場所

// [6-1]落下ブロックとフィールドの当たり判定を行う関数を宣言する
bool BlockIntersectField()
{
    // [6-1-1]落下ブロックのすべての行を反復する
    for (int y = 0; y < block.shape.size; y++)
    {
        // [6-1-2]落下ブロックのすべての列を反復する
        for (int x = 0; x < block.shape.size; x++)
        {
            // [6-1-3]対象のマスにブロックがあるかどうかを判定する
            if (block.shape.pattern[y][x])
            {
                // [6-1-4]ブロックのフィールド上の列を宣言する
                int globalX = block.x + x;

                // [6-1-5]ブロックのフィールド上の行を宣言する
                int globalY = block.y + y;

                // [6-1-6]ブロックとフィールドの当たり判定を行う
                if ((globalX < 0)                   // 列が左外かどうか
                    || (globalX >= FIELD_WIDTH)     // 列が右外かどうか
                    || (globalY < 0)                // 行が上外かどうか
                    || (globalY >= FIELD_HEIGHT)    // 行が下外かどうか

                    // フィールド上にブロックがあるかどうか
                    || (field[globalY][globalX] != BLOCK_NONE))
                {
                    return true;// [6-1-7]当たったという結果を返す
                }
            }
        }
    }

    return false;// [6-1-8]当たらなかったという結果を返す
}

// [6-2]そろった行のブロックを削除する関数を宣言する
void EraseLine()
{
    // [6-2-1]すべての行を反復する
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        // [6-2-2]その行がそろったかどうかのフラグを宣言する
        bool completed = true;

        // [6-2-3]すべての列を反復する
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            // [6-2-4]対象のマスにブロックがないかどうか判定する
            if (field[y][x] == BLOCK_NONE)
            {
                completed = false;// [6-2-5]そろわなかった

                break;// [6-2-6]その行のチェックを抜ける
            }
        }

        // [6-2-7]その行がそろったかどうか判定する
        if (completed)
        {
            // [6-2-8]すべての列を反復する
            for (int x = 0; x < FIELD_WIDTH; x++)
            {
                // [6-2-9]対象のマスが消せるブロックなら
                if (field[y][x] == BLOCK_SOFT)
                {
                    // [6-2-10]対象のマスのブロックを消す
                    field[y][x] = BLOCK_NONE;
                }
            }

            // [6-2-11]すべての列を反復する
            for (int x = 0; x < FIELD_WIDTH; x++)
            {
                // [6-2-12]消えた行から先頭の行まで反復する
                for (int y2 = y; y2 >= 0; y2--)
                {
                    // [6-2-13]消せないブロックが見つかったら反復を抜ける
                    if(field[y2][x] == BLOCK_HARD)
                        break;

                    // [6-2-14]先頭の行かどうかを判定する
                    if (y2 == 0)
                    {
                        // [6-2-15]ブロックを消す
                        field[y2][x] = BLOCK_NONE;
                    }

                    // [6-2-16]先頭の行でなければ
                    else
                    {
                        // [6-2-17]上のマスが消せないブロックでないかどうかを判定する
                        if (field[y2 - 1][x] != BLOCK_HARD)
                        {
                            // [6-2-18]上のマスを下のマスにコピーする
                            field[y2][x] = field[y2 - 1][x];
                        }
                    }
                }
            }
        }
    }
}

// [6-3]画面を描画する関数を宣言する
void DrawScreen()
{
    // [6-3-1]画面バッファーを宣言する
    int screen[FIELD_HEIGHT][FIELD_WIDTH];

    // [6-3-2]フィールドを画面バッファーにコピーする
    memcpy(screen, field, sizeof field);

    // [6-3-3]フィールドのすべての行を反復する
    for (int y = 0; y < BLOCK_HEIGHT_MAX; y++)
    {
        // [6-3-4]フィールドのすべての列を反復する
        for (int x = 0; x < BLOCK_WIDTH_MAX; x++)
        {
            // [6-3-5]ブロックがあるかどうかを判定する
            if (block.shape.pattern[y][x])
            {
                // [6-3-6]画面バファーに落下ブロックを書き込む
                screen[block.y + y][block.x + x] = BLOCK_FALL;
            }
        }
    }

    // [6-3-7]画面をクリアする
    system("cls");

    // [6-3-8]フィールドのすべての行を反復する
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        // [6-3-9]フィールドのすべての列を反復する
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            // [6-3-10]ブロックの種類で分岐する
            switch (screen[y][x])
            {
            case BLOCK_NONE: printf("　");    break;// [6-3-11]ブロックなし
            case BLOCK_HARD: printf("＋");    break;// [6-3-12]消せないブロック
            case BLOCK_SOFT: printf("◆");    break;// [6-3-13]消せるブロック
            case BLOCK_FALL: printf("◇");    break;// [6-3-14]落下ブロック
            }
        }

        printf("¥n");// [6-3-15]改行する
    }
}

// [6-4]落下ブロックを回転させる関数を宣言する
void RotateBlock()
{
    // [6-4-1]回転後のブロックを宣言する
    BLOCK rotatedBlock = block;

    // [6-4-2]落下ブロックのすべての行を反復する
    for (int y = 0; y < block.shape.size; y++)
    {
        // [6-4-3]落下ブロックのすべての列を反復する
        for (int x = 0; x < block.shape.size; x++)
        {
            // [6-4-4]回転後のブロックの形状を作成する
            rotatedBlock.shape.pattern[block.shape.size - 1 - x][y] =
                block.shape.pattern[y][x];
        }
    }

    // [6-4-5]回転後のブロックを適用する
    block = rotatedBlock;
}

// [6-5]落下ブロックを初期化する関数を宣言する
void InitBlock()
{
    // [6-5-1]落下ブロックの形状を、ランダムに設定する
    block.shape = blockShapes[rand() % BLOCK_SHAPE_MAX];

    // [6-5-2]落下ブロックの列を中心にする
    block.x = FIELD_WIDTH / 2 - block.shape.size / 2;

    block.y = 0;// [6-5-3]落下ブロックの行を先頭にする

    // [6-5-4]落下ブロックを回転させる回数を宣言する
    int rotateCount = rand() % 4;

    // [6-5-5]落下ブロックを回転させる回数だけ反復する
    for (int i = 0; i < rotateCount; i++)
    {
        // [6-5-6]落下ブロックを回転させる
        RotateBlock();
    }
}

// [6-6]ゲームを初期化する関数を宣言する
void Init()
{
    // [6-6-1]フィールドに初期状態をコピーする
    memcpy(field, defaultField, sizeof field);

    InitBlock();// [6-6-2]ブロックを初期化する関数を呼び出す

    DrawScreen();// [6-6-3]画面を描画する関数を呼び出す
}

// [6-7]落下ブロックを落下させる関数を宣言する
void FallBlock()
{
    BLOCK lastBlock = block;// [6-7-1]ブロックの移動前の状態を宣言する

    block.y++;// [6-7-2]ブロックを落下させる

    // [6-7-3]ブロックとフィールドが重なったかどうか判定する
    if (BlockIntersectField())
    {
        // [6-7-4]落下ブロックを移動前の状態に戻す
        block = lastBlock;

        // [6-7-5]落下ブロックのすべての行を反復する
        for (int y = 0; y < BLOCK_HEIGHT_MAX; y++)
        {
            // [6-7-6]落下ブロックのすべての列を反復する
            for (int x = 0; x < BLOCK_WIDTH_MAX; x++)
            {
                // [6-7-7]ブロックがあるマスかどうかを判定する
                if (block.shape.pattern[y][x])
                {
                    // [6-7-8]フィールドに消せるブロックを書き込む
                    field[block.y + y][block.x + x] = BLOCK_SOFT;
                }
            }
        }

        // [6-7-9]そろったブロックを削除する関数を呼び出す
        EraseLine();

        // [6-7-10]ブロックを初期化する関数を呼び出す
        InitBlock();

        // [6-7-11]ブロックとフィールドが重なったかどうか判定する
        if (BlockIntersectField())
        {
            Init();// [6-7-12]ゲームを初期化する
        }
    }

    DrawScreen();// [6-7-13]画面を描画する関数を呼び出す
}

// [6-8]プログラム実行の開始点を宣言する
int main()
{
    srand((unsigned int)time(NULL));// [6-8-1]乱数をシャッフルする

    // [6-8-2]ゲームを初期化する関数を呼び出す
    Init();

    clock_t lastClock = clock();// [6-8-3]前回の更新時刻を保持する変数を宣言する

    // [6-8-4]メインループ
    while (1)
    {
        clock_t newClock = clock();// [6-8-5]現在の時刻を宣言する
        
        // [6-8-6]待機時間を経過したら
        if (newClock >= lastClock + INTERVAL)
        {
            lastClock = newClock;// [6-8-7]前回の更新時刻を現在の時刻で更新する

            FallBlock();// [6-8-8]落下ブロックを落下させる関数を呼び出す
        }

        // [6-8-9]キーボード入力があったかどうか判定する
        if (_kbhit())
        {
            // [6-8-10]ブロックの移動前の状態を宣言する
            BLOCK lastBlock = block;

            // [6-8-11]入力されたキーによって分岐する
            switch (_getch())
            {
            case 'w':       // [6-8-12]wキーが押されたら
                break;

            case 's':       // [6-8-13]sキーが押されたら
                block.y++;  // [6-8-14]ブロックを下に移動する
                break;

            case 'a':       // [6-8-15]aキーが押されたら
                block.x--;  // [6-8-16]ブロックを左に移動する
                break;

            case 'd':       // [6-8-17]dキーが押されたら
                block.x++;  // [6-8-18]ブロックを右に移動する
                break;

            default:// [6-8-19]移動以外のキーが押されたら

                // [6-8-20]落下ブロックを回転させる関数を呼び出す
                RotateBlock();

                break;
            }

            // [6-8-21]ブロックとフィールドが重なったかどうか判定する
            if (BlockIntersectField())
            {
                // [6-8-22]ブロックを移動前の状態に戻す
                block = lastBlock;
            }
            // [6-8-23]ブロックとフィールドが重ならなければ
            else
            {
                // [6-8-24]画面を描画する関数を呼び出す
                DrawScreen();
            }
        }
    }
}