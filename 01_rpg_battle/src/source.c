/* battle.c */
/* 2026-04-23 */
/* console setting
 * font size = 72
 * font = misaki
 * widh 32
 * hight 10
 * write in alacritty-game.toml
 */

/* [1] Headers */
#include "console_manager.h"
#include "input_handler.h"
#include <locale.h>  // for ncurses
#include <ncurses.h> // printwを使うために必要
// #include <stdio.h> // [1-1] 標準入出力ヘッダーをインクルードする
// ncursesではprintwを使うので不要
#include <stdlib.h> // [1-2] 標準ライブラリヘッダをインクルードする（srandのため）::
#include <string.h> // [1-3] 文字列操作ヘッダーをインクルードする
#include <time.h> // [1-4] 時間管理ヘッダーをインクルードする
// #include <stdio.h>

/* [2] Constants */

/* [3] enums */
// [3-1] モンスターの種類を定義する
enum {
  MONSTER_PLAYER, // [3-1-1] player
  MONSTER_SLIME,  // [3-1-2] slime
  MONSTER_BOSS,   // [3-1-3] 魔王
  MONSTER_MAX     // [3-1-4] モンスターの種類の数
};

// [3-2] キャラクターの種類を定義する　kinds of characters
enum {
  CHARACTER_PLAYER,  // [3-2-1] プレイヤー
  CHARACTER_MONSTER, // [3-2-2] モンスター
  CHARACTER_MAX      //[3-2-3] キャラクターの種類の数
};

// [3-3] コマンドの種類を定義する
enum {
  COMMAND_FIGHT, // [3-3-1] 戦う　fight
  COMMAND_SPELL, // [3-3-2] 呪文　spell
  COMMAND_RUN,   // [3-3-3] 逃げる　runaway
  COMMAND_MAX    // [3-3-4] コマンドの種類の数　number of commands
};

/* [4] structs */
// [4-1]struct of characters
typedef struct {
  int hp;               // [4-1-1] HP
  int maxHP;            // [4-1-2] Max HP
  int mp;               // [4-1-3] MP
  int maxMP;            // [4-1-4] Max MP
  int attack;           // [4-1-5] 攻撃力
  char name[4 * 3 + 1]; // [4-1-6] name 4文字 x 全角3バイト(utf8) + '\0'
  char aa[256];         // [4-1-7] ASCII art
  int command;          // [4-1-8] command
  int target;           // [4-1-9] 攻撃対象
} CHARACTER;

/* [5] variables */
// [5-1] モンスターのステータスの配列を宣言する　monster's status
CHARACTER monsters[MONSTER_MAX] = {
    // [5-1-1] MONSTER_PLAYER プレイヤー
    {
        100,        // [5-1-2] int hp HP
        100,        // [5-1-3] int maxHP  MaxHP
        15,         // [5-1-4] int mp MP
        15,         // [5-1-5] int Max HP
        30,         // [5-1-6] int attack 攻撃力
        "ゆうしゃ", // [5-1-7] char name name [4 * 3 + 1] name
        "",         // doesn't have aa but declare as ""
        0,          // command initialize as 0
        0,          // target initialize as 0
    },

    // [5-1-8]MONSTER_SLIME
    {
        3,          // [5-1-9] int hp
        3,          // [5-1-10] int maxHP
        0,          // [5-1-11] int mp MP
        0,          // [5-1-12] int maxHP
        2,          // [5-1-13] int attach 攻撃力
        "スライム", // [5-1-14] char name [4 * 3 +1] name
        // [5-1-15] char aa[256] アスキーアート
        "／・Д・＼\n"
        "～～～～～",
        0, // command initialize as 0
        0, // target initialize as 0
    },

    // [5-1-16]MONSTER_BOSS
    {
        255,      // [5-1-17] int hp
        255,      // [5-1-18] int maxHP
        0,        // [5-1-19] int mp MP
        0,        // [5-1-20] int maxHP
        50,       // [5-1-21] int attach 攻撃力
        "まおう", // [5-1-21] char name [4 * 3 +1] name
        // [5-1-23] char aa[256] アスキーアート
        "　Ａ＠Ａ\n"
        "ψ（▼皿▼）ψ",
        0, // command initialize as 0
        0, // target initialize as 0
    },
};

// [5-2] キャラクターの配列を宣言する　array of characters
CHARACTER characters[CHARACTER_MAX];

