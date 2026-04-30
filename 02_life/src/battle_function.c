#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "battle_function.h"
#include "data.h"
#include "types.h"

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
  // [6-3-1] プレイヤーのコマンドを初期化する
  characters[CHARACTER_PLAYER].command = COMMAND_FIGHT;

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
    switch (getch()) {
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
  getch();

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
        getch();

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
        getch();

        break;

      case COMMAND_SPELL: // [6-4-22] 呪文　spell
        // [6-4-23] MPが足りるかどうかを判定する
        if (characters[i].mp < SPELL_COST) {
          // [6-4-24] MPが足りないメッセージを表示する
          printw("ＭＰが　たりない！\n");

          // [6-4-25] キーボード入力を待つ
          getch();

          // [6-4-26] 呪文を唱える処理を抜ける
          break;
        }

        // [6-4-27] MPを消費させる
        characters[i].mp -= SPELL_COST;

        // [6-4-28] 画面を再描画する
        DrawBattleScreen();

        // [6-4-29] 呪文を唱えたメッセージを表示する
        printw("%sは　ヒールを　となえた！\n", characters[i].name);

        // [6-4-30] キーボード入力を待つ
        getch();

        //[6-4-31] HPを回復させる
        characters[i].hp = characters[i].maxHP;

        //[6-4-32] 戦闘シーンの画面を再描画する
        DrawBattleScreen();

        //[6-4-33] HPが回復したメッセージを表示する
        printw("%sのきずが　かいふくした！\n", characters[i].name);

        //[6-4-34] キーボード入力を待つ
        getch();

        break;

      case COMMAND_RUN: // [6-4-35] 逃げる　runaway
        // [6-4-36] 逃げ出したメッセージを表示する
        printw("%s　は　にげだした！\n", characters[i].name);
        // [6-4-37] キーボード入力を待つ
        getch();

        //[6-4-38] 戦闘処理を抜ける
        return;
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
        getch();

        // [6-4-48] 戦闘シーンの関数を抜ける
        return;
      }
    }
  }

} // battle scene
