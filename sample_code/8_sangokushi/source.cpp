// [1]ヘッダーをインクルードする場所

#include <stdio.h>      // [1-1]標準入出力ヘッダーをインクルードする
#include <stdlib.h>     // [1-2]標準ライブラリヘッダーをインクルードする
#include <time.h>       // [1-3]時間管理ヘッダーをインクルードする
#include <conio.h>      // [1-4]コンソール入出力ヘッダーをインクルードする
#include <vector>       // [1-5]ベクターヘッダーをインクルードする
#include <algorithm>    // [1-6]アルゴリズムヘッダーをインクルードする

// [2]定数を定義する場所

#define TROOP_BASE      (5)     // [2-1]基本兵数を定義する
#define TROOP_MAX       (9)     // [2-2]最大兵数を定義する
#define TROOP_UNIT      (10000) // [2-3]兵数の単位を定義する
#define START_YEAR      (196)   // [2-4]開始年を定義する
#define CHRONOLOGY_MAX  (1024)  // [2-5]年表の最大文字数を定義する

// [3]列挙定数を定義する場所

// [3-1]大名の種類を定義する
enum
{
    LORD_RIKAKU,    // [3-1- 1]李傕
    LORD_RYUBI,     // [3-1- 2]劉備
    LORD_ENSHO,     // [3-1- 3]袁紹
    LORD_SOSO,      // [3-1- 4]曹操
    LORD_RYOFU,     // [3-1- 5]呂布
    LORD_RYUHYO,    // [3-1- 6]劉表
    LORD_SONSAKU,   // [3-1- 7]孫策
    LORD_RYUSHO,    // [3-1- 8]劉璋
    LORD_BATO,      // [3-1- 9]馬騰
    LORD_KOSONSAN,  // [3-1-10]公孫瓚
    LORD_MAX        // [3-1-11]種類の数
};

// [3-2]城の種類を定義する
enum
{
    CASTLE_SHIREI,  // [3-2- 1]司隸
    CASTLE_YOSHU,   // [3-2- 2]豫州
    CASTLE_KISHU,   // [3-2- 3]冀州
    CASTLE_ENSHU,   // [3-2- 4]兗州
    CASTLE_JOSHU,   // [3-2- 5]徐州
    CASTLE_KEISHU,  // [3-2- 6]荊州
    CASTLE_YOUSHU,  // [3-2- 7]揚州
    CASTLE_EKISHU,  // [3-2- 8]益州
    CASTLE_RYOSHU,  // [3-2- 9]涼州
    CASTLE_YUSHU,   // [3-2-10]幽州
    CASTLE_MAX      // [3-2-11]種類の数
};

// [4]構造体を宣言する場所

// [4-1]大名の構造体を宣言する
typedef struct {
    char familyName[16];    // [4-1-1]姓
    char firstName[16];     // [4-1-2]名
} LORD;

// [4-2]城の構造体を宣言する
typedef struct {
    const char* name;               // [4-2-1]名前
    int                 owner;              // [4-2-2]城主
    int                 troopCount;         // [4-2-3]兵数
    std::vector<int>    connectedCastles;   // [4-2-4]接続された城のリスト
} CASTLE;

// [5]変数を宣言する場所

// [5-1]大名の配列を宣言する
LORD lords[LORD_MAX] =
{
    {"李傕",      "稚然",},   // [5-1- 1]LORD_RIKAKU    李傕
    {"劉備",      "玄徳",},   // [5-1- 2]LORD_RYUBI     劉備
    {"袁紹",      "本初",},   // [5-1- 3]LORD_ENSHO     袁紹
    {"曹操",      "孟徳",},   // [5-1- 4]LORD_SOSO      曹操
    {"呂布",      "奉先",},   // [5-1- 5]LORD_RYOFU     呂布
    {"劉表",      "景升",},   // [5-1- 6]LORD_RYUHYO    劉表
    {"孫策",      "伯符",},   // [5-1- 7]LORD_SONSAKU   孫策
    {"劉璋",      "季玉",},   // [5-1- 8]LORD_RYUSHO    劉璋
    {"馬騰",      "寿成",},   // [5-1- 9]LORD_BATO      馬騰
    {"公孫瓚",    "伯珪",},   // [5-1-10]LORD_KOSONSAN  公孫瓚
};

