// [1]ヘッダーをインクルードする場所

#include <stdio.h>  // [1-1]標準入出力ヘッダーをインクルードする
#include <stdlib.h> // [1-2]標準ライブラリヘッダーをインクルードする
#include <time.h>   // [1-3]時間管理ヘッダーをインクルードする
#include <conio.h>  // [1-4]コンソール入出力ヘッダーをインクルードする
#include <vector>   // [1-5]ベクターヘッダーをインクルードする

// [2]定数を定義する場所

#define MAZE_WIDTH  (8)                 // [2-1]迷路の幅を定義する
#define MAZE_HEIGHT (8)                 // [2-2]迷路の高さを定義する

#define GOAL_X      (MAZE_WIDTH - 1)    // [2-3]ゴールの列を定義する
#define GOAL_Y      (MAZE_HEIGHT - 1)   // [2-4]ゴールの行を定義する

// [3]列挙定数を定義する場所

// [3-1]方位の種類を定義する
enum
{
    DIRECTION_NORTH,    // [3-1-1]北
    DIRECTION_WEST,     // [3-1-2]西
    DIRECTION_SOUTH,    // [3-1-3]南
    DIRECTION_EAST,     // [3-1-4]東
    DIRECTION_MAX       // [3-1-5]方位の数
};

// [3-2]プレイヤーからの相対位置の種類を定義する
enum
{
    LOCATION_FRONT_LEFT,    // [3-2-1]左前
    LOCATION_FRONT_RIGHT,   // [3-2-2]右前
    LOCATION_FRONT,         // [3-2-3]前
    LOCATION_LEFT,          // [3-2-4]左
    LOCATION_RIGHT,         // [3-2-5]右
    LOCATION_CENTER,        // [3-2-6]中心
    LOCATION_MAX            // [3-2-7]位置の数
};

// [4]構造体を宣言する場所

// [4-1]ベクトルの構造体を宣言する
typedef struct {
    int x, y;// [4-1-1]座標
} VEC2;

// [4-2]迷路のマスの構造体を宣言する
typedef struct {
    bool walls[DIRECTION_MAX];  // [4-2-1]各方位の壁の有無
} TILE;

// [4-3]プレイヤーの構造体を宣言する
typedef struct {
    VEC2 position;  // [4-3-1]座標
    int direction;  // [4-3-1]向いている方位
} CHARACTER;

// [5]変数を宣言する場所

// [5-1]各方位のベクトルを宣言する
VEC2 directions[] =
{
    { 0,-1},    // DIRECTION_NORTH  北
    {-1, 0},    // DIRECTION_WEST   西
    { 0, 1},    // DIRECTION_SOUTH  南
    { 1, 0}     // DIRECTION_EAST   東
};

// [5-2]基準となるアスキーアートを宣言する
const char* all =
    "L       /¥n"
    "#L     /#¥n"
    "#|L _ /|#¥n"
    "#|#|#|#|#¥n"
    "#|#|_|#|#¥n"
    "#|/   L|#¥n"
    "#/     L#¥n"
    "/       L¥n";

// [5-3]左前方前の壁のアスキーアートを宣言する
const char* frontLeftNorth =
    "         ¥n"
    "         ¥n"
    "  _      ¥n"
    " |#|     ¥n"
    " |_|     ¥n"
    "         ¥n"
    "         ¥n"
    "         ¥n";

// [5-4]右前方前の壁のアスキーアートを宣言する
const char* frontRightNorth =
    "         ¥n"
    "         ¥n"
    "      _  ¥n"
    "     |#| ¥n"
    "     |_| ¥n"
    "         ¥n"
    "         ¥n"
    "         ¥n";

// [5-5]前方前の壁のアスキーアートを宣言する
const char* frontNorth =
    "         ¥n"
    "         ¥n"
    "    _    ¥n"
    "   |#|   ¥n"
    "   |_|   ¥n"
    "         ¥n"
    "         ¥n"
    "         ¥n";

// [5-6]前方左の壁のアスキーアートを宣言する
const char* frontWest =
    "         ¥n"
    "         ¥n"
    " |L      ¥n"
    " |#|     ¥n"
    " |#|     ¥n"
    " |/      ¥n"
    "         ¥n"
    "         ¥n";

// [5-7]前方右の壁のアスキーアートを宣言する
const char* frontEast =
    "         ¥n"
    "         ¥n"
    "      /| ¥n"
    "     |#| ¥n"
    "     |#| ¥n"
    "      L| ¥n"
    "         ¥n"
    "         ¥n";

