// [1]ヘッダーをインクルードする場所

#include <stdio.h>  // [1-1]標準入出力ヘッダーをインクルードする
#include <stdlib.h> // [1-2]標準ライブラリヘッダーをインクルードする
#include <string.h>	// [1-3]文字列操作ヘッダーをインクルードする
#include <time.h>   // [1-4]時間管理ヘッダーをインクルードする
#include <conio.h>  // [1-5]コンソール入出力ヘッダーをインクルードする

// [2]定数を定義する場所

#define SPELL_COST      (3)     // [2-1]呪文の消費MPを定義する
#define MAP_WIDTH       (16)    // [2-2]マップの幅を定義する
#define MAP_HEIGHT      (16)    // [2-3]マップの高さを定義する
#define SCREEN_WIDTH    (16)    // [2-4]スクロール画面の幅を定義する
#define SCREEN_HEIGHT   (12)    // [2-5]スクロール画面の高さを定義する

// [3]列挙定数を定義する場所

// [3-1]モンスターの種類を定義する
enum
{
    MONSTER_PLAYER, // [3-1-1]プレイヤー
    MONSTER_SLIME,  // [3-1-2]スライム
    MONSTER_BOSS,   // [3-1-3]魔王
    MONSTER_MAX     // [3-1-4]モンスターの種類の数
};

// [3-2]キャラクターの種類を定義する
enum
{
    CHARACTER_PLAYER,   // [3-2-1]プレイヤー
    CHARACTER_MONSTER,  // [3-2-2]モンスター
    CHARACTER_MAX       // [3-2-3]キャラクターの種類の数
};

// [3-3]コマンドの種類を定義する
enum
{
    COMMAND_FIGHT,  // [3-3-1]戦う
    COMMAND_SPELL,  // [3-3-2]呪文
    COMMAND_RUN,    // [3-3-3]逃げる
    COMMAND_MAX     // [3-3-4]コマンドの種類の数
};

// [3-4]マップの種類を定義する
enum {
    MAP_FIELD,          // [3-4-1]フィールド
    MAP_KING_CASTLE,    // [3-4-2]王様の城
    MAP_BOSS_CASTLE,    // [3-4-3]魔王の城
    MAP_MAX             // [3-4-4]マップの種類の数
};

// [4]構造体を宣言する場所

// [4-1]キャラクターの構造体を宣言する
typedef struct {
    int hp;                 // [4-1-1]HP
    int maxHp;              // [4-1-2]最大HP
    int mp;                 // [4-1-3]MP
    int maxMp;              // [4-1-4]最大MP
    int attack;             // [4-1-5]攻撃力
    char name[4 * 2 + 1];   // [4-1-6]名前
    char aa[256];           // [4-1-7]アスキーアート
    int command;            // [4-1-8]コマンド
    int target;             // [4-1-9]攻撃対象
}CHARACTER;

// [5]変数を宣言する場所

// [5-1]モンスターのステータスの配列を宣言する
CHARACTER monsters[MONSTER_MAX] =
{
    // [5-1-1]MONSTER_PLAYER    プレイヤー
    {
        100,        // [5-1-2]int hp                HP
        100,        // [5-1-3]int maxHp             最大HP
        15,         // [5-1-4]int mp                MP
        15,         // [5-1-5]int maxMp             最大MP
        30,         // [5-1-6]int attack            攻撃力
        "ゆうしゃ", // [5-1-7]char name[4 * 2 + 1]  名前
    },

    // [5-1-8]MONSTER_SLIME スライム
    {
        3,          // [5-1-9]int hp                HP
        3,          // [5-1-10]int maxHp            最大HP
        0,          // [5-1-11]int mp               MP
        0,          // [5-1-12]int maxMp            最大MP
        2,          // [5-1-13]int attack           攻撃力
        "スライム", // [5-1-14]char name[4 * 2 + 1] 名前

        // [5-1-15]char aa[256] アスキーアート
        "／・Д・＼¥n"
        "〜〜〜〜〜"
    },

    // [5-1-16]MONSTER_BOSS 魔王
    {
        255,        // [5-1-17]int hp               HP
        255,        // [5-1-18]int maxHp            最大HP
        0,          // [5-1-19]int mp               MP
        0,          // [5-1-20]int maxMp            最大MP
        50,         // [5-1-21]int attack           攻撃力
        "まおう",   // [5-1-22]char name[4 * 2 + 1] 名前

        // [5-1-23]char aa[256] アスキーアート
        "　　Ａ＠Ａ¥n"
        "ψ（▼皿▼）ψ"
    }
};

