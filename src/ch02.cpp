// 第2章：コマンド

#include <iostream>
#include "ch02.h"

// 2.1 入力の設定
void InputHandler1::handleInput()
{
  if (isPressed(ButtonType::BUTTON_X))
  {
    jump();
  }
  else if (isPressed(ButtonType::BUTTON_Y))
  {
    fire();
  }
  else if (isPressed(ButtonType::BUTTON_A))
  {
    swap();
  }
  else if (isPressed(ButtonType::BUTTON_B))
  {
    throwGrenade();
  }
};

bool InputHandler2::isPressed(ButtonType button) {
  // 実引数に渡されたリテラルを元に、そのボタンが押されたかどうかを返す
};

// Commandパターンでの実装
void InputHandler2::handleInput()
{
  if (isPressed(ButtonType::BUTTON_X))
  {
    buttonX_->execute();
  }
  else if (isPressed(ButtonType::BUTTON_Y))
  {
    buttonY_->execute();
  }
  else if (isPressed(ButtonType::BUTTON_A))
  {
    buttonA_->execute();
  }
  else if (isPressed(ButtonType::BUTTON_B))
  {
    buttonB_->execute();
  }
};

// Command* InputHandler::handleInput()
//  {
//    if(isPressed(ButtonType::BUTTON_X)) {
//      return buttonX_;
//    }
//    else if(isPressed(ButtonType::BUTTON_Y)) {
//      return buttonY_;
//    }
//    else if(isPressed(ButtonType::BUTTON_A)) {
//      return buttonA_;
//    }
//    else if(isPressed(ButtonType::BUTTON_B)) {
//      return buttonB_;
//    }
//    return nullptr;
//  };

// コマンドを受け取って実行するコード
void execute()
{
  ActorOfCh02 actor = ActorOfCh02();
  InputHandler inputhandler = InputHandler();
  Command *command = inputhandler.handleInput(); //ハンドラでコマンドを取得
  if (command)
  {
    command->execute(actor); //実際のコマンドの実行は遅れる
  }
};
