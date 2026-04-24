// [1]ヘッダーをインクルードする場所

#include <stdio.h>  // [1-1]標準入出力ヘッダーをインクルードする
#include <stdlib.h> // [1-2]標準ライブラリヘッダーをインクルードする
#include <string.h> // [1-3]文字列操作ヘッダーをインクルードする
#include <time.h>   // [1-4]時間管理ヘッダーをインクルードする
#include <conio.h>  // [1-5]コンソール入出力ヘッダーをインクルードする
#include <vector>   // [1-6]ベクターヘッダーをインクルードする

// [2]定数を定義する場所

#define MAZE_WIDTH  (19)            // [2-1]迷路の幅を定義する
#define MAZE_HEIGHT (19)            // [2-2]迷路の高さを定義する

#define FPS         (2)             // [2-3]1秒あたりの更新頻度を定義する
#define INTERVAL    (1000 / FPS)    // [2-4]更新ごとの待機時間（ミリ秒）を定義する

// [3]列挙定数を定義する場所

// [3-1]キャラクターの種類を定義する
enum
{
    CHARACTER_PLAYER,   // [3-1-1]プレイヤー
    CHARACTER_RANDOM,   // [3-1-2]気まぐれモンスター
    CHARACTER_CHASE,    // [3-1-3]追いかけモンスター
    CHARACTER_AMBUSH,   // [3-1-4]先回りモンスター
    CHARACTER_SIEGE,    // [3-1-5]挟み撃ちモンスター
    CHARACTER_MAX       // [3-1-6]キャラクターの数
};

// [3-2]方向の種類を定義する
enum
{
    DIRECTION_UP,       // [3-2-1]上
    DIRECTION_LEFT,     // [3-2-2]左
    DIRECTION_DOWN,     // [3-2-3]下
    DIRECTION_RIGHT,    // [3-2-4]右
    DIRECTION_MAX       // [3-2-5]方向の数
};

// [4]構造体を宣言する場所

// [4-1]ベクトルの構造体を宣言する
typedef struct {
    int x, y;   // [4-1-1]座標
} VEC2;

// [4-2]キャラクターの構造体を宣言する
typedef struct {
    VEC2        position;           // [4-2-1]座標
    const VEC2  defaultPosition;    // [4-2-2]初期座標
    VEC2        lastPosition;       // [4-2-3]前回の座標
} CHARACTER;

// [5]変数を宣言する場所

// [5-1]迷路を宣言する
char maze[MAZE_HEIGHT][MAZE_WIDTH + 1];

// [5-2]迷路の初期状態を宣言する
const char defaultMaze[MAZE_HEIGHT][MAZE_WIDTH + 1] =
{
    "#########o#########",
    "#ooooooo#o#ooooooo#",
    "#o###o#o#o#o#o###o#",
    "#o# #o#ooooo#o# #o#",
    "#o###o###o###o###o#",
    "#ooooooooooooooooo#",
    "#o###o###o###o###o#",
    "#ooo#o#ooooo#o#ooo#",
    "###o#o#o###o#o#o###",
    "oooooooo# #oooooooo",
    "###o#o#o###o#o#o###",
    "#ooo#o#ooooo#o#ooo#",
    "#o###o###o###o###o#",
    "#oooooooo oooooooo#",
    "#o###o###o###o###o#",
    "#o# #o#ooooo#o# #o#",
    "#o###o#o#o#o#o###o#",
    "#ooooooo#o#ooooooo#",
    "#########o#########"
};

// [5-3]キャラクターの配列を宣言する
CHARACTER characters[CHARACTER_MAX] =
{
    // [5-3-1]CHARACTER_PLAYER  プレイヤー
    {
        {},         // [5-3-2]VEC2          position
        {9, 13},    // [5-3-3]const VEC2    defaultPosition
        {},         // [5-3-4]VEC2          lastPosition
    },

    // [5-3-5]CHARACTER_RANDOM  気まぐれモンスター
    {
        {},         // [5-3-6]VEC2          position
        {1, 1},     // [5-3-7]const VEC2    defaultPosition
        {},         // [5-3-8]VEC2          lastPosition
    },

    // [5-3-9]CHARACTER_CHASE   追いかけモンスター
    {
        {},         // [5-3-10]VEC2         position
        {17, 1},    // [5-3-11]const VEC2   defaultPosition
        {},         // [5-3-12]VEC2         lastPosition
    },

    // [5-3-13]CHARACTER_AMBUSH 先回りモンスター
    {
        {},         // [5-3-14]VEC2         position
        {1, 17},    // [5-3-15]const VEC2   defaultPosition
        {},         // [5-3-16]VEC2         lastPosition
    },

    // [5-3-17]CHARACTER_SIEGE      挟み撃ちモンスター
    {
        {},         // [5-3-18]VEC2         position
        {17, 17},   // [5-3-19]const VEC2   defaultPosition
        {},         // [5-3-20]VEC2         lastPosition
    }
};

