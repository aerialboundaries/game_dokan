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
#define TROOP_UNIT      (1000)  // [2-3]兵数の単位を定義する
#define START_YEAR      (1570)  // [2-4]開始年を定義する
#define CHRONOLOGY_MAX  (1024)  // [2-5]年表の最大文字数を定義する

// [3]列挙定数を定義する場所

// [3-1]大名の種類を定義する
enum
{
    LORD_DATE,      // [3-1- 1]伊達輝宗
    LORD_UESUGI,    // [3-1- 2]上杉謙信
    LORD_TAKEDA,    // [3-1- 3]武田信玄
    LORD_HOJO,      // [3-1- 4]北条氏政
    LORD_TOKUGAWA,  // [3-1- 5]徳川家康
    LORD_ODA,       // [3-1- 6]織田信長
    LORD_ASHIKAGA,  // [3-1- 7]足利義昭
    LORD_MORI,      // [3-1- 8]毛利元就
    LORD_CHOSOKABE, // [3-1- 9]長宗我部元親
    LORD_SIMAZU,    // [3-1-10]島津義久
    LORD_MAX        // [3-1-11]種類の数
};

// [3-2]城の種類を定義する
enum
{
    CASTLE_YONEZAWA,        // [3-2- 1]米沢城
    CASTLE_KASUGAYAMA,      // [3-2- 2]春日山城
    CASTLE_TSUTSUJIGASAKI,  // [3-2- 3]躑躅ヶ崎館
    CASTLE_ODAWARA,         // [3-2- 4]小田原城
    CASTLE_OKAZAKI,         // [3-2- 5]岡崎城
    CASTLE_GIFU,            // [3-2- 6]岐阜城
    CASTLE_NIJO,            // [3-2- 7]二条城
    CASTLE_YOSHIDAKORIYAMA, // [3-2- 8]吉田郡山城
    CASTLE_OKO,             // [3-2- 9]岡豊城
    CASTLE_UCHI,            // [3-2-10]内城
    CASTLE_MAX              // [3-2-11]種類の数
};

// [4]構造体を宣言する場所

// [4-1]大名の構造体を宣言する
typedef struct {
    char familyName[16];    // [4-1-1]姓
    char firstName[16];     // [4-1-2]名
} LORD;

// [4-2]城の構造体を宣言する
typedef struct {
    const char*         name;               // [4-2-1]名前
    int                 owner;              // [4-2-2]城主
    int                 troopCount;         // [4-2-3]兵数
    std::vector<int>    connectedCastles;   // [4-2-4]接続された城のリスト
} CASTLE;

// [5]変数を宣言する場所

// [5-1]大名の配列を宣言する
LORD lords[LORD_MAX] =
{
    {"伊達",    "輝宗"},    // [5-1- 1]LORD_DATE        伊達輝宗
    {"上杉",    "謙信"},    // [5-1- 2]LORD_UESUGI      上杉謙信
    {"武田",    "信玄"},    // [5-1- 3]LORD_TAKEDA      武田信玄
    {"北条",    "氏政"},    // [5-1- 4]LORD_HOJO        北条氏政
    {"徳川",    "家康"},    // [5-1- 5]LORD_TOKUGAWA    徳川家康
    {"織田",    "信長"},    // [5-1- 6]LORD_ODA         織田信長
    {"足利",    "義昭"},    // [5-1- 7]LORD_ASHIKAGA    足利義昭
    {"毛利",    "元就"},    // [5-1- 8]LORD_MORI        毛利元就
    {"長宗我部","元親"},    // [5-1- 9]LORD_CHOSOKABE   長宗我部元親
    {"島津",    "義久"}     // [5-1-10]LORD_SIMAZU      島津義久
};