// [5-2]キャラクターの配列を宣言する
CHARACTER characters[CHARACTER_MAX];

// [5-3]コマンドの名前を宣言する
char commandNames[COMMAND_MAX][4 * 2 + 1] = {
    "たたかう", // [5-3-1]COMMAND_FIGHT 戦う
    "じゅもん", // [5-3-2]COMMAND_SPELL 呪文
    "にげる"    // [5-3-3]COMMAND_RUN   逃げる
};

// [5-4]マップの地形データを宣言する
char map[MAP_MAX][MAP_HEIGHT][MAP_WIDTH + 1] =
{
    // [5-4-1]MAP_FIELD フィールド
    {
        "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾",
        "‾‾MMMMM‾‾MMMM.‾‾",
        "‾M...M.##..M...‾",
        "‾M.M.M.‾‾M.M.M.‾",
        "‾M.M...‾‾M...M.‾",
        "‾M.MMMM‾‾MMMM..‾",
        "‾M..MM.‾‾‾‾‾‾#‾‾",
        "‾‾M.M.‾‾‾‾‾‾‾#‾‾",
        "‾‾M.MM‾‾‾‾BMM..‾",
        "‾‾...MM‾‾M.MMM.‾",
        "‾...‾‾M‾‾M...M.‾",
        "‾..‾‾‾K‾‾MMM.M.‾",
        "‾..‾‾‾.‾‾M...M.‾",
        "‾......‾‾M.MM..‾",
        "‾‾....‾‾‾‾....‾‾",
        "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾"
    },

    // [5-4-2]MAP_KING_CASTLE   王様の城
    {
        "HHH.......HHH",
        "H.H.......H.H",
        "HHHHHHHHHHHHH",
        ".H.........H.",
        ".H.HHH.HHH.H.",
        ".H.H0H.H1H.H.",
        ".H.........H.",
        ".HW.......WH.",
        ".HY.......YH.",
        "HHHHHH.HHHHHH",
        "H.H‾‾‾#‾‾‾H.H",
        "HHH‾‾‾#‾‾‾HHH",
        ".............."
    },

    // [5-4-3]MAP_BOSS_CASTLE   魔王の城
    {
        "HHH.......HHH",
        "H.H.......H.H",
        "HHHHHHHHHHHHH",
        ".H....H....H.",
        ".H..WHHHW..H.",
        ".H..YH2HY..H.",
        ".H.........H.",
        ".H..W...W..H.",
        ".H..Y...Y..H.",
        ".H.........H.",
        "HHHHHH.HHHHHH",
        "H.H‾‾‾#‾‾‾H.H",
        "HHH‾‾‾#‾‾‾HHH",
        "‾‾‾‾‾‾#‾‾‾‾‾‾",
        "‾‾‾‾‾‾#‾‾‾‾‾‾",
        "............."
    }
};

int currentMap; // [5-5]現在のマップを宣言する

int playerX = 6;    // [5-6]プレイヤーのX座標
int playerY = 12;   // [5-7]プレイヤーのY座標

// [6]関数を宣言する場所

// [6-1]ゲームを初期化する関数を宣言する
void Init()
{
    // [6-1-1]プレイヤーのステータスを初期化する
    characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];

    // [6-1-2]現在のマップを初期化する
    currentMap = MAP_KING_CASTLE;

    playerX = 4;    // [6-1-3]プレイヤーのX座標を初期化する
    playerY = 6;    // [6-1-4]プレイヤーのY座標を初期化する
}

// [6-2]戦闘シーンの画面を描画する関数を宣言する
void DrawBattleScreen()
{
    // [6-2-1]画面をクリアする
    system("cls");

    // [6-2-2]プレイヤーの名前を表示する
    printf("%s¥n", characters[CHARACTER_PLAYER].name);

    // [6-2-3]プレイヤーのステータスを表示する
    printf("ＨＰ：%d／%d　ＭＰ：%d／%d¥n",
        characters[CHARACTER_PLAYER].hp,
        characters[CHARACTER_PLAYER].maxHp,
        characters[CHARACTER_PLAYER].mp,
        characters[CHARACTER_PLAYER].maxMp);

    // [6-2-4]1行空ける
    printf("¥n");

    // [6-2-5]モンスターのアスキーアートを描画する
    printf("%s", characters[CHARACTER_MONSTER].aa);

    // [6-2-6]モンスターのＨＰを表示する
    printf("（ＨＰ：%d／%d）¥n",
        characters[CHARACTER_MONSTER].hp,
        characters[CHARACTER_MONSTER].maxHp);

    // [6-2-7]1行空ける
    printf("¥n");
}