// [5-2]城の配列を宣言する
CASTLE castles[CASTLE_MAX] =
{
    // [5-2-1]CASTLE_SHIREI 司隸
    {
        "司隸",         // const char* name     名前
        LORD_RIKAKU,    // int owner            城主
        TROOP_BASE,     // int troopCount       兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_YOSHU,   // 豫州
            CASTLE_KISHU,   // 冀州
            CASTLE_ENSHU,   // 兗州
            CASTLE_KEISHU,  // 荊州
            CASTLE_EKISHU,  // 益州
            CASTLE_RYOSHU   // 涼州
        }
    },

    // [5-2-2]CASTLE_YOSHU  豫州
    {
        "豫州",     // const char* name 名前
        LORD_RYUBI, // int owner        城主
        TROOP_BASE, // int troopCount   兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_SHIREI,  // 司隸
            CASTLE_ENSHU,   // 兗州
            CASTLE_JOSHU,   // 徐州
            CASTLE_KEISHU,  // 荊州
            CASTLE_YOUSHU   // 揚州
        }
    },

    // [5-2-3]CASTLE_KISHU  冀州
    {
        "冀州",     // const char* name 名前
        LORD_ENSHO, // int owner        城主
        TROOP_BASE, // int troopCount   兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_SHIREI,  // 司隸
            CASTLE_ENSHU,   // 兗州
            CASTLE_JOSHU,   // 徐州
            CASTLE_YUSHU    // 幽州
        }
    },

    // [5-2-4]CASTLE_ENSHU  兗州
    {
        "兗州",     // const char* name 名前
        LORD_SOSO,  // int owner        城主
        TROOP_BASE, // int troopCount   兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_SHIREI,  // 司隸
            CASTLE_YOSHU,   // 豫州
            CASTLE_KISHU,   // 冀州
            CASTLE_JOSHU    // 徐州
        }
    },

    // [5-2-5]CASTLE_JOSHU  徐州
    {
        "徐州",     // const char* name 名前
        LORD_RYOFU, // int owner        城主
        TROOP_BASE, // int troopCount   兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_YOSHU,   // 豫州
            CASTLE_KISHU,   // 冀州
            CASTLE_ENSHU,   // 兗州
            CASTLE_YOUSHU   // 揚州
        }
    },

    // [5-2-6]CASTLE_KEISHU 荊州
    {
        "荊州",         // const char* name 名前
        LORD_RYUHYO,    // int owner        城主
        TROOP_BASE,     // int troopCount   兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_SHIREI,  // 司隸
            CASTLE_YOSHU,   // 豫州
            CASTLE_YOUSHU,  // 揚州
            CASTLE_EKISHU   // 益州
        }
    },

    // [5-2-7]CASTLE_YOUSHU 揚州
    {
        "揚州",         // const char* name 名前
        LORD_SONSAKU,   // int owner        城主
        TROOP_BASE,     // int troopCount   兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_YOSHU,   // 豫州
            CASTLE_JOSHU,   // 徐州
            CASTLE_KEISHU   // 荊州
        }
    },

    // [5-2-8]CASTLE_EKISHU 益州
    {
        "益州",         // const char* name 名前
        LORD_RYUSHO,    // int owner        城主
        TROOP_BASE,     // int troopCount   兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_SHIREI,  // 司隸
            CASTLE_KEISHU   // 荊州
        }
    },

    // [5-2-9]CASTLE_RYOSHU 涼州
    {
        "涼州",     // const char* name 名前
        LORD_BATO,  // int owner        城主
        TROOP_BASE, // int troopCount   兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_SHIREI   // 司隸
        }
    },

    // [5-2-10]CASTLE_YUSHU 幽州
    {
        "幽州",         // const char* name 名前
        LORD_KOSONSAN,  // int owner        城主
        TROOP_BASE,     // int troopCount   兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_KISHU    // 冀州
        }
    }
};

int year;  // [5-3]現在の年を宣言する

int playerLord;// [5-4]プレイヤーの大名を宣言する

char chronology[CHRONOLOGY_MAX];// [5-5]年表を宣言する

// [6]関数を宣言する場所

// [6-1]城の数を数える関数を宣言する
int GetCastleCount(int _lord)
{
    // [6-1-1]城の数を宣言する
    int castleCount = 0;

    // [6-1-2]すべての城を反復する
    for (int i = 0; i < CASTLE_MAX; i++)
    {
        // [6-1-3]対象の城の城主が、対象の大名かどうかを判定する
        if (castles[i].owner == _lord)
        {
            // [6-1-4]城の数を加算する
            castleCount++;
        }
    }

    // [6-1-5]城の数を返す
    return castleCount;
}