// [5-8]左方前の壁のアスキーアートを宣言する
const char* leftNorth =
    "         ¥n"
    "_        ¥n"
    "#|       ¥n"
    "#|       ¥n"
    "#|       ¥n"
    "_|       ¥n"
    "         ¥n"
    "         ¥n";

// [5-9]右方前の壁のアスキーアートを宣言する
const char* rightNorth =
    "         ¥n"
    "        _¥n"
    "       |#¥n"
    "       |#¥n"
    "       |#¥n"
    "       |_¥n"
    "         ¥n"
    "         ¥n";

// [5-10]前の壁のアスキーアートを宣言する
const char* north =
    "         ¥n"
    "  _____  ¥n"
    " |#####| ¥n"
    " |#####| ¥n"
    " |#####| ¥n"
    " |_____| ¥n"
    "         ¥n"
    "         ¥n";

// [5-11]左の壁のアスキーアートを宣言する
const char* west =
    "L        ¥n"
    "#L       ¥n"
    "#|       ¥n"
    "#|       ¥n"
    "#|       ¥n"
    "#|       ¥n"
    "#/       ¥n"
    "/        ¥n";

// [5-12]右の壁のアスキーアートを宣言する
const char* east =
    "        /¥n"
    "       /#¥n"
    "       |#¥n"
    "       |#¥n"
    "       |#¥n"
    "       |#¥n"
    "       L#¥n"
    "        L¥n";

// [5-13]アスキーアートのテーブルを宣言する
const char* aaTable[LOCATION_MAX][DIRECTION_MAX] =
{
    // LOCATION_FRONT_LEFT  左前
    {
        frontLeftNorth,     // DIRECTION_NORTH  北
        NULL,               // DIRECTION_WEST   西
        NULL,               // DIRECTION_SOUTH  南
        NULL                // DIRECTION_EAST   東
    },

    // LOCATION_FRONT_RIGHT 右前
    {
        frontRightNorth,    // DIRECTION_NORTH  北
        NULL,               // DIRECTION_WEST   西
        NULL,               // DIRECTION_SOUTH  南
        NULL                // DIRECTION_EAST   東
    },

    // LOCATION_FRONT       前
    {
        frontNorth,         // DIRECTION_NORTH  北
        frontWest,          // DIRECTION_WEST   西
        NULL,               // DIRECTION_SOUTH  南
        frontEast           // DIRECTION_EAST   東
    },

    // LOCATION_LEFT        左
    {
        leftNorth,          // DIRECTION_NORTH  北
        NULL,               // DIRECTION_WEST   西
        NULL,               // DIRECTION_SOUTH  南
        NULL                // DIRECTION_EAST   東
    },

    // LOCATION_RIGHT       右
    {
        rightNorth,         // DIRECTION_NORTH  北
        NULL,               // DIRECTION_WEST   西
        NULL,               // DIRECTION_SOUTH  南
        NULL                // DIRECTION_EAST   東
    },

    // LOCATION_CENTER      中心
    {
        north,              // DIRECTION_NORTH  北
        west,               // DIRECTION_WEST   西
        NULL,               // DIRECTION_SOUTH  南
        east                // DIRECTION_EAST   東
    }
};

// [5-14]プレイヤーからの相対座標のテーブルを宣言する
VEC2 locations[DIRECTION_MAX][LOCATION_MAX] =
{
    // DIRECTION_NORTH  北
    {
        {-1,-1},    // LOCATION_FRONT_LEFT  左前
        { 1,-1},    // LOCATION_FRONT_RIGHT 右前
        { 0,-1},    // LOCATION_FRONT       前
        {-1, 0},    // LOCATION_LEFT        左
        { 1, 0},    // LOCATION_RIGHT       右
        { 0, 0}     // LOCATION_CENTER      中心
    },

    // DIRECTION_WEST   西
    {
        {-1, 1},    // LOCATION_FRONT_LEFT  左前
        {-1,-1},    // LOCATION_FRONT_RIGHT 右前
        {-1, 0},    // LOCATION_FRONT       前
        { 0, 1},    // LOCATION_LEFT        左
        { 0,-1},    // LOCATION_RIGHT       右
        { 0, 0}     // LOCATION_CENTER      中心
    },

    // DIRECTION_SOUTH  南
    {
        { 1, 1},    // LOCATION_FRONT_LEFT  左前
        {-1, 1},    // LOCATION_FRONT_RIGHT 右前
        { 0, 1},    // LOCATION_FRONT       前
        { 1, 0},    // LOCATION_LEFT        左
        {-1, 0},    // LOCATION_RIGHT       右
        { 0, 0}     // LOCATION_CENTER      中心
    },

    // DIRECTION_EAST   東
    {
        { 1,-1},    // LOCATION_FRONT_LEFT  左前
        { 1, 1},    // LOCATION_FRONT_RIGHT 右前
        { 1, 0},    // LOCATION_FRONT       前
        { 0,-1},    // LOCATION_LEFT        左
        { 0, 1},    // LOCATION_RIGHT       右
        { 0, 0}     // LOCATION_CENTER      中心
    }
};