// [6-3]コマンドを選択する関数を宣言する
void SelectCommand()
{
    // [6-3-1]プレイヤーのコマンドを初期化する
    characters[CHARACTER_PLAYER].command = COMMAND_FIGHT;

    // [6-3-2]コマンドが決定されるまでループする
    while (1)
    {
        // [6-3-3]戦闘画面を描画する関数を呼び出す
        DrawBattleScreen();

        // [6-3-4]コマンドの一覧を表示する
        for (int i = 0; i < COMMAND_MAX; i++)
        {
            // [6-3-5]選択中のコマンドなら
            if (i == characters[CHARACTER_PLAYER].command)
            {
                // [6-3-6]カーソルを描画する
                printf("＞");
            }
            // [6-3-7]選択中のコマンドでなければ
            else
            {
                // [6-3-8]全角スペースを描画する
                printf("　");
            }

            // [6-3-9]コマンドの名前を表示する
            printf("%s¥n", commandNames[i]);
        }

        // [6-3-10]入力されたキーによって分岐する
        switch (_getch())
        {
        case 'w':   // [6-3-11]wキーが押されたら
            characters[CHARACTER_PLAYER].command--; // [6-3-12]上のコマンドに切り替える
            break;

        case 's':   // [6-3-13]sキーが押されたら
            characters[CHARACTER_PLAYER].command++; // [6-3-14]下のコマンドに切り替える
            break;

        default:    // [6-3-15]上記以外のキーが押されたら
            return; // [6-3-16]関数を抜ける
        }

        // [6-3-17]カーソルを上下にループさせる
        characters[CHARACTER_PLAYER].command = (COMMAND_MAX + characters[CHARACTER_PLAYER].command) % COMMAND_MAX;
    }
}