// [5-4]方向のベクトルの配列を宣言する
VEC2 directions[DIRECTION_MAX] =
{
    { 0,-1},    // [5-4-1]DIRECTION_UP      上
    {-1, 0},    // [5-4-2]DIRECTION_LEFT    左
    { 0, 1},    // [5-4-3]DIRECTION_DOWN    下
    { 1, 0}     // [5-4-4]DIRECTION_RIGHT   右
};

// [6]関数を宣言する場所

// [6-1]ベクトルを加算する関数を宣言する
VEC2 Vec2Add(VEC2 _v0, VEC2 _v1)
{
    // [6-1-1]加算したベクトルを返す
    return
    {
        _v0.x + _v1.x,
        _v0.y + _v1.y
    };
}

// [6-2]ベクトルを減算する関数を宣言する
VEC2 Vec2Subtract(VEC2 _v0, VEC2 _v1)
{
    // [6-2-1]減算したベクトルを返す
    return
    {
        _v0.x - _v1.x,
        _v0.y - _v1.y
    };
}

// [6-3]ベクトルどうしが等しいかどうかを判定する関数を宣言する
bool Vec2Equal(VEC2 _v0, VEC2 _v1)
{
    // [6-3-1]ベクトルどうしが等しいかどうかを返す
    return (_v0.x == _v1.x) && (_v0.y == _v1.y);
}

// [6-4]上下左右にループした座標を取得する関数を宣言する
VEC2 GetLoopPosition(VEC2 _position)
{
    // [6-4-1]上下左右にループした座標を返す
    return
    {
        (MAZE_WIDTH + _position.x) % MAZE_WIDTH,
        (MAZE_HEIGHT + _position.y) % MAZE_HEIGHT
    };
}

// [6-5]ランダムな移動先を取得する関数を宣言する
VEC2 GetRandomPosition(CHARACTER _character)
{
    // [6-5-1]移動先の候補のリストを宣言する
    std::vector<VEC2> positions;

    // [6-5-2]すべての方向を反復する
    for (int i = 0; i < DIRECTION_MAX; i++)
    {
        // [6-5-3]各方向の座標を宣言する
        VEC2 newPosition = Vec2Add(_character.position, directions[i]);

        // [6-5-4]対象の座標を上下左右にループさせる
        newPosition = GetLoopPosition(newPosition);

        // [6-5-5]対象の座標に移動可能かどうかを判定する
        if (
            // 壁ではない
            (maze[newPosition.y][newPosition.x] != '#')

            // かつ前回の座標と同じではない
            && (!Vec2Equal(newPosition, _character.lastPosition))
        )
        {
            // [6-5-6]対象の座標を移動先の候補のリストに追加する
            positions.push_back(newPosition);
        }
    }

    // [6-5-7]移動先の候補の中からランダムで座標を返す
    return positions[rand() % positions.size()];
}