TILE maze[MAZE_HEIGHT][MAZE_WIDTH];  // [5-15]迷路を宣言する

CHARACTER player;// [5-16]プレイヤーを宣言する

// [6]関数を宣言する場所

// [6-1]ベクトルを加算する関数を宣言する
VEC2 VecAdd(VEC2 _v0, VEC2 _v1)
{
    // [6-1-1]ベクトルを加算して返す
    return
    {
        _v0.x + _v1.x,
        _v0.y + _v1.y
    };
}

// [6-2]対象の座標が迷路の範囲内かどうかを判定する関数を宣言する
bool IsInsideMaze(VEC2 _position)
{
    // [6-2-1]対象の座標が迷路の範囲内かどうかを返す
    return (_position.x >= 0)
        && (_position.x < MAZE_WIDTH)
        && (_position.y >= 0)
        && (_position.y < MAZE_HEIGHT);
}

// [6-3]壁を掘る関数を宣言する
void DigWall(VEC2 _position, int _direction)
{
    // [6-3-1]対象の座標が迷路の範囲内かどうかを判定する
    if (!IsInsideMaze(_position))
    {
        return;// [6-3-2]関数を抜ける
    }

    // [6-3-3]対象の壁を掘る
    maze[_position.y][_position.x].walls[_direction] = false;

    // [6-3-4]隣のマスの座標を宣言する
    VEC2 nextPosition = VecAdd(_position, directions[_direction]);

    // [6-3-5]隣のマスが迷路の範囲内かどうかを判定する
    if (IsInsideMaze(nextPosition))
    {
        // [6-3-6]隣の部屋の掘る壁の方位を宣言する
        int nextDirection = (_direction + 2) % DIRECTION_MAX;

        // [6-3-7]隣の部屋の壁を掘る
        maze[nextPosition.y][nextPosition.x].walls[nextDirection] = false;
    }
}

// [6-4]対象の壁を掘ってもよいかどうかを判定する関数を宣言する
bool CanDigWall(VEC2 _position, int _direction)
{
    // [6-4-1]隣の座標を宣言する
    VEC2 nextPosition = VecAdd(_position, directions[_direction]);

    // [6-4-2]隣の座標が迷路の範囲内でないかどうかを判定する
    if (!IsInsideMaze(nextPosition))
    {
        return false;// [6-4-3]掘ってはいけないという結果を返す
    }

    // [6-4-4]すべての方位を反復する
    for (int i = 0; i < DIRECTION_MAX; i++)
    {
        // [6-4-5]壁が掘られているかどうかを判定する
        if (!maze[nextPosition.y][nextPosition.x].walls[i])
        {
            return false;// [6-4-6]掘ってはいけないという結果を返す
        }
    }

    return true;// [6-4-7]掘ってもよいという結果を返す
}

// [6-5]迷路をランダムで生成する関数を宣言する
void GenerateMap()
{
    // [6-5-1]迷路のすべての行を反復する
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-5-2]迷路のすべての列を反復する
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-5-3]マスのすべての方位を反復する
            for (int i = 0; i < DIRECTION_MAX; i++)
            {
                // [6-5-4]対象の方位を壁にする
                maze[y][x].walls[i] = true;
            }
        }
    }

    // [6-5-5]現在の座標を宣言する
    VEC2 currentPosition = { 0, 0 };

    // [6-5-6]壁を掘るべきマスのリストを宣言する
    std::vector<VEC2> toDigWallPositions;

    // [6-5-7]壁を掘るべきマスのリストに現在のマスを加える
    toDigWallPositions.push_back(currentPosition);

    // [6-5-8]無限ループする
    while (1)
    {
        // [6-5-9]掘れる壁の方位のリストを宣言する
        std::vector<int> canDigDirections;

        // [6-5-10]すべての方位を反復する
        for (int i = 0; i < DIRECTION_MAX; i++)
        {
            // [6-5-11]対象の方位の壁を掘ってもよいのであれば
            if (CanDigWall(currentPosition, i))
            {
                // [6-5-12]掘れる壁の方位のリストに追加する
                canDigDirections.push_back(i);
            }
        }

        // [6-5-13]掘れる壁があるかどうかを判定する
        if (canDigDirections.size() > 0)
        {
            // [6-5-14]掘る壁の方位を宣言する
            int digDirection = canDigDirections[rand() % canDigDirections.size()];

            // [6-5-15]対象の壁を掘る
            DigWall(currentPosition, digDirection);

            // [6-5-16]掘った壁の向こうに移動する
            currentPosition = VecAdd(currentPosition, directions[digDirection]);

            // [6-5-17]壁を掘るべきマスの座標リストに現在の座標を加える
            toDigWallPositions.push_back(currentPosition);
        }

        // [6-5-18]掘れるがないとき
        else
        {
            // [6-5-19]壁を掘るべきマスのリストから現在のマスを削除する
            toDigWallPositions.erase(toDigWallPositions.begin());

            // [6-5-20]壁を掘るべきマスのリストが空かどうかを判定する
            if (toDigWallPositions.size() <= 0)
            {
                break;// [6-5-21]ループを抜ける
            }

            // [6-5-22]壁を掘るべきマスのリストから、先頭のマスを取得し移動する
            currentPosition = toDigWallPositions.front();
        }
    }
}