// [5-3] コマンドの名前を宣言する　declare command names
char commandNames[COMMAND_MAX][4 * 3 + 1] = {
    "たたかう", // [5-3-1]COMMAND_FIGHT
    "じゅもん", // [5-3-2]COMMAND_SPELL
    "にげる"    // [5-3-3]COMMAND_RUN
};

/* [6a] functions prototypes */
void Battle(int _monster);   // [6-4] battle scene
void Init(void);             // initialize the game
void DrawBattleScreen(void); // draw battle sceen
void SelectCommand();        // [6-3] select commands

/* [6-6] main */
int main(void) {
  // [6-6-1] 乱数をシャッフルする
  srand((unsigned int)time(NULL));

  /* to use Japanese mult byte for ncurses */
  setlocale(LC_ALL, "");
  /* --- 最初に一度だけ初期化 ncurses--- */
  init_console();
  // [6-6-2] ゲームを初期化する関数を呼び出す initialize game data (must be
  // before drawing)
  Init();

  //  printw("Console Initialized.\n");
  //  printw("Press any key (Press 'q' to quit)...\n");
  //  refresh();

  //   int ch;
  //   while (1) {
  //     /* input_handlerから _getch() を呼び出す */
  //     ch = _getch();
  //
  //     if (ch == 'q')
  //       break;
  //
  //     clear();
  //     printw("Key: %c (Code: %d)\n", ch, ch);
  //     printw("Keep pressing or press 'q' to quit.");
  //
  //     refresh();
  //   }

  /* ここにプログラムを書いてみる */
  // [6-6-3] 戦闘シーンの関数を呼び出す call battle
  Battle(MONSTER_BOSS);

  /* ここまでプログラム */

  /* --- 最後に必ず終了処理 --- */
  close_console();

  printw("Program ended safely.\n");
  return 0;
}

/* [6] function implement */