// [6-6]目標地点への最短経路の最初の座標を取得する関数を宣言する
VEC2 GetChasePosition(CHARACTER _character, VEC2 _targetPosition)
{
    // [6-6-1]経路を探索すべき座標のリストを宣言する
    std::vector<VEC2> toCheckPositions;

    // [6-6-2]探索をするキャラクター自身の座標を探索すべき座標のリストに追加する
    toCheckPositions.push_back(_character.position);

    // [6-6-3]探索開始地点から各マスへの距離を保持する配列を宣言する
    int distances[MAZE_HEIGHT][MAZE_WIDTH];

    // [6-8-4]迷路のすべての行を反復する
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-6-5]迷路のすべての列を反復する
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-6-6]対象のマスへの距離を未設定として初期化する
            distances[y][x] = -1;
        }
    }

    // [6-6-7]探索をするキャラクター自身の座標への距離は0に設定する
    distances[_character.position.y][_character.position.x] = 0;

    // [6-6-8]探索開始地点から各マスへの経路を保持する配列を宣言する
    std::vector<VEC2> routes[MAZE_HEIGHT][MAZE_WIDTH];

    // [6-6-9]探索すべき座標のリストが空になるまで反復する
    while (!toCheckPositions.empty())
    {
        // [6-6-10]すべての方向を反復する
        for (int i = 0; i < DIRECTION_MAX; i++)
        {
            // [6-8-11]探索中の座標に隣接する各方向の座標を取得する
            VEC2 newPosition = Vec2Add(toCheckPositions.front(), directions[i]);

            // [6-6-12]対象の座標を上下左右にループさせた座標に変換する
            newPosition = GetLoopPosition(newPosition);

            // [6-6-13]対象の座標への距離を宣言する
            int newDistance =
                distances[toCheckPositions.front().y][toCheckPositions.front().x] + 1;

            // [6-6-14]対象の座標を探索すべきかどうかを判定する
            if (
                (
                	// 未設定である
                    (distances[newPosition.y][newPosition.x] < 0)

                    // もしくは最短経路である
                    || (newDistance < distances[newPosition.y][newPosition.x])
                )

                // かつ壁ではない
                && (maze[newPosition.y][newPosition.x] != '#')
            )
            {
                // [6-6-15]対象の座標への距離を更新する
                distances[newPosition.y][newPosition.x] = newDistance;

                // [6-6-16]対象の座標を探索すべき座標のリストへ追加する
                toCheckPositions.push_back(newPosition);

                // [6-6-17]対象の座標への経路を、1つ前の座標の経路で初期化する
                routes[newPosition.y][newPosition.x] =
                    routes[toCheckPositions.front().y][toCheckPositions.front().x];

                // [6-6-18]対象の座標への経路に、対象の座標を追加する
                routes[newPosition.y][newPosition.x].push_back(newPosition);
            }
        }

        // [6-6-19]探索すべき座標のリストから先頭の座標を削除する
        toCheckPositions.erase(toCheckPositions.begin());
    }

    // [6-6-20]目標地点への経路があるかどうかを判定する
    if (
        // 経路がある
        (!routes[_targetPosition.y][_targetPosition.x].empty())

        // かつ前回の座標と違う座標であれば
        && (!Vec2Equal(
            routes[_targetPosition.y][_targetPosition.x].front(),
            _character.lastPosition)
        )
    )
    {
        // [6-6-21]目標地点への経路の1つ目の座標を返す
        return routes[_targetPosition.y][_targetPosition.x].front();
    }
    // [6-6-22]目標地点への経路がなければ
    else
    {
        // [6-6-23]ランダムな座標を返す
        return GetRandomPosition(_character);
    }
}

// [6-7]迷路を描画する関数を宣言する
void DrawMaze()
{
    // [6-7-1]画面バッファーを宣言する
    char screen[MAZE_HEIGHT][MAZE_WIDTH + 1];

    // [6-7-2]画面バッファーに迷路をコピーする
    memcpy(screen, maze, sizeof maze);

    // [6-7-3]すべてのキャラクターを反復する
    for (int i = 0; i < CHARACTER_MAX; i++)
    {
        // [6-7-4]キャラクターの番号を画面バッファーに書き込む
        screen[characters[i].position.y][characters[i].position.x] = i;
    }

    system("cls");// [6-7-5]画面をクリアする

    // [6-7-6]迷路のすべての行を反復する
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-7-7]迷路のすべての列を反復する
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-7-8]マスを描画する
            switch (screen[y][x])
            {
            case ' ':               printf("　");    break;  // [6-7-9]床
            case '#':               printf("■");    break;  // [6-7-10]壁を描画する
            case 'o':               printf("・");    break;  // [6-7-11]ドット
            case CHARACTER_PLAYER:  printf("○");    break;  // [6-7-12]プレイヤー
            case CHARACTER_RANDOM:  printf("☆");    break;  // [6-7-13]気まぐれモンスター
            case CHARACTER_CHASE:   printf("凸");    break;  // [6-7-14]追いかけモンスター
            case CHARACTER_AMBUSH:  printf("◇");    break;  // [6-7-15]先回りモンスター
            case CHARACTER_SIEGE:   printf("凹");    break;  // [6-7-16]挟み撃ちモンスター
            }
        }

        // [6-7-17]1行描画するごとに改行する
        printf("¥n");
    }
}