// [5-2]城の配列を宣言する
CASTLE castles[CASTLE_MAX] =
{
    // [5-2-1]CASTLE_YONEZAWA   米沢城
    {
        "米沢城",   // const char* name         名前
        LORD_DATE,  // int owner                城主
        TROOP_BASE, // int troopCount           兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_KASUGAYAMA,  // 春日山城
            CASTLE_ODAWARA      // 小田原城
        }
    },

    // [5-2-2]CASTLE_KASUGAYAMA 春日山城
    {
        "春日山城",     // const char* name     名前
        LORD_UESUGI,    // int owner            城主
        TROOP_BASE,     // int troopCount       兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_YONEZAWA,        // 米沢城
            CASTLE_TSUTSUJIGASAKI,  // 躑躅ヶ崎館
            CASTLE_GIFU             // 岐阜城
        }
    },

    // [5-2-3]CASTLE_TSUTSUJIGASAKI 躑躅ヶ崎館
    {
        "躑躅ヶ崎館",   // const char* name     名前
        LORD_TAKEDA,    // int owner            城主
        TROOP_BASE,     // int troopCount       兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_KASUGAYAMA,  // 春日山城
            CASTLE_ODAWARA,     // 小田原城
            CASTLE_OKAZAKI      // 岡崎城
        }
    },

    // [5-2-4]CASTLE_ODAWARA    小田原城
    {
        "小田原城", // const char* name         名前
        LORD_HOJO,  // int owner                城主
        TROOP_BASE, // int troopCount           兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_YONEZAWA,        // 米沢城
            CASTLE_TSUTSUJIGASAKI,  // 躑躅ヶ崎館
            CASTLE_OKAZAKI          // 岡崎城
        }
    },

    // [5-2-5]CASTLE_OKAZAKI    岡崎城
    {
        "岡崎城",       // const char* name     名前
        LORD_TOKUGAWA,  // int owner            城主
        TROOP_BASE,     // int troopCount       兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_TSUTSUJIGASAKI,  // 躑躅ヶ崎館
            CASTLE_ODAWARA,         // 小田原城
            CASTLE_GIFU             // 岐阜城
        }
    },

    // [5-2-6]CASTLE_GIFU   岐阜城
    {
        "岐阜城",   // const char* name         名前
        LORD_ODA,   // int owner                城主
        TROOP_BASE, // int troopCount           兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_KASUGAYAMA,  // 春日山城
            CASTLE_OKAZAKI,     // 岡崎城
            CASTLE_NIJO         // 二条城
        }
    },

    // [5-2-7]CASTLE_NIJO   二条城
    {
        "二条城",       // const char* name     名前
        LORD_ASHIKAGA,  // int owner            城主
        TROOP_BASE,     // int troopCount       兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_GIFU,            // 岐阜城
            CASTLE_YOSHIDAKORIYAMA, // 吉田郡山城
            CASTLE_OKO              // 岡豊城
        }
    },

    // [5-2-8]CASTLE_YOSHIDAKORIYAMA    吉田郡山城
    {
        "吉田郡山城",   // const char* name     名前
        LORD_MORI,      // int owner            城主
        TROOP_BASE,     // int troopCount       兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_NIJO,    // 二条城
            CASTLE_OKO,     // 岡豊城
            CASTLE_UCHI     // 内城
        }
    },

    // [5-2-9]CASTLE_OKO    岡豊城
    {
        "岡豊城",       // const char* name     名前
        LORD_CHOSOKABE, // int owner            城主
        TROOP_BASE,     // int troopCount       兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_NIJO,            // 二条城
            CASTLE_YOSHIDAKORIYAMA, // 吉田郡山城
            CASTLE_UCHI             // 内城
        }
    },

    // [5-2-10]CASTLE_UCHI  内城
    {
        "内城",         // const char* name     名前
        LORD_SIMAZU,    // int owner            城主
        TROOP_BASE,     // int troopCount       兵数

        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_YOSHIDAKORIYAMA, // 吉田郡山城
            CASTLE_OKO              // 岡豊城
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
        "1570ねん　〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜　　　　　〜¥n"      // 01
        "　　　　　〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜　0米沢5　〜¥n"      // 02
        "〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜1春日5　伊達　〜〜¥n"      // 03
        "〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜　〜〜上杉　　　　　〜〜¥n"      // 04
        "〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜　〜　　　　　　　　〜〜¥n"      // 05
        "〜〜〜〜〜〜〜〜〜〜〜〜〜〜　　　　　2躑躅5　　　〜〜¥n"      // 06
        "〜〜〜〜〜〜〜〜〜〜〜〜〜　　　　　　武田　　　〜〜〜¥n"      // 07
        "〜〜〜〜〜〜　　　　　　　5岐阜5　　　　　　　　〜〜〜¥n"      // 08
        "〜〜〜〜　7吉田5　6二条5　織田　4岡崎5　3小田5　〜〜〜¥n"      // 09
        "〜〜〜　　毛利　　足利　　　　　徳川　　北条〜〜〜〜〜¥n"      // 10
        "〜〜　〜〜〜〜〜〜〜　　　〜〜〜〜〜〜〜〜〜〜〜〜〜〜¥n"      // 11
        "〜　　　〜　8岡豊5〜〜　〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜¥n"      // 12
        "〜　　　〜〜長宗〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜¥n"      // 13
        "〜9内城5〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜¥n"      // 14
        "〜島津〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜¥n"      // 15
        "〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜¥n");    // 16