// [6-1] ゲームを初期化する関数を宣言する
void Init(void) {
  // [6-1-1] プレイヤーのステータスを初期化する
  characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

// [6-2] 戦闘シーンの画面を描画する関数を宣言する
void DrawBattleScreen(void) {
  // [6-2-1] 画面をクリアする　clear screen
  clear(); // ncursesの画面消去

  // [6-2-2] display player name
  printw("%s\n",
         characters[CHARACTER_PLAYER]
             .name); // ncurses needs printw insted of printf

  // [6-2-3] プレイヤーのステータスを表示する
  printw("ＨＰ : %d / %d  ＭＰ : %d / %d\n", characters[CHARACTER_PLAYER].hp,
         characters[CHARACTER_PLAYER].maxHP, characters[CHARACTER_PLAYER].mp,
         characters[CHARACTER_PLAYER].maxHP);

  // [6-2-4] 一行開ける
  printw("\n");

  //[6-2-5] モンスターのアスキーアートを描画する　draw ascii art of monster
  printw("%s", characters[CHARACTER_MONSTER].aa);

  //[6-2-6] モンスターのHPを表示する　display monster's hp
  printw("(ＨＰ：%d／%d)\n", characters[CHARACTER_MONSTER].hp,
         characters[CHARACTER_MONSTER].maxHP);

  //[6-2-7] 一行開ける　one blank row
  printw("\n");

  refresh(); // printw and refersh() should be one set.
}

// [6-3] コマンドを選択する関数を宣言する
void SelectCommand() {
  // [6-3-2] コマンドが決定されるまでループする　roop until command is
  // determined
  while (1) {
    // [6-3-3] call DrawBattleScreen();
    DrawBattleScreen();

    // [6-3-4] コマンドの一覧を表示する　display list of commands
    for (int i = 0; i < COMMAND_MAX; i++) {
      // [6-3-5] 選択中のコマンドなら　if chosen command
      if (i == characters[CHARACTER_PLAYER].command) {
        // [6-3-6] カーソルを描画する　draw cursor
        printw("＞");
        // [6-3-7] 選択中のコマンドでなければ　if not chosen command
      } else {
        // [6-3-8] 全角スペースを仰臥する　draw wide space
        printw("　");
      }

      // [6-3-9] display command names
      printw("%s\n",
             commandNames[i]); // ncursesではprintfではなくprintwを使う
    }
    refresh(); // printwはrefresh()が呼ばれるまで画面を更新しないのでprintwとセットで使う。
               // printwを複数実行した後で一気に画面表示を更新することで速度を上げるため
               // for
               // 文を抜けた後に一回だけつかう。for文の中で何回も呼ぶと遅くなる
               // どこでrefreshするかよく考えること。

    // [6-3-10] 入力されたキーによって分岐する　selection by input key
    switch (_getch()) {
    case 'w': // [6-3-11] if w key is hit
      // [6-3-12] change to up command
      characters[CHARACTER_PLAYER].command--;
      break;

    case 's': // [6-3-13] if s key is hit
              // [6-13-14] change to down command
      characters[CHARACTER_PLAYER].command++;
      break;

    default:  // [6-3-15] if other key is hit
      return; // [6-3-16] exit the function
    }
    // [6-3-17] カーソルキーを上下にループさせる　loop cursor up and down
    characters[CHARACTER_PLAYER].command =
        (COMMAND_MAX + characters[CHARACTER_PLAYER].command) % COMMAND_MAX;
  }
}

// [6-4] 戦闘シーンの関数を宣言する
void Battle(int _monster) {
  // [6-4-1] モンスターのステータスを初期化する　initialize monster's status
  characters[CHARACTER_MONSTER] = monsters[_monster];

  //[6-4-2] プレイヤーの攻撃対象をモンスターに設定する　set the target of
  // playert to a monster
  characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;

  //[6-4-3] モンスターの攻撃対象をプレイヤーに設定する　set the monnsters'
  // target to the player
  characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

  // [6-4-4] call Battle Screen
  DrawBattleScreen();

  // [6-4-5] 戦闘シーンの最初のメッセージを表示する　display messages for battel
  // scene
  printw("%sが　あらわれた！\n", characters[CHARACTER_MONSTER].name);

  //[6-4-6] wait for keybord input
  _getch();

  //[6-4-7] 戦闘が終了するまでループする　loop until battle ends
  while (1) {
    //[6-4-8] コマンドを選択する関数を呼び出す　select command
    SelectCommand();

    //[6-4-9] 各キャラクターを反復する　repeat character
    for (int i = 0; i < CHARACTER_MAX; i++) {
      // [6-4-10] 戦闘シーンの画面を描画する関数を呼び出す　refresh battle scene
      DrawBattleScreen();

      // [6-4-11] 選択されたコマンドで分岐する　selection by chosen commmand
      switch (characters[i].command) {
      case COMMAND_FIGHT: // [6-4-12] fight
        // [6-4-13] display message to fight
        printw("%sの　こうげき！\n", characters[i].name);

        // [6-4-14] wait for keyboard input
        _getch();

        // [6-4-15] 敵に与えるダメージを計算する
        int damage = 1 + rand() % characters[i].attack;

        // [6-4-16] 敵にダメージを与える
        characters[characters[i].target].hp -= damage;

        // [6-4-17] 敵のHPが負の値になったかどうかを判定する
        if (characters[characters[i].target].hp < 0) {
          // [6-4-18] 敵のHPを0にする
          characters[characters[i].target].hp = 0;
        }

        // [6-4-19] 戦闘シーンの画面を再描画する関数を呼び出す
        DrawBattleScreen();

        // [6-4-20] 敵にダメージを与えたメッセージを表示する
        printw("%sに　%dの　ダメージ！\n",
               characters[characters[i].target].name, damage);

        // [6-4-21] キーボード入力を待つ
        _getch();

        break;

      case COMMAND_SPELL: // [6-4-22] 呪文　spell
        break;
      case COMMAND_RUN: // [6-4-35] 逃げる　runaway
        break;
      }

      // [6-4-39] 攻撃対象を倒したかどうかを判定する
      if (characters[characters[i].target].hp <= 0) {
        // [6-4-40] 攻撃対象によって処理を分岐させる
        switch (characters[i].target) {
        // [6-4-41] プレイヤーなら
        case CHARACTER_PLAYER:
          // [6-4-42] プレイヤーが死んだメッセージを表示する
          printw("あなたは　しにました");
          break;

        // [6-4-43] モンスターなら
        case CHARACTER_MONSTER:
          // [6-4-44]
          // モンスターのアスキーアートを何も表示しないように書き換える
          strcpy(characters[characters[i].target].aa, "\n");

          // [6-4-45] 戦闘シーンの画面を再描画する関数を呼び出す
          DrawBattleScreen();

          // [6-4-46] モンスターを倒したメッセージを表示する
          printw("%s をたおした！\n", characters[characters[i].target].name);
          break;
        }
        // [6-4-47] キーボード入力を待つ
        _getch();

        // [6-4-48] 戦闘シーンの関数を抜ける
        return;
      }
    }
  }

} // battle scene