// [6-8]ゲームを初期化する関数を宣言する
void Init()
{
    // [6-8-1]迷路に初期状態をコピーする
    memcpy(maze, defaultMaze, sizeof maze);

    // [6-8-2]すべてのキャラクターを反復する
    for (int i = 0; i < CHARACTER_MAX; i++)
    {
        // [6-8-3]キャラクターの座標を初期化する
        characters[i].position
            = characters[i].lastPosition
            = characters[i].defaultPosition;
    }
}

// [6-9]ゲームオーバーの関数を宣言する
bool IsGameOver()
{
    // [6-9-1]すべてのモンスターを反復する
    for (int i = CHARACTER_PLAYER + 1; i < CHARACTER_MAX; i++)
    {
        // [6-9-2]対象のモンスターとプレイヤーの座標が同じかどうかを判定する
        if (Vec2Equal(
            characters[i].position,                 // 対象のモンスターの座標
            characters[CHARACTER_PLAYER].position)) // プレイヤーの座標
        {
            // [6-9-3]画面をクリアする
            system("cls");

            // [6-9-4]迷路の高さの半分だけ反復する
            for (int j = 0; j < MAZE_HEIGHT / 2; j++)
            {
                // [6-9-5]改行する
                printf("¥n");
            }

            // [6-9-6]ゲームオーバーのメッセージを表示する
            printf("　　　　　ＧＡＭＥ　ＯＶＥＲ");

            // [6-9-7]キーボード入力を待つ
            _getch();

            // [6-9-8]ゲームオーバーになったという結果を返す
            return true;
        }
    }

    // [6-9-9]ゲームオーバーにならなかったという結果を返す
    return false;
}

// [6-10]エンディングの関数を宣言する
bool IsComplete()
{
    // [6-10-1]迷路のすべての行を反復する
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-10-2]迷路のすべての列を反復する
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-10-3]対象のマスがドットかどうかを判定する
            if (maze[y][x] == 'o')
            {
                // [6-10-4]クリアではないという結果を返す
                return false;
            }
        }
    }

    // [6-10-5]画面をクリアする
    system("cls");

    // [6-10-6]迷路の高さの半分だけ反復する
    for (int i = 0; i < MAZE_HEIGHT / 2; i++)
    {
        // [6-10-7]改行する
        printf("¥n");
    }

    // [6-10-8]エンディングのメッセージを表示する
    printf("　　ＣＯＮＧＲＡＴＵＬＡＴＩＯＮＳ！");

    // [6-10-9]キーボード入力を待つ
    _getch();

    // [6-10-10]クリアしたという結果を返す
    return true;
}