// [6-4]戦闘シーンの関数を宣言する
void Battle(int _monster)
{
    // [6-4-1]モンスターのステータスを初期化する
    characters[CHARACTER_MONSTER] = monsters[_monster];

    // [6-4-2]プレイヤーの攻撃対象をモンスターに設定する
    characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;

    // [6-4-3]モンスターの攻撃対象をプレイヤーに設定する
    characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

    // [6-4-4]戦闘シーンの画面を描画する関数を呼び出す
    DrawBattleScreen();

    // [6-4-5]戦闘シーンの最初のメッセージを表示する
    printf("%sが　あらわれた！¥n", characters[CHARACTER_MONSTER].name);

    // [6-4-6]キーボード入力を待つ
    _getch();

    // [6-4-7]戦闘が終了するまでループする
    while (1)
    {
        // [6-4-8]コマンドを選択する関数を呼び出す
        SelectCommand();

        // [6-4-9]各キャラクターを反復する
        for (int i = 0; i < CHARACTER_MAX; i++)
        {
            // [6-4-10]戦闘シーンの画面を描画する関数を呼び出す
            DrawBattleScreen();

            // [6-4-11]選択されたコマンドで分岐する
            switch (characters[i].command)
            {
            case COMMAND_FIGHT: // [6-4-12]戦う
            {
                // [6-4-13]攻撃をするメッセージを表示する
                printf("%sの　こうげき！¥n", characters[i].name);

                // [6-4-14]キーボード入力を待つ
                _getch();

                // [6-4-15]敵に与えるダメージを計算する
                int damage = 1 + rand() % characters[i].attack;

                // [6-4-16]敵にダメージを与える
                characters[characters[i].target].hp -= damage;

                // [6-4-17]敵のHPが負の値になったかどうかを判定する
                if (characters[characters[i].target].hp < 0)
                {
                    // [6-4-18]敵のHPを0にする
                    characters[characters[i].target].hp = 0;
                }

                // [6-4-19]戦闘シーンの画面を再描画する関数を呼び出す
                DrawBattleScreen();

                // [6-4-20]敵にダメージを与えたメッセージを表示する
                printf("%sに　%dの　ダメージ！¥n",
                    characters[characters[i].target].name,
                    damage);

                // [6-4-21]キーボード入力を待つ
                _getch();

                break;
            }
            case COMMAND_SPELL: // [6-4-22]呪文

                // [6-4-23]MPが足りるかどうかを判定する
                if (characters[i].mp < SPELL_COST)
                {
                    // [6-4-24]MPが足りないメッセージを表示する
                    printf("ＭＰが　たりない！¥n");

                    // [6-4-25]キーボード入力を待つ
                    _getch();

                    // [6-4-26]呪文を唱える処理を抜ける
                    break;
                }

                // [6-4-27]MPを消費させる
                characters[i].mp -= SPELL_COST;

                // [6-4-28]画面を再描画する
                DrawBattleScreen();

                // [6-4-29]呪文を唱えたメッセージを表示する
                printf("%sは　ヒールを　となえた！¥n", characters[i].name);

                // [6-4-30]キーボード入力を待つ
                _getch();

                // [6-4-31]HPを回復させる
                characters[i].hp = characters[i].maxHp;

                // [6-4-32]戦闘シーンの画面を再描画する
                DrawBattleScreen();

                // [6-4-33]HPが回復したメッセージを表示する
                printf("%sのきずが　かいふくした！¥n", characters[i].name);

                // [6-4-34]キーボード入力を待つ
                _getch();

                break;

            case COMMAND_RUN:   // [6-4-35]逃げる

                // [6-4-36]逃げ出したメッセージを表示する
                printf("%sは　にげだした！¥n", characters[i].name);

                // [6-4-37]キーボード入力を待つ
                _getch();

                // [6-4-38]戦闘処理を抜ける
                return;

                break;
            }

            // [6-4-39]攻撃対象を倒したかどうかを判定する
            if (characters[characters[i].target].hp <= 0)
            {
                // [6-4-40]攻撃対象によって処理を分岐させる
                switch (characters[i].target)
                {
                    // [6-4-41]プレイヤーなら
                case CHARACTER_PLAYER:

                    // [6-4-42]プレイヤーが死んだメッセージを表示する
                    printf("あなたは　しにました");

                    break;

                // [6-4-43]モンスターなら
                case CHARACTER_MONSTER:

                    // [6-4-44]モンスターのアスキーアートを何も表示しないように書き換える
                    strcpy_s(characters[characters[i].target].aa, "¥n");

                    // [6-4-45]戦闘シーンの画面を再描画する関数を呼び出す
                    DrawBattleScreen();

                    // [6-4-46]モンスターを倒したメッセージを表示する
                    printf("%sを　たおした！¥n", characters[characters[i].target].name);

                    break;
                }

                // [6-4-47]キーボード入力を待つ
                _getch();

                // [6-4-48]戦闘シーンの関数を抜ける
                return;
            }
        }
    }
}