// [6-6]マップを描画する関数を宣言する
void DrawMap()
{
    // [6-6-1]迷路のすべての行を反復する
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-6-2]迷路のすべての列を反復する
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            //  [6-6-3]北の壁を描画する
            printf("＋%s＋", maze[y][x].walls[DIRECTION_NORTH] ? "―" : "　");
        }

        printf("¥n");// [6-6-4]1行描画するごとに改行する

        // [6-6-5]迷路のすべての列を反復する
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-6-6]床のアスキーアートを宣言する
            char floorAA[] = "　";

            // [6-6-7]プレイヤーの座標を描画中なら
            if ((x == player.position.x) && (y == player.position.y))
            {
                // [6-6-8]方位のアスキーアートを宣言する
                const char* directionAA[] =
                {
                    "↑",    // DIRECTION_NORTH  北
                    "←",    // DIRECTION_WEST   西
                    "↓",    // DIRECTION_SOUTH  南
                    "→"     // DIRECTION_EAST   東
                };

                // [6-6-9]床のアスキーアートにプレイヤーのアスキーアートをコピーする
                strcpy_s(floorAA, directionAA[player.direction]);
            }

            // [6-6-10]ゴールの座標を描画中なら
            else if ((x == GOAL_X) && (y == GOAL_Y))
            {
                // [6-6-11]床のアスキーアートにゴールのアスキーアートをコピーする
                strcpy_s(floorAA, "Ｇ");
            }

            // [6-6-12]西の壁、中心の床、東の壁を描画する
            printf("%s%s%s",
                maze[y][x].walls[DIRECTION_WEST] ? "｜" : "　",
                floorAA,
                maze[y][x].walls[DIRECTION_EAST] ? "｜" : "　");
        }

        printf("¥n");// [6-6-13]1行描画するごとに改行する

        // [6-6-14]迷路のすべての列を反復する
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-6-15]南の壁を描画する
            printf("＋%s＋", maze[y][x].walls[DIRECTION_SOUTH] ? "―" : "　");
        }

        printf("¥n");// [6-6-16]1行描画するごとに改行する
    }
}