// [6-2]基本情報を描画する関数を宣言する
void DrawScreen()
{
    system("cls");// [6-2-1]画面をクリアする
/*
    // [6-2-1.5]地図のサンプルを描画する
    printf("%s",
        " 196ねん　　　　　　　　　　9幽州5　　　\n"    // 01
        "　　　　　　　　　　　　　　公孫　～　～\n"    // 02
        "8涼州5　　　　　　2冀州5　　　～～～～～\n"    // 03
        "馬騰　　　　　　　袁紹　　～～～～～～～\n"    // 04
        "　　　　　　　　　　　　　　～～　　～～\n"    // 05
        "　　　　　　　　　3兗州5　　　　　～～～\n"    // 06
        "　　　0司隸5　　　曹操　　4徐州5　～～～\n"    // 07
        "　　　李傕　　　　　　　　呂布　～～～～\n"    // 08
        "　　　　　　　　　1豫州5　　　　　～～～\n"    // 09
        "　　　　　　　　　劉備　　　　　　　～～\n"    // 10
        "7益州5　　5荊州5　　　　6揚州5　　　～～\n"    // 11
        "劉璋　　　劉表　　　　　孫策　　　　～～\n"    // 12
        "　　　　　　　　　　　　　　　　　～～～\n"    // 13
        "　　　　　　　　　　　　　　　　　～～～\n"    // 14
        "　　　　　　　　　　　　　　　～～～～～\n"    // 15
        "　　　　　　　　　～～～～～～～～～～～\n"    // 16
    );
*/
// [6-2-2]地図の1行目を描画する
    printf(" %dねん　　　　　　　　　　%d%.6s%d　　　\n",
        year,                               // 年
        CASTLE_YUSHU,                       // 幽州の州番号
        castles[CASTLE_YUSHU].name,         // 幽州の名前
        castles[CASTLE_YUSHU].troopCount);  // 幽州の兵数

    // [6-2-3]地図の2行目を描画する
    printf("　　　　　　　　　　　　　　%.6s　～　～\n",
        lords[castles[CASTLE_YUSHU].owner].familyName); // 幽州の州牧の氏名

    // [6-2-4]地図の3行目を描画する
    printf("%d%.6s%d　　　　　　%d%.6s%d　　　～～～～～\n",
        CASTLE_RYOSHU,                      // 涼州の州番号
        castles[CASTLE_RYOSHU].name,        // 涼州の名前
        castles[CASTLE_RYOSHU].troopCount,  // 涼州の兵数
        CASTLE_KISHU,                       // 冀州の州番号
        castles[CASTLE_KISHU].name,         // 冀州の名前
        castles[CASTLE_KISHU].troopCount);  // 冀州の兵数

    // [6-2-5]地図の4行目を描画する
    printf("%.6s　　　　　　　%.6s　　～～～～～～～\n",
        lords[castles[CASTLE_RYOSHU].owner].familyName,     // 涼州の州牧の氏名
        lords[castles[CASTLE_KISHU].owner].familyName);     // 冀州の州牧の氏名

    // [6-2-6]地図の5行目を描画する
    printf("　　　　　　　　　　　　　　～～　　～～\n");

    // [6-2-7]地図の6行目を描画する
    printf("　　　　　　　　　%d%.6s%d　　　　　～～～\n",
        CASTLE_ENSHU,                       // 兗州の州番号
        castles[CASTLE_ENSHU].name,         // 兗州の名前
        castles[CASTLE_ENSHU].troopCount);  // 兗州の兵数

    // [6-2-8]地図の7行目を描画する
    printf("　　　%d%.6s%d　　　%.6s　　%d%.6s%d　～～～\n",
        CASTLE_SHIREI,                                  // 司隸の州番号
        castles[CASTLE_SHIREI].name,                    // 司隸の名前
        castles[CASTLE_SHIREI].troopCount,              // 司隸の兵数
        lords[castles[CASTLE_ENSHU].owner].familyName,  // 兗州の州牧の氏名
        CASTLE_JOSHU,                                   // 徐州の州番号
        castles[CASTLE_JOSHU].name,                     // 徐州の名前
        castles[CASTLE_JOSHU].troopCount);              // 徐州の兵数

    // [6-2-9]地図の8行目を描画する
    printf("　　　%.6s　　　　　　　　%.6s　～～～～\n",
        lords[castles[CASTLE_SHIREI].owner].familyName, // 司隸の州牧の氏名
        lords[castles[CASTLE_JOSHU].owner].familyName); // 徐州の州牧の氏名

    // [6-2-10]地図の9行目を描画する
    printf("　　　　　　　　　%d%s%d　　　　～～～～\n",
        CASTLE_YOSHU,                       // 豫州の州番号
        castles[CASTLE_YOSHU].name,         // 豫州の名前
        castles[CASTLE_YOSHU].troopCount);  // 豫州の兵数

    // [6-2-11]地図の10行目を描画する
    printf("　　　　　　　　　%.6s　　　　　　～～～\n",
        lords[castles[CASTLE_YOSHU].owner].familyName); // 豫州の州牧の氏名

    // [6-2-12]地図の11行目を描画する
    printf("　　　　　%d%.6s%d　　　　　　%d%.6s%d　～～\n",
        CASTLE_KEISHU,                      // 荊州の州番号
        castles[CASTLE_KEISHU].name,        // 荊州の名前
        castles[CASTLE_KEISHU].troopCount,  // 荊州の兵数
        CASTLE_YOUSHU,                      // 揚州の州番号
        castles[CASTLE_YOUSHU].name,        // 揚州の名前
        castles[CASTLE_YOUSHU].troopCount); // 揚州の兵数

    // [6-2-13]地図の12行目を描画する
    printf("%d%.6s%d　　%.6s　　　　　　　%.6s　　～～\n",
        CASTLE_EKISHU,                                      // 益州の州番号
        castles[CASTLE_EKISHU].name,                        // 益州の名前
        castles[CASTLE_EKISHU].troopCount,                  // 益州の兵数
        lords[castles[CASTLE_KEISHU].owner].familyName,     // 荊州の州牧の氏名
        lords[castles[CASTLE_YOUSHU].owner].familyName);    // 揚州の州牧の氏名

    // [6-2-14]地図の13行目を描画する
    printf("%.6s　　　　　　　　　　　　　　　　～～\n",
        lords[castles[CASTLE_EKISHU].owner].familyName);    // 益州の州牧の氏名

    // [6-2-15]地図の14行目を描画する
    printf("　　　　　　　　　　　　　　　　　　～～\n");

    // [6-2-16]地図の15行目を描画する
    printf("　　　　　　　　　　　　　　　　～～～～\n");

    // [6-2-17]地図の16行目を描画する
    printf("　　　　　　　　　～～～～～～～～～～～\n");

    // [6-2-18]1行空けておく
    printf("\n");
}