// [6-5]マップを描画する処理を記述する関数を宣言する
void DrawMap()
{
    // [6-5-1]画面をクリアする
    system("cls");

    // [6-5-2]描画するすべての行を反復する
    for (int y = playerY - SCREEN_HEIGHT / 2; y < playerY + SCREEN_HEIGHT / 2; y++)
    {
        // [6-5-3]描画するすべての列を反復する
        for (int x = playerX - SCREEN_WIDTH / 2; x < playerX + SCREEN_WIDTH / 2; x++)
        {
            // [6-5-4]対象の座標がプレイヤーの座標と等しいかどうかを判定する
            if ((x == playerX) && (y == playerY))
            {
                // [6-5-5]プレイヤーのアスキーアートを描画する
                printf("勇");
            }

            // [6-5-6]対象の座標がマップデータの範囲外かどうかを判定する
            else if ((x < 0) || (x >= MAP_WIDTH)    // X座標がマップの範囲外
                || (y < 0) || (y >= MAP_HEIGHT)     // Y座標がマップの範囲外
                || (map[currentMap][y][x] == '¥0')) // 対象のマスが設定されていない
            {
                // [6-5-7]マップの種類によって分岐する
                switch (currentMap)
                {
                case MAP_FIELD:         printf("〜");   break;  // [6-5-8]フィールドの外は海
                case MAP_KING_CASTLE:   printf("．");   break;  // [6-5-9]王様の城の外は平地
                case MAP_BOSS_CASTLE:   printf("．");   break;  // [6-5-10]魔王の城の外は平地
                }
            }

            // [6-5-11]上記の状態以外であれば
            else
            {
                // [6-5-12]マスの種類によって分岐する
                switch (map[currentMap][y][x])
                {
                case '‾':   printf("〜");   break;  // [6-5-13]海
                case '.':   printf("．");   break;  // [6-5-14]平地
                case 'M':   printf("Ｍ");   break;  // [6-5-15]山
                case '#':   printf("＃");   break;  // [6-5-16]橋
                case 'K':   printf("王");   break;  // [6-5-17]王様の城
                case 'B':   printf("魔");   break;  // [6-5-18]魔王の城
                case 'H':   printf("□");   break;  // [6-5-19]壁
                case 'W':   printf("炎");   break;  // [6-5-20]炎
                case 'Y':   printf("Ｙ");   break;  // [6-5-21]燭台
                case '0':   printf("王");   break;  // [6-5-22]王
                case '1':   printf("姫");   break;  // [6-5-23]姫
                case '2':   printf("魔");   break;  // [6-5-24]魔王
                }
            }
        }

        // [6-5-25]1行描画するごとに改行する
        printf("¥n");
    }

    // [6-5-26]1行空ける
    printf("¥n");

    // [6-5-27]プレイヤーの名前を表示する
    printf("%s¥n", characters[CHARACTER_PLAYER].name);

    // [6-5-28]プレイヤーのステータスを表示する
    printf("ＨＰ：%d／%d ＭＰ：%d／%d¥n",
        characters[CHARACTER_PLAYER].hp,
        characters[CHARACTER_PLAYER].maxHp,
        characters[CHARACTER_PLAYER].mp,
        characters[CHARACTER_PLAYER].maxMp);

    // [6-5-29]1行空ける
    printf("¥n");
}

