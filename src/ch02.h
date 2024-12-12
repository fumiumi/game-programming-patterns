// 第2章：コマンド

#pragma once

#include <iostream>
#include <string>
#include "lib/Actor.h"

// ゲームの入力操作を処理するクラス

// 2.1 入力の設定
enum class ButtonType {
  BUTTON_X,
  BUTTON_Y,
  BUTTON_A,
  BUTTON_B
};

class InputHandler1 {
public:
  static bool isPressed(ButtonType button);
  void handleInput();

private:
  void jump();
  void fire();
  void swap();
  void throwGrenade();
};

// Commandパターン
//入力に対するコマンドを表すクラス
class Command1
{
public:
  virtual ~Command1() {}
  virtual void execute() = 0;
};

class JumpCommand1 : public Command1
{
public:
  void execute() override
  {
    jump();
  }

private:
  void jump();
};

class FireCommand1 : public Command1
{
public:
  void execute() override
  {
    fire();
  }

private:
  void fire();
};

class SwapCommand1 : public Command1
{
public:
  void execute() override
  {
    swap();
  }

private:
  void swap();
};

class ThrowGrenadeCommand1 : public Command1
{
public:
  void execute() override
  {
    throwGrenade();
  }

private:
  void throwGrenade();
};


//コマンドパターンでInputHandlerを書き換える
class InputHandler2 
{
public:
  //コマンドをボタンに割り当てる
  InputHandler2()
  {
    buttonX_ = new JumpCommand1();
    buttonY_ = new FireCommand1();
    buttonA_ = new SwapCommand1();
    buttonB_ = new ThrowGrenadeCommand1();
  }
  ~InputHandler2()
  {
    delete buttonX_;
    delete buttonY_;
    delete buttonA_;
    delete buttonB_;
  }

  static bool isPressed(ButtonType button);
  void handleInput();

private:
  Command1* buttonX_;
  Command1* buttonY_;
  Command1* buttonA_;
  Command1* buttonB_;
};

//2.2 アクターへの指示

//各コマンドはすべてのアクターオブジェクトが使用できるわけではない

class ActorOfCh02 : public Actor
{
public:
  ActorOfCh02() {}
  ~ActorOfCh02() {}
  void jump() override;
  void fire() override;
  void swap() override;
  void throwGrenade() override;
};

class Command
{
public:
  virtual ~Command() {}
  //関数を呼び出すときにアクターを渡す
  virtual void execute(Actor& actor) = 0;
};

class JumpCommand : public Command
{
public:
  void execute(Actor& actor) override
  {
    actor.jump();
  }
};

class FireCommand : public Command
{
public:
  void execute(Actor& actor) override
  {
    actor.fire();
  }
};

class SwapCommand : public Command
{
public:
  void execute(Actor& actor) override
  {
    actor.swap();
  }
};

class ThrowGrenadeCommand : public Command
{
public:
  void execute(Actor& actor) override
  {
    actor.throwGrenade();
  }
};

class InputHandler
{
public:
  InputHandler();
  ~InputHandler();

  static bool isPressed(ButtonType button);
  Command* handleInput();

private:
  Command* buttonX_;
  Command* buttonY_;
  Command* buttonA_;
  Command* buttonB_;
};

Command* InputHandler::handleInput() //ハンドラはコマンドを返すだけで、アクターに関する知識を持たない
{
  if(isPressed(ButtonType::BUTTON_X)) {
    return buttonX_;
  }
  else if(isPressed(ButtonType::BUTTON_Y)) {
    return buttonY_;
  }
  else if(isPressed(ButtonType::BUTTON_A)) {
    return buttonA_;
  }
  else if(isPressed(ButtonType::BUTTON_B)) {
    return buttonB_;
  }
  return nullptr;
};