// [6-3]ゲームを初期化する関数を宣言する
void Init()
{
    year = START_YEAR;// [6-3-1]年をリセットする

    // [6-3-2]すべての城を反復する
    for (int i = 0; i < CASTLE_MAX; i++)
    {
        // [6-3-3]城主を初期化する
        castles[i].owner = i;

        // [6-3-4]兵数を初期化する
        castles[i].troopCount = TROOP_BASE;
    }

    // [6-3-5]年表をクリアする
    sprintf_s(chronology, "");

    DrawScreen();// [6-3-6]基本情報を描画する画面を呼び出す

    // [6-3-7]大名の選択を促すメッセージを表示する
    printf("わがきみ、われらがしろは　このちずの\n"
        "どこに　ありまするか？！（0～%d）\n",
        CASTLE_MAX - 1);    // 城番号の最大値

    printf("\n");// [6-3-8]1行空ける

    // [6-3-9]選択された城を保持する変数を宣言する
    int selectedCastle;

    // [6-3-10]範囲内の城番号が入力されるまで反復する
    do {
        selectedCastle = _getch() - '0';// [6-3-11]城番号を入力する
    } while ((selectedCastle < 0) || (selectedCastle >= CASTLE_MAX));

    // [6-3-12]選択した城の城主をプレイヤーの大名とする
    playerLord = castles[selectedCastle].owner;

    // [6-3-13]決定した大名を通知するメッセージを表示する
    printf("%sさま、%sから　てんかとういつを\nめざしましょうぞ！\n",
        lords[playerLord].firstName,    // 選択された大名の名
        castles[playerLord].name);      // 選択された城の名前

    _getch();// [6-3-14]キーボード入力を待つ
}