// [6-6]プログラムの実行開始点を宣言する
int main()
{
    // [6-6-1]乱数をシャッフルする
    srand((unsigned int)time(NULL));

    // [6-6-2]ゲームを初期化する関数を呼び出す
    Init();

    // [6-6-3]メインループ
    while (1)
    {
        // [6-6-4]マップを描画する関数を呼び出す
        DrawMap();

        int lastPlayerX = playerX;// [6-6-5]プレイヤーの移動前のX座標を宣言する
        int lastPlayerY = playerY;// [6-6-6]プレイヤーの移動前のY座標を宣言する

        // [6-6-7]入力されたキーで分岐する
        switch (_getch())
        {
        case 'w':   playerY--;  break;  // [6-6-8]wキーで上移動
        case 's':   playerY++;  break;  // [6-6-9]sキーで下移動
        case 'a':   playerX--;  break;  // [6-6-10]aキーで左移動
        case 'd':   playerX++;  break;  // [6-6-11]dキーで右移動
        }

        // [6-6-12]マップの外に出たかどうかを判定する
        if ((playerX < 0) || (playerX >= MAP_WIDTH)         // X座標がマップの範囲外
            || (playerY < 0) || (playerY >= MAP_HEIGHT)     // Y座標がマップの範囲外
            || (map[currentMap][playerY][playerX] == '¥0')) // 未設定のマス
        {
            // [6-6-13]現在のマップによって分岐する
            switch (currentMap)
            {
            case MAP_KING_CASTLE:   // [6-6-14]王様の城

                // [6-6-15]フィールドマップに切り替える
                currentMap = MAP_FIELD;

                playerX = 6;    // [6-6-16]プレイヤーのX座標を設定する
                playerY = 12;   // [6-6-17]プレイヤーのY座標を設定する

                break;

            case MAP_BOSS_CASTLE:   // [6-6-18]魔王の城

                // [6-6-19]フィールドマップに切り替える
                currentMap = MAP_FIELD;

                playerX = 10;   // [6-6-20]プレイヤーのX座標を設定する
                playerY = 9;    // [6-6-21]プレイヤーのY座標を設定する

                break;
            }
        }

        // [6-6-22]移動先のマスの種類によって分岐させる
        switch (map[currentMap][playerY][playerX])
        {
        case 'K':   // [6-6-23]王様の城

            // [6-6-24]王様の城にマップを切り替える
            currentMap = MAP_KING_CASTLE;

            playerX = 6;    // [6-6-25]プレイヤーのX座標を設定する
            playerY = 12;   // [6-6-26]プレイヤーのY座標を設定する

            break;

        case 'B':   // [6-6-27]魔王の城

            // [6-6-28]魔王の城にマップを切り替える
            currentMap = MAP_BOSS_CASTLE;

            playerX = 6;    // [6-6-29]プレイヤーのX座標を設定する
            playerY = 15;   // [6-6-30]プレイヤーのY座標を設定する

            break;

        case '0':   // [6-6-31]王様

            // [6-6-32]王様の会話メッセージを表示する
            printf("＊「おお　ゆうしゃよ！¥n"
                "ひがしの　まじょうの　まおうを¥n"
                "たおし　せかいを　すくってくれ！¥n"
            );

            _getch();// [6-6-33]キーボード入力待ち状態にする

            break;

        case '1':   // [6-6-34]姫

            // [6-6-35]姫の会話メッセージを表示する
            printf("＊「かみに　いのりを　ささげます。¥n"
                "おお　かみよ！¥n"
                "ゆうしゃさまに　しゅくふくを！¥n"
            );

            // [6-6-36]キーボード入力待ち状態にする
            _getch();

            // [6-6-37]プレイヤーのHPを回復させる
            characters[CHARACTER_PLAYER].hp = characters[CHARACTER_PLAYER].maxHp;

            // [6-6-38]プレイヤーのMPを回復させる
            characters[CHARACTER_PLAYER].mp = characters[CHARACTER_PLAYER].maxMp;

            break;

        case '2':   // [6-6-39]魔王

            // [6-6-40]魔王の会話メッセージを表示する
            printf("＊「おろかな　にんげんよ！¥n"
                "わが　やぼうを　はばむものは¥n"
                "このよから　けしさってくれる！¥n"
            );

            // [6-6-41]キーボード入力待ち状態にする
            _getch();

            // [6-6-42]魔王との戦闘を発生させる
            Battle(MONSTER_BOSS);

            // [6-6-43]魔王が死んだかどうかを判定する
            if (characters[CHARACTER_MONSTER].hp <= 0)
            {
                // [6-6-44]画面をクリアする
                system("cls");

                // [6-6-45]エンディングのメッセージを表示する
                printf("　まおうは　ほろび　せかいは¥n"
                    "めつぼうのききから　すくわれた！¥n"
                    "¥n"
                    "　おうは　ふれをだし　ゆうしゃを¥n"
                    "さがしもとめたが、だれも¥n"
                    "みたものは　いなかったという…¥n"
                    "¥n"
                    "¥n"
                    "　　　　ＴＨＥ　ＥＮＤ");

                // [6-6-46]キーボード入力待ち状態にする
                _getch();

                // [6-6-47]ゲームを終了する
                return 0;
            }

            break;
        }

        // [6-6-48]移動先のマスの種類によって分岐させる
        switch (map[currentMap][playerY][playerX])
        {
        case '.':   // [6-6-49]平地
        case '#':   // [6-6-50]橋

            // [6-6-51]敵と遭遇したかどうかを判定する
            if ((currentMap == MAP_FIELD) && (rand() % 16 == 0))
            {
                // [6-6-52]雑魚モンスターとの戦闘を発生させる
                Battle(MONSTER_SLIME);
            }

            break;

        default:    // [6-6-53]上記以外のマス
            playerX = lastPlayerX;// [6-6-54]プレイヤーのX座標を移動前に戻す
            playerY = lastPlayerY;// [6-6-55]プレイヤーのY座標を移動前に戻す
            break;
        }

        // [6-6-56]プレイヤーが死んだかどうかを判定する
        if (characters[CHARACTER_PLAYER].hp <= 0)
        {
            // [6-6-57]ゲームを初期化する関数を呼び出す
            Init();

            // [6-6-58]画面を再描画する
            DrawMap();

            // [6-6-59]王様のメッセージを表示する
            printf("＊「おお　ゆうしゃよ！¥n"
                "かみが　そなたを　すくわれた！¥n"
                "ゆうしゃに　えいこう　あれ！¥n");

            // [6-6-60]キーボードの入力待ち状態にする
            _getch();
        }
    }
}