// [6-7]迷路を擬似3D視点で描画する関数を宣言する
void Draw3D()
{
    // [6-7-1]画面バッファーを宣言する
    char screen[] =
        "         ¥n"
        "         ¥n"
        "         ¥n"
        "         ¥n"
        "         ¥n"
        "         ¥n"
        "         ¥n"
        "         ¥n";

    // [6-7-2]すべての相対位置を反復する
    for (int i = 0; i < LOCATION_MAX; i++)
    {
        // [6-7-3]絶対位置を宣言する
        VEC2 position = VecAdd(player.position, locations[player.direction][i]);

        // [6-7-4]絶対位置が迷路の範囲外かどうかを判定する
        if (!IsInsideMaze(position))
            continue;// [6-7-5]次の相対位置へスキップする

        // [6-7-6]すべての方位を反復する
        for (int j = 0; j < DIRECTION_MAX; j++)
        {
            // [6-7-7]相対方位を宣言する
            int direction = (DIRECTION_MAX + j - player.direction) % DIRECTION_MAX;

            // [6-7-8]対象の壁がないかどうかを判定する
            if (!maze[position.y][position.x].walls[j])
            {
                continue;// [6-7-9]次の方位へスキップする
            }

            // [6-7-10]合成するアスキーアートがないかどうかを判定する
            if (!aaTable[i][direction])
            {
                continue;// [6-7-11]次の相対位置へスキップする
            }

            // [6-7-12]画面バッファーのすべての文字を反復する
            for (int k = 0; k < sizeof(screen); k++)
            {
                // [6-7-13]対象の文字がスペースでないかどうか判定する
                if (aaTable[i][direction][k] != ' ')
                {
                    // [6-7-14]画面バッファーに合成するアスキーアートを書き込む
                    screen[k] = aaTable[i][direction][k];
                }
            }
        }
    }

    // [6-7-15]画面バッファーのすべての文字を反復する
    for (int i = 0; i < sizeof(screen); i++)
    {
        // [6-7-16]画面バッファーの半角文字を全角文字に変換して描画する
        switch (screen[i])
        {
        case ' ':   printf("　");    break; // [6-7-17]「 」を「　」として描画する
        case '#':   printf("　");    break; // [6-7-18]「#」を「　」として描画する
        case '_':   printf("＿");    break; // [6-7-19]「_」を「＿」として描画する
        case '|':   printf("｜");    break; // [6-7-20]「|」を「｜」として描画する
        case '/':   printf("／");    break; // [6-7-21]「/」を「／」として描画する
        case 'L':   printf("＼");    break; // [6-7-22]「L」を「＼」として描画する
        default:

            // [6-7-23]上記以外の文字はそのまま描画する
            printf("%c", screen[i]);

            break;
        }
    }
}

// [6-8]ゲームを初期化する関数を宣言する
void Init()
{
    GenerateMap();// [6-8-1]迷路をランダムで生成する関数を呼び出す

    player.position = { 0,0 };// [6-8-2]プレイヤーの座標を初期化する

    player.direction = DIRECTION_NORTH;// [6-8-3]プレイヤーの方位を初期化する
}

// [6-9]プログラムの実行開始点を宣言する
int main()
{
    srand((unsigned int)time(NULL));// [6-9-1]乱数をシャッフルする

    Init();// [6-9-2]ゲームを初期化する関数を呼び出す

    // [6-9-3]メインループ
    while (1)
    {
        system("cls");// [6-9-4]画面をクリアする

        // [6-9-5]迷路を擬似3D視点で描画する関数を呼び出す
        Draw3D();

        // [6-9-6]マップを描画する関数を呼び出す
        DrawMap();

        // [6-9-7]入力されたキーで分岐する
        switch (_getch())
        {
        case 'w':// [6-9-8]wキーが押されたら

            // [6-9-9]プレイヤーの目の前が壁でないかどうかを判定する
            if (!maze[player.position.y][player.position.x].walls[player.direction])
            {
                // [6-9-10]前進先の座標を宣言する
                VEC2 nextPosition = VecAdd(player.position, directions[player.direction]);

                // [6-9-11]前進先の座標が迷路の範囲内かどうかを判定する
                if (IsInsideMaze(nextPosition))
                {
                    // [6-9-12]前進先の座標を適用する
                    player.position = nextPosition;

                    // [6-9-13]ゴールに到達したかどうかを判定する
                    if ((player.position.x == GOAL_X) && (player.position.y == GOAL_Y))
                    {
                        system("cls");// [6-9-14]画面をクリアする

                        // [6-9-15]メッセージを表示する
                        printf(
                            "　＊　＊　ＣＯＮＧＲＡＴＵＬＡＴＩＯＮＳ　＊　＊¥n"
                            "¥n"
                            "　あなたはついに　でんせつのまよけを　てにいれた！¥n"
                            "¥n"
                            "　しかし、くらくをともにした　「なかま」という¥n"
                            "かけがえのない　たからをてにした　あなたにとって、¥n"
                            "まよけのかがやきも　いろあせて　みえるのであった…¥n"
                            "¥n"
                            "　　　　　　　〜　ＴＨＥ　ＥＮＤ　〜¥n");

                        _getch();// [6-9-16]キーボード入力を待つ

                        Init();// [6-9-17]ゲームを初期化する
                    }
                }
            }

            break;

        case 's':// [6-9-18]sキーが押されたら

            player.direction += 2;// [6-9-19]後ろを向く

            break;

        case 'a':// [6-9-20]aキーが押されたら

            player.direction++;// [6-9-21]左を向く

            break;

        case 'd':// [6-9-22]dキーが押されたら

            player.direction--;// [6-9-23]右を向く

            break;
        }

        // [6-9-24]プレイヤーの向いている方位を範囲内に補正する
        player.direction = (DIRECTION_MAX + player.direction) % DIRECTION_MAX;
    }
}