// [6-4]攻城戦の関数を宣言する
void Siege(
    int _offensiveLord,         // 攻め込んだ大名
    int _offensiveTroopCount,   // 攻め込んだ兵数
    int _castle)                // 攻め込まれた城
{
    system("cls");// [6-4-1]画面をクリアする

    // [6-4-2]攻城戦の名前を表示する
    printf("～%sの　たたかい～\n", castles[_castle].name);

    printf("\n");// [6-4-3]1行空ける

    // [6-4-4]攻め込まれた大名を宣言する
    int defensiveLord = castles[_castle].owner;

    // [6-4-5]無限ループする
    while (1)
    {
        // [6-4-6]合戦の経過を表示する
        printf("%sぐん（%5dにん）　Ｘ　%sぐん（%5dにん）\n",

            // 攻め込んだ大名の姓
            lords[_offensiveLord].familyName,

            // 攻め込んだ兵数
            _offensiveTroopCount * TROOP_UNIT,

            // 攻め込まれた大名の姓
            lords[defensiveLord].familyName,

            // 攻め込まれた城の兵数
            castles[_castle].troopCount * TROOP_UNIT);

        _getch();// [6-4-7]キーボード入力を待つ

        // [6-4-8]攻守いずれかの兵数が0以下かどうか判定する
        if ((_offensiveTroopCount <= 0) || (castles[_castle].troopCount <= 0))
        {
            break;// [6-4-9]ループを抜ける
        }

        // [6-4-10]0～2の乱数が、0かどうかを判定する
        if (rand() % 3 == 0)
        {
            castles[_castle].troopCount--;// [6-4-11]守備側の兵を減らす
        }

        // [6-4-12]0～2の乱数が、1か2なら
        else
        {
            _offensiveTroopCount--;// [6-4-13]攻撃側の兵を減らす
        }
    }

    printf("\n");// [6-4-14]1行空ける

    // [6-4-15]守備側の兵が全滅したかどうかを判定する
    if (castles[_castle].troopCount <= 0)
    {
        // [6-4-16]落城したメッセージを表示する
        printf("%s　らくじょう！！\n", castles[_castle].name);

        printf("\n");// [6-4-17]1行空ける

        // [6-4-18]攻撃側の大名の城にする
        castles[_castle].owner = _offensiveLord;

        // [6-4-19]攻撃側の兵を入城させる
        castles[_castle].troopCount = _offensiveTroopCount;

        // [6-4-20]城主が攻め込んだ大名に変わったメッセージを表示する
        printf("%sは　%sの　ものとなります\n",
            castles[_castle].name,
            lords[_offensiveLord].familyName);

        printf("\n");// [6-4-21]1行空ける

        // [6-4-22]守備側の大名が、城をすべて失ったかどうかを判定する
        if (GetCastleCount(defensiveLord) <= 0)
        {
            char str[128];  // [6-4-23]追加する文字列を宣言する

            // [6-4-24]追加する文字列を作成する
            sprintf_s(str, "%dねん　%s（%s）が　%sで　%s（%s）を　ほろぼす\n",
                year,                               // 滅ぼした年
                lords[_offensiveLord].familyName,   // 滅ぼした大名の姓
                lords[_offensiveLord].firstName,    // 滅ぼした大名の名
                castles[_castle].name,              // 戦場の名前
                lords[defensiveLord].familyName,    // 滅ぼされた大名の姓
                lords[defensiveLord].firstName);    // 滅ぼされた大名の名

            // [6-4-25]年表に文字列を追加する
            strcat_s(chronology, str);
        }
    }

    // [6-4-26]守備側の兵が全滅していなければ
    else
    {
        // [6-4-27]攻撃側が全滅したメッセージを表示する
        printf("%sぐん　かいめつ！！\n"
            "\n"
            "%sぐんが　%sを　まもりきりました！\n",
            lords[_offensiveLord].familyName,
            lords[defensiveLord].familyName,
            castles[_castle].name);
    }
}