// [6-11]プログラムの実行開始点を宣言する
int main()
{
    // [6-11-1]乱数を現在の時刻でシャッフルする
    srand((unsigned int)time(NULL));

start:  // [6-11-2]ゲームの開始ラベル
    ;   // [6-11-3]空文

    // [6-11-4]ゲームを初期化する関数を呼び出す
    Init();

    // [6-11-5]迷路を描画する関数を呼び出す
    DrawMaze();

    // [6-11-6]前回の更新時刻を宣言する
    time_t lastClock = clock();

    // [6-11-7]メインループ
    while (1)
    {
        // [6-11-8]現在の時刻を宣言する
        time_t newClock = clock();

        // [6-11-9]前回の更新から待機時間が経過したかどうかを判定する
        if (newClock > lastClock + INTERVAL)
        {
            // [6-11-10]前回の更新時刻を現在の時刻で更新する
            lastClock = newClock;

            // [6-11-11]すべてのモンスターを反復する
            for (int i = CHARACTER_PLAYER + 1; i < CHARACTER_MAX; i++)
            {
                // [6-11-12]移動先の座標を宣言する
                VEC2 newPosition = characters[i].position;

                // [6-11-13]モンスターの種類によって分岐する
                switch (i)
                {
                    // [6-11-14]気まぐれモンスター
                case CHARACTER_RANDOM:

                    // [6-11-15]ランダムな移動先の座標を設定する
                    newPosition = GetRandomPosition(characters[i]);

                    break;

                // [6-11-16]追いかけモンスター
                case CHARACTER_CHASE:

                    // [6-11-17]プレイヤーを追いかける座標を設定する
                    newPosition =
                        GetChasePosition(characters[i], characters[CHARACTER_PLAYER].position);

                    break;

                // [6-11-18]先回りモンスター
                case CHARACTER_AMBUSH:
                {
                    // [6-11-19]プレイヤーの向きベクトルを宣言する
                    VEC2 playerDirection = Vec2Subtract(
                        characters[CHARACTER_PLAYER].position,
                        characters[CHARACTER_PLAYER].lastPosition);

                    // [6-11-20]目標地点を宣言する
                    VEC2 targetPosition = characters[CHARACTER_PLAYER].position;

                    // [6-11-21]3回反復する
                    for (int j = 0; j < 3; j++)
                    {
                        // [6-11-22]目標地点にプレイヤーの向きベクトルを加算する
                        targetPosition = Vec2Add(targetPosition, playerDirection);
                    }

                    // [6-11-23]目標地点を上下左右にループさせた座標に変換する
                    targetPosition = GetLoopPosition(targetPosition);

                    // [6-11-24]目標地点を目指す座標を設定する
                    newPosition = GetChasePosition(characters[i], targetPosition);

                    break;
                }
                // [6-11-25]挟み撃ちモンスター
                case CHARACTER_SIEGE:
                {
                    // [6-11-26]追いかけモンスターからプレイヤーへのベクトルを取得する
                    VEC2 chaseToPlayer = Vec2Subtract(
                        characters[CHARACTER_PLAYER].position,  // プレイヤーの座標
                        characters[CHARACTER_CHASE].position);  // 追いかけモンスターの座標

                    // [6-11-27]目的地を宣言する
                    VEC2 targetPosition =

                        // ベクトルを加算する
                        Vec2Add(

                            // プレイヤーの座標
                            characters[CHARACTER_PLAYER].position,
                            
                            // 追いかけモンスターからプレイヤーへのベクトル
                            chaseToPlayer);

                    // [6-11-28]目標地点を上下左右にループさせた座標に変換する
                    targetPosition = GetLoopPosition(targetPosition);

                    // [6-11-29]目標地点を目指す座標を設定する
                    newPosition = GetChasePosition(characters[i], targetPosition);

                    break;
                }
                }

                // [6-11-30]前回の座標を現在の座標で更新する
                characters[i].lastPosition = characters[i].position;

                // [6-11-31]移動先に移動させる
                characters[i].position = newPosition;
            }

            // [6-11-32]ゲームオーバーになったかどうかを判定する
            if (IsGameOver())
            {
                goto start; // [6-11-33]ゲームの開始ラベルにジャンプする
            }

            // [6-11-34]画面を再描画する
            DrawMaze();
        }

        // [6-11-35]キーボード入力があったかどうかを判定する
        if (_kbhit())
        {
            // [6-11-36]プレイヤーの新しい座標を宣言する
            VEC2 newPosition = characters[CHARACTER_PLAYER].position;

            // [6-11-37]入力されたキーによって分岐する
            switch (_getch())
            {
            case 'w':   newPosition.y--;    break;  // [6-11-38]wが押されたら上へ移動する
            case 's':   newPosition.y++;    break;  // [6-11-39]sが押されたら下へ移動する
            case 'a':   newPosition.x--;    break;  // [6-11-40]aが押されたら左へ移動する
            case 'd':   newPosition.x++;    break;  // [6-11-41]dが押されたら右へ移動する
            }

            // [6-11-42]移動先の座標を上下左右にループさせる
            newPosition = GetLoopPosition(newPosition);

            // [6-11-43]移動先が壁でないどうかを判定する
            if (maze[newPosition.y][newPosition.x] != '#')
            {
                // [6-11-44]プレイヤーの前回の座標を現在の座標で更新する
                characters[CHARACTER_PLAYER].lastPosition =
                    characters[CHARACTER_PLAYER].position;

                // [6-11-45]プレイヤーの座標を更新する
                characters[CHARACTER_PLAYER].position = newPosition;

                // [6-11-46]ゲームオーバーになったかどうかを判定する
                if (IsGameOver())
                {
                    goto start; // [6-11-47]ゲームの開始ラベルにジャンプする
                }

                // [6-11-48]プレイヤーの座標にドットがあるかどうかを判定する
                if (maze[characters[CHARACTER_PLAYER].position.y]
                                    [characters[CHARACTER_PLAYER].position.x] == 'o')
                {
                    // [6-11-49]プレイヤーの座標のドットを消す
                    maze[characters[CHARACTER_PLAYER].position.y]
                        [characters[CHARACTER_PLAYER].position.x] = ' ';

                    // [6-11-50]クリアしたかどうかを判定する
                    if (IsComplete())
                    {
                        goto start; // [6-11-51]ゲームの開始ラベルにジャンプする
                    }
                }
            }

            // [6-11-52]迷路を再描画する
            DrawMaze();
        }
    }
}