*/
    // [6-2-2]地図の1行目を描画する
    printf("%dねん　〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜　　　　　〜¥n",
        year);  // 年

    // [6-2-3]地図の2行目を描画する
    printf("　　　　　〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜　%d%.4s%d　〜¥n",

        // 米沢城の城番号
        CASTLE_YONEZAWA,

        // 米沢城の名前
        castles[CASTLE_YONEZAWA].name,

        // 米沢城の兵数
        castles[CASTLE_YONEZAWA].troopCount);

    // [6-2-4]地図の3行目を描画する
    printf("〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜%d%.4s%d　%.4s　〜〜¥n",

        // 春日山城の城番号
        CASTLE_KASUGAYAMA,

        // 春日山城の名前
        castles[CASTLE_KASUGAYAMA].name,

        // 春日山城の兵数
        castles[CASTLE_KASUGAYAMA].troopCount,

        // 米沢城の名の姓
        lords[castles[CASTLE_YONEZAWA].owner].familyName);

    // [6-2-5]地図の4行目を描画する
    printf("〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜　〜〜%.4s　　　　　〜〜¥n",

        // 春日山城の名の姓
        lords[castles[CASTLE_KASUGAYAMA].owner].familyName);

    // [6-2-6]地図の5行目を描画する
    printf("〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜　〜　　　　　　　　〜〜¥n");

    // [6-2-7]地図の6行目を描画する
    printf("〜〜〜〜〜〜〜〜〜〜〜〜〜〜　　　　　%d%.4s%d　　　〜〜¥n",

        // 躑躅ヶ崎館の城番号
        CASTLE_TSUTSUJIGASAKI,

        // 躑躅ヶ崎館の名前
        castles[CASTLE_TSUTSUJIGASAKI].name,

        // 躑躅ヶ崎館の兵数
        castles[CASTLE_TSUTSUJIGASAKI].troopCount);

    // [6-2-8]地図の7行目を描画する
    printf("〜〜〜〜〜〜〜〜〜〜〜〜〜　　　　　　%.4s　　　〜〜〜¥n",

        // 躑躅ヶ崎館の城主の姓**
        lords[castles[CASTLE_TSUTSUJIGASAKI].owner].familyName);

    // [6-2-9]地図の8行目を描画する
    printf("〜〜〜〜〜〜　　　　　　　%d%.4s%d　　　　　　　　〜〜〜¥n",

        // 岐阜城の城番号
        CASTLE_GIFU,

        // 岐阜城の名前
        castles[CASTLE_GIFU].name,

        // 岐阜城の兵数
        castles[CASTLE_GIFU].troopCount);

    // [6-2-10]地図の9行目を描画する
    printf("〜〜〜〜　%d%.4s%d　%d%.4s%d　%.4s　　　　　%d%.4s%d　〜〜〜¥n",

        // 吉田郡山城の城番号
        CASTLE_YOSHIDAKORIYAMA,

        // 吉田郡山城の名前
        castles[CASTLE_YOSHIDAKORIYAMA].name,

        // 吉田郡山城の兵数
        castles[CASTLE_YOSHIDAKORIYAMA].troopCount,

        // 二条城の城番号
        CASTLE_NIJO,

        // 二条城の名前
        castles[CASTLE_NIJO].name,

        // 二条城の兵数
        castles[CASTLE_NIJO].troopCount,

        // 岐阜城の城主の姓
        lords[castles[CASTLE_GIFU].owner].familyName,

        // 小田原城の城番号
        CASTLE_ODAWARA,

        // 小田原城の名前
        castles[CASTLE_ODAWARA].name,

        // 小田原城の兵数
        castles[CASTLE_ODAWARA].troopCount);

    // [6-2-11]地図の10行目を描画する
    printf("〜〜〜　　%.4s　　%.4s　〜　　　%d%.4s%d　%.4s〜〜〜〜〜¥n",

        // 吉田郡山城の城主の姓
        lords[castles[CASTLE_YOSHIDAKORIYAMA].owner].familyName,

        // 二条城の城主の姓
        lords[castles[CASTLE_NIJO].owner].familyName,

        // 岡崎城の城番号
        CASTLE_OKAZAKI,

        // 岡崎城の名前
        castles[CASTLE_OKAZAKI].name,

        // 岡崎城の兵数
        castles[CASTLE_OKAZAKI].troopCount,

        // 小田原城の城主の姓
        lords[castles[CASTLE_ODAWARA].owner].familyName);

    // [6-2-12]地図の11行目を描画する
    printf("〜〜　〜〜〜〜〜〜〜　　　　〜〜%.4s〜　〜　〜〜〜〜〜¥n",

        // 岡崎城の城主の姓
        lords[castles[CASTLE_OKAZAKI].owner].familyName);

    // [6-2-13]地図の12行目を描画する
    printf("〜　　　〜　%d%.4s%d　〜　　　　〜〜〜〜〜〜〜〜〜〜〜〜¥n",

        // 岡豊城の城番号
        CASTLE_OKO,

        // 岡豊城の名前
        castles[CASTLE_OKO].name,

        // 岡豊城の兵数
        castles[CASTLE_OKO].troopCount);

    // [6-2-14]地図の13行目を描画する**
    printf("〜　　　〜　%.4s　〜〜　　〜〜〜〜〜〜〜〜〜〜〜〜〜〜¥n",

        // 岡豊城の城主の姓**
        lords[castles[CASTLE_OKO].owner].familyName);

    // [6-2-15]地図の14行目を描画する
    printf("〜%d%.4s%d〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜¥n",

        // 内城の城番号
        CASTLE_UCHI,

        // 内城の名前
        castles[CASTLE_UCHI].name,

        // 内城の兵数
        castles[CASTLE_UCHI].troopCount);

    // [6-2-16]地図の15行目を描画する
    printf("〜%.4s〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜¥n",

        // 内城の城主の姓
        lords[castles[CASTLE_UCHI].owner].familyName);

    // [6-2-17]地図の16行目を描画する
    printf("〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜¥n");

    // [6-2-18]1行空けておく
    printf("¥n");
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
    printf("おやかたさま、われらがしろは　このちずの¥n"
        "どこに　ありまするか？！（0〜%d）¥n",
        CASTLE_MAX - 1);    // 城番号の最大値

    printf("¥n");// [6-3-8]1行空ける

    // [6-3-9]選択された城を保持する変数を宣言する
    int selectedCastle;

    // [6-3-10]範囲内の城番号が入力されるまで反復する
    do {
        selectedCastle = _getch() - '0';// [6-3-11]城番号を入力する
    } while ((selectedCastle < 0) || (selectedCastle >= CASTLE_MAX));

    // [6-3-12]選択した城の城主をプレイヤーの大名とする
    playerLord = castles[selectedCastle].owner;

    // [6-3-13]決定した大名を通知するメッセージを表示する
    printf("%sさま、%sから　てんかとういつを¥nめざしましょうぞ！¥n",
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
    printf("〜%sの　たたかい〜¥n", castles[_castle].name);

    printf("¥n");// [6-4-3]1行空ける

    // [6-4-4]攻め込まれた大名を宣言する
    int defensiveLord = castles[_castle].owner;

    // [6-4-5]無限ループする
    while (1)
    {
        // [6-4-6]合戦の経過を表示する
        printf("%sぐん（%4dにん）　Ｘ　%sぐん（%4dにん）¥n",

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

        // [6-4-10]0〜2の乱数が、0かどうかを判定する
        if (rand() % 3 == 0)
        {
            castles[_castle].troopCount--;// [6-4-11]守備側の兵を減らす
        }

        // [6-4-12]0〜2の乱数が、1か2なら
        else
        {
            _offensiveTroopCount--;// [6-4-13]攻撃側の兵を減らす
        }
    }

    printf("¥n");// [6-4-14]1行空ける

    // [6-4-15]守備側の兵が全滅したかどうかを判定する
    if (castles[_castle].troopCount <= 0)
    {
        // [6-4-16]落城したメッセージを表示する
        printf("%s　らくじょう！！¥n", castles[_castle].name);

        printf("¥n");// [6-4-17]1行空ける

        // [6-4-18]攻撃側の大名の城にする
        castles[_castle].owner = _offensiveLord;

        // [6-4-19]攻撃側の兵を入城させる
        castles[_castle].troopCount = _offensiveTroopCount;

        // [6-4-20]城主が攻め込んだ大名に変わったメッセージを表示する
        printf("%sは　%sけの　ものとなります¥n",
            castles[_castle].name,
            lords[_offensiveLord].familyName);

        printf("¥n");// [6-4-21]1行空ける

        // [6-4-22]守備側の大名が、城をすべて失ったかどうかを判定する
        if (GetCastleCount(defensiveLord) <= 0)
        {
            char str[128];  // [6-4-23]追加する文字列を宣言する

            // [6-4-24]追加する文字列を作成する
            sprintf_s(str, "%dねん　%s%sが　%sで　%s%sを　ほろぼす¥n",
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
        printf("%sぐん　かいめつ！！¥n"
            "¥n"
            "%sぐんが　%sを　まもりきりました！¥n",
            lords[_offensiveLord].familyName,
            lords[defensiveLord].familyName,
            castles[_castle].name);
    }
}

// [6-5]プログラムの実行開始点を宣言する
int main()
{
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
                printf("%.4s", castles[turnOrder[j]].name);
            }

            // [6-5-16]改行して1行空ける
            printf("¥n¥n");

            // [6-5-17]現在のターンの城の番号を宣言する
            int currentCastle = turnOrder[i];

            // [6-5-18]メッセージを表示する
            printf("%sけの　%sの　ひょうじょうちゅう…¥n",
                lords[castles[currentCastle].owner].familyName, // 城主の姓
                castles[currentCastle].name);                   // 城の名前

            printf("¥n");// [6-5-19]1行空ける

            // [6-5-20]現在の城の城主がプレイヤーかどうかを判定する
            if (castles[currentCastle].owner == playerLord)
            {
                // [6-5-21]進軍先の城の指定を促すメッセージを表示する
                printf("%sさま、どこに　しんぐん　しますか？¥n",
                    lords[castles[currentCastle].owner].firstName);

                printf("¥n");// [6-5-22]1行空ける

                // [6-5-23]すべての接続された城を反復する
                for (int j = 0; j < (int)castles[currentCastle].connectedCastles.size(); j++)
                {
                    // [6-5-24]接続された城の番号と名前を表示する
                    printf("%d %s¥n",
                        castles[currentCastle].connectedCastles[j],
                        castles[castles[currentCastle].connectedCastles[j]].name);
                }

                printf("¥n");// [6-5-25]1行空ける

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
                    printf("しんぐんを　とりやめました¥n");

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
                printf("%sに　なんぜんにん　しんぐん　しますか？（0〜%d）¥n",
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
                printf("¥n");

                // [6-5-48]入力された進軍兵数を通知する
                printf("%sに　%dにん%s",
                    castles[targetCastle].name, // 進軍先の城の名前
                    troopCount * TROOP_UNIT,	// 進軍兵数

                    // 進軍先の城の城主がプレイヤーかどうかを判定する
                    (castles[targetCastle].owner == playerLord)
                    ? "　いどう　しました"          // プレイヤーの城なら
                    : "で　しゅつじんじゃ〜！！");  // 敵の城なら

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
                            return castles[_castle0].troopCount< castles[_castle1].troopCount;
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
                        printf("%sの　%s%sが　%sに　せめこみました！¥n",
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
                        printf("%sから　%sに　%dにん　いどうしました¥n",
                            castles[currentCastle].name,
                            castles[targetCastle].name,
                            sendTroopCount* TROOP_UNIT);
                    }
                }
            }

            _getch();// [6-5-89]キーボード入力を待つ

            // [6-5-90]プレイヤーの城がないかどうかを判定する
            if (GetCastleCount(playerLord) <= 0)
            {
                DrawScreen();// [6-5-91]画面を描画する

                printf("%s", chronology);// [6-5-92]年表を表示する

                printf("¥n");// [6-5-93]1行空ける

                // [6-5-94]ゲームオーバーのメッセージを表示する
                printf("ＧＡＭＥ　ＯＶＥＲ¥n");

                _getch();// [6-5-95]キーボード入力を待つ

                goto start;// [6-5-96]ゲームの開始ラベルにジャンプする
            }

            // [6-5-97]プレイヤーすべての城を所有しているかどうかを判定する
            else if (GetCastleCount(playerLord) >= CASTLE_MAX)
            {
                DrawScreen();// [6-5-98]画面を描画する

                printf("%s", chronology);// [6-5-99]年表を表示する

                // [6-5-100]エンディングのメッセージを表示する
                printf("%dねん　%s%sが　せいいたいしょうぐんに　にんぜられる¥n"
                    "%dねん　%s%sが　%sばくふを　ひらく¥n"
                    "¥n"
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

        // [6-5-109]「本能寺の変」イベントが起きる条件を満たしているかどうかを判定する
        if (
            // 1582年である
            (year == 1582)
            
            // かつ織田家が二条城を所有している
            && (castles[CASTLE_NIJO].owner == LORD_ODA))
        {
            // [6-5-110]織田家大名の姓を「羽柴」に書き換える
            strcpy_s(lords[LORD_ODA].familyName, "羽柴");

            // [6-5-111]織田家大名の名を「秀吉」に書き換える
            strcpy_s(lords[LORD_ODA].firstName, "秀吉");

            DrawScreen();// [6-5-112]画面を再描画する

            // [6-5-113]「本能寺の変」イベントのメッセージを表示する
            printf(
                "明智光秀「てきは　本能寺に　あり！¥n"
                "¥n"
                "明智光秀が　本能寺の　織田信長を　しゅうげきした！¥n"
                "¥n"
                "織田信長「ぜひに　およばず…¥n"
                "¥n"
                "織田信長は　本能寺に　ひをはなち　じがいした！¥n"
                "¥n"
                "ごじつ、羽柴秀吉が　山崎のたたかいで　明智光秀を　たおし、¥n"
                "織田けの　こうけいの　ちいを　さんだつした！¥n");

            _getch();// [6-5-114]キーボード入力を待つ
        }
    }
}