// [6-5]プログラムの実行開始点を宣言する
int main()
{
    system("chcp 65001");// [6-5-0]コンソールの文字セットをUTF-8に設定する

    srand((unsigned int)time(NULL));// [6-5-1]乱数をシャッフルする

start:  // [6-5-2]ゲームの開始ラベル
    ;   // [6-5-3]空文

    Init();// [6-5-4]ゲームをリセットする関数を呼び出す

    // [6-5-5]メインループ
    while (1)
    {
        int turnOrder[CASTLE_MAX];  // [6-5-6]ターンの順のテーブルを宣言する

        // [6-5-7]ターンの順を初期化する
        for (int i = 0; i < CASTLE_MAX; i++)
        {
            turnOrder[i] = i;// [6-5-8]ターンの順を初期化する
        }

        // [6-5-9]すべての城を反復する
        for (int i = 0; i < CASTLE_MAX; i++)
        {
            // [6-5-10]ターンをランダムに入れ替える
            std::swap(turnOrder[i], turnOrder[rand() % CASTLE_MAX]);
        }

        // [6-5-11]すべてのターンを反復する
        for (int i = 0; i < CASTLE_MAX; i++)
        {
            DrawScreen();// [6-5-12]基本情報画面を再描画する

            // [6-5-13]すべてのターンを反復する
            for (int j = 0; j < CASTLE_MAX; j++)
            {
                // [6-5-14]現在のターンの城にカーソルを描画する
                printf("%s", (j == i) ? "＞" : "　");

                // [6-5-15]各ターンの城の名前を描画する
                printf("%.6s", castles[turnOrder[j]].name);
            }

            // [6-5-16]改行して1行空ける
            printf("\n\n");

            // [6-5-17]現在のターンの城の番号を宣言する
            int currentCastle = turnOrder[i];

            // [6-5-18]メッセージを表示する
            printf("%sの　%sの　ひょうじょうちゅう…\n",
                lords[castles[currentCastle].owner].familyName, // 城主の姓
                castles[currentCastle].name);                   // 城の名前

            printf("\n");// [6-5-19]1行空ける

            // [6-5-20]現在の城の城主がプレイヤーかどうかを判定する
            if (castles[currentCastle].owner == playerLord)
            {
                // [6-5-21]進軍先の城の指定を促すメッセージを表示する
                printf("%sさま、どこに　しんぐん　しますか？\n",
                    lords[castles[currentCastle].owner].firstName);

                printf("\n");// [6-5-22]1行空ける

                // [6-5-23]すべての接続された城を反復する
                for (int j = 0; j < (int)castles[currentCastle].connectedCastles.size(); j++)
                {
                    // [6-5-24]接続された城の番号と名前を表示する
                    printf("%d %s\n",
                        castles[currentCastle].connectedCastles[j],
                        castles[castles[currentCastle].connectedCastles[j]].name);
                }

                printf("\n");// [6-5-25]1行空ける

                // [6-5-26]進軍先の城を入力して宣言する
                int targetCastle = _getch() - '0';

                // [6-5-27]現在の城と対象の城が接続しているかどうかを保持するフラグを宣言する
                bool isConnected = false;

                // [6-5-28]現在の城と接続しているすべての城を反復する
                for (int castle : castles[currentCastle].connectedCastles)
                {
                    // [6-5-29]対象の城との接続が確認できたら
                    if (castle == targetCastle)
                    {
                        isConnected = true;// [6-5-30]接続の有無のフラグを立てる

                        break;// [6-5-31]反復を抜ける
                    }
                }

                // [6-5-32]接続している城が選ばれなかったら
                if (!isConnected)
                {
                    // [6-5-33]進軍を取りやめるメッセージを表示する
                    printf("しんぐんを　とりやめました\n");

                    _getch();// [6-5-34]キーボード入力を待つ

                    continue;// [6-5-35]次の国の評定にスキップする
                }

                // [6-5-36]現在の城の兵数を最大進軍数として宣言する
                int troopMax = castles[currentCastle].troopCount;

                // [6-5-37]進軍先がプレイヤーの城かどうかを判定する
                if (castles[targetCastle].owner == playerLord)
                {
                    // [6-5-38]進軍先の城の空き兵数を宣言する
                    int targetCapacity = TROOP_MAX - castles[targetCastle].troopCount;

                    // [6-5-39]現在の城の兵数か、進軍先の空き兵数の少ないほうを最大進軍兵数とする
                    troopMax = std::min(troopMax, targetCapacity);
                }

                // [6-5-40]入力された城を通知して、移動する兵数の入力を促すメッセージを表示する
                printf("%sに　なんまんにん　しんぐん　しますか？（0～%d）\n",
                    castles[targetCastle].name,	// 進軍先の城の名前
                    troopMax);					// 進軍兵数

                // [6-5-41]進軍兵数を宣言する
                int troopCount;

                // [6-5-42]範囲内の兵数が入力されるまで反復する
                do {
                    troopCount = _getch() - '0';// [6-5-43]進軍兵数を入力する
                } while ((troopCount < 0) || (troopCount > troopMax));

                // [6-5-44]現在の城の兵数を、移動する分だけ減らす
                castles[currentCastle].troopCount -= troopCount;

                // [6-5-45]移動先がプレイヤーの城なら
                if (castles[targetCastle].owner == playerLord)
                {
                    // [6-5-46]進軍先の城の兵数に、移動兵数を加算する
                    castles[targetCastle].troopCount += troopCount;
                }

                // [6-5-47]改行する
                printf("\n");

                // [6-5-48]入力された進軍兵数を通知する
                printf("%sに　%dにん%s",
                    castles[targetCastle].name, // 進軍先の城の名前
                    troopCount * TROOP_UNIT,	// 進軍兵数

                    // 進軍先の城の城主がプレイヤーかどうかを判定する
                    (castles[targetCastle].owner == playerLord)
                    ? "　いどう　しました"          // プレイヤーの城なら
                    : "で　しゅつじんじゃ～！！");  // 敵の城なら

                // [6-5-49]進軍先が敵の城かどうかを判定する
                if (castles[targetCastle].owner != playerLord)
                {
                    _getch();// [6-5-50]キーボード入力を待つ

                    // [6-5-51]攻城戦の関数を呼び出す
                    Siege(
                        playerLord,     // int _offensiveLord       攻め込んだ大名
                        troopCount,     // int _offensiveTroopCount 攻め込んだ兵数
                        targetCastle);  // int _castle              攻め込まれた城
                }
            }

            // [6-5-52]現在の城の城主がプレイヤーでなければ
            else
            {
                // [6-5-53]接続された敵の城のリストを宣言する
                std::vector<int> connectedEnemyCastles;

                // [6-5-54]すべての接続された城を反復する
                for (int j = 0;
                    j < (int)castles[currentCastle].connectedCastles.size();
                    j++)
                {
                    // [6-5-55]敵の城かどうかを判定する
                    if (castles[castles[currentCastle].connectedCastles[j]].owner
                        != castles[currentCastle].owner)
                    {
                        // [6-5-56]接続された敵の城のリストに加える
                        connectedEnemyCastles.push_back(
                            castles[currentCastle].connectedCastles[j]);
                    }
                }

                // [6-5-57]接続された敵の城があるかどうかを判定する
                if (connectedEnemyCastles.size() > 0)
                {
                    // [6-5-58]兵の少ない順に並び替える
                    sort(connectedEnemyCastles.begin(), connectedEnemyCastles.end(),
                        // 2つの城を比較するラムダ
                        [](int _castle0, int _castle1)
                        {
                            // リストの後ろの城のほうが、兵が多いかどうかを判定して返す
                            return castles[_castle0].troopCount < castles[_castle1].troopCount;
                        }
                    );

                    // [6-5-59]最も兵の少ない城のみになるまで反復する
                    while (
                        // 隣接する敵の城が2城以上である
                        (connectedEnemyCastles.size() > 1)

                        // かつその中で最も兵数の少ない城よりも兵数の多い城があれば
                        && (castles[connectedEnemyCastles.front()].troopCount
                            < castles[connectedEnemyCastles.back()].troopCount))
                    {
                        // [6-5-60]リストから最後尾を削除する
                        connectedEnemyCastles.pop_back();
                    }

                    // [6-5-61]攻め込む城を宣言する
                    int targetCastle =
                        connectedEnemyCastles[rand() % connectedEnemyCastles.size()];

                    // [6-5-62]攻め込むかどうかを判定する
                    if (
                        // 兵数が基準値以上であるか
                        (castles[currentCastle].troopCount >= TROOP_BASE)

                        // こちらの兵数が守備兵を差し引いて相手の2倍以上であれば
                        || (castles[currentCastle].troopCount - 1
                            >= castles[targetCastle].troopCount * 2))
                    {
                        // [6-5-63]攻め込む兵数を宣言する
                        int troopCount = std::max(castles[currentCastle].troopCount - 1, 0);

                        // [6-5-64]現在の城の兵数から攻め込む兵数を減算する
                        castles[currentCastle].troopCount -= troopCount;

                        // [6-5-65]攻め込むメッセージを表示する
                        printf("%sの　%s（%s）が　%sに　せめこみました！\n",
                            castles[currentCastle].name,
                            lords[castles[currentCastle].owner].familyName,
                            lords[castles[currentCastle].owner].firstName,
                            castles[targetCastle].name);

                        _getch();// [6-5-66]キーボード入力を待つ

                        // [6-5-67]攻城戦の関数を呼び出す
                        Siege(

                            // int _offensiveLord       攻め込んだ大名
                            castles[currentCastle].owner,

                            // int _offensiveTroopCount 攻め込んだ兵数
                            troopCount,

                            // int _castle              攻め込まれた城
                            targetCastle);
                    }
                }

                // [6-5-68]接続された敵の城がなければ
                else
                {
                    // [6-5-69]接続された前線の城のリストを宣言する
                    std::vector<int> frontCastles;

                    // [6-5-70]すべての接続された城を反復する
                    for (int neighbor : castles[currentCastle].connectedCastles)
                    {
                        // [6-5-71]隣接する城に接続されたすべての城を反復する
                        for (int neighborNeighbor : castles[neighbor].connectedCastles)
                        {
                            // [6-5-72]対象の城が敵の城に隣接しているかどうかを判定する
                            if (castles[neighborNeighbor].owner != castles[neighbor].owner)
                            {
                                frontCastles.push_back(neighbor);// [6-5-73]前線の城のリストに追加する

                                break;// [6-5-74]反復を抜ける
                            }
                        }
                    }

                    // [6-5-75]兵を送る城のリストを宣言する
                    std::vector<int> destCastles =

                        // 前線の城がないかどうかを判定する
                        frontCastles.empty()

                        // なければ接続された城のリストを設定する
                        ? castles[currentCastle].connectedCastles

                        // あれば前線の城のリストを設定する
                        : frontCastles;

                    // [6-5-76]兵の少ない順に並び替える
                    sort(destCastles.begin(), destCastles.end(),
                        [](int _castle0, int _castle1)
                        {
                            return castles[_castle0].troopCount < castles[_castle1].troopCount;
                        }
                    );

                    // [6-5-77]最も兵の少ない城のみになるまで反復する
                    while (
                        // 兵を送る先の城の候補が複数ある
                        (destCastles.size() > 1)

                        // かつその中で最も兵数の少ない城よりも兵数の多い城があれば
                        && (castles[destCastles.front()].troopCount
                            < castles[destCastles.back()].troopCount))
                    {
                        // [6-5-78]リストから最後尾を削除する
                        destCastles.pop_back();
                    }

                    // [6-5-79]兵を送る城を宣言する
                    int targetCastle = destCastles[rand() % destCastles.size()];

                    // [6-5-80]送る兵数を宣言する
                    int sendTroopCount = TROOP_MAX - castles[targetCastle].troopCount;

                    // [6-5-81]兵を送る先の城が前線かどうかを判定する
                    if (!frontCastles.empty())
                    {
                        // [6-5-82]送り先の空き兵数と送り元の兵数のうち、少ない兵数を設定する
                        sendTroopCount = std::min(

                            // 送り先の空き兵数
                            sendTroopCount,

                            // 送り元の兵数
                            castles[currentCastle].troopCount);
                    }

                    // [6-5-83]兵を送る先の城が前線でない味方の城なら
                    else
                    {
                        // [6-5-84]送り先の空き兵数と送り元の余剰兵数のうち、少ない兵数を設定する
                        sendTroopCount = std::min(

                            // 送り先の空き兵数
                            sendTroopCount,

                            // 送り元の兵数
                            castles[currentCastle].troopCount - (TROOP_BASE - 1));
                    }

                    // [6-5-85]送る兵がいるかどうかを判定する
                    if (sendTroopCount > 0)
                    {
                        // [6-5-86]送り元の兵数を減らす
                        castles[currentCastle].troopCount -= sendTroopCount;

                        // [6-5-87]送り先の兵数を増やす
                        castles[targetCastle].troopCount += sendTroopCount;

                        // [6-5-88]兵士が移動したメッセージを表示する
                        printf("%sから　%sに　%dにん　いどうしました\n",
                            castles[currentCastle].name,
                            castles[targetCastle].name,
                            sendTroopCount * TROOP_UNIT);
                    }
                }
            }

            _getch();// [6-5-89]キーボード入力を待つ

            // [6-5-90]プレイヤーの城がないかどうかを判定する
            if (GetCastleCount(playerLord) <= 0)
            {
                DrawScreen();// [6-5-91]画面を描画する

                printf("%s", chronology);// [6-5-92]年表を表示する

                printf("\n");// [6-5-93]1行空ける

                // [6-5-94]ゲームオーバーのメッセージを表示する
                printf("ＧＡＭＥ　ＯＶＥＲ\n");

                _getch();// [6-5-95]キーボード入力を待つ

                goto start;// [6-5-96]ゲームの開始ラベルにジャンプする
            }

            // [6-5-97]プレイヤーすべての城を所有しているかどうかを判定する
            else if (GetCastleCount(playerLord) >= CASTLE_MAX)
            {
                DrawScreen();// [6-5-98]画面を描画する

                printf("%s", chronology);// [6-5-99]年表を表示する

                // [6-5-100]エンディングのメッセージを表示する
                printf("%dねん　%s%sが　せいいたいしょうぐんに　にんぜられる\n"
                    "%dねん　%s%sが　%sばくふを　ひらく\n"
                    "\n"
                    "ＴＨＥ　ＥＮＤ",
                    year + 3,                       // 征夷大将軍になった年
                    lords[playerLord].familyName,   // プレイヤーの大名の姓
                    lords[playerLord].firstName,    // プレイヤーの大名の名
                    year + 3,                       // 幕府を開いた年
                    lords[playerLord].familyName,   // プレイヤーの大名の姓
                    lords[playerLord].firstName,    // プレイヤーの大名の名
                    lords[playerLord].familyName);  // 幕府の名前

                _getch();// [6-5-101]キーボード入力を待つ

                goto start;// [6-5-102]ゲーム開始ラベルにジャンプする
            }
        }

        year++;// [6-5-103]年を進める

        // [6-5-104]すべての城を反復する
        for (int i = 0; i < CASTLE_MAX; i++)
        {
            // [6-5-105]対象の城の兵数が基本兵数未満かどうかを判定する
            if (castles[i].troopCount < TROOP_BASE)
            {
                castles[i].troopCount++;// [6-5-106]兵数を増やす
            }

            // [6-5-107]対象の城の兵数が基本兵数より多いかどうかを判定する
            else if (castles[i].troopCount > TROOP_BASE)
            {
                castles[i].troopCount--;// [6-5-108]兵数を減らす
            }
        }
    }
}