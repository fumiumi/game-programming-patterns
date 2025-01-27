#include "ch07.h"
#include <string>

namespace
{
  const int JUMP_VELOCITY = 5;
  std::string IMAGE_JUMP = "jump.png";
  std::string IMAGE_DUCK = "dock.png";
  std::string IMAGE_STAND = "stand.png";
  std::string IMAGE_DIVE = "dive.png";
}

Heroine::Heroine()
  : pos_x_(0), 
    pos_y_(0), 
    velocity_x_(0), 
    velocity_y_(0), 
    is_jumping_(false),
    is_ducking_(false)
{
}

// 最初の実装
void Heroine::HandleInput(Input input)
{
  if(input == Input::PRESS_B)
  {
    velocity_x_ = JUMP_VELOCITY;
    SetGraph(IMAGE_JUMP);
  }
}

// エアージャンプを防止するために、is_jumping_フラグを追加
void Heroine::HandleInput(Input input)
{
  if(input == Input::PRESS_B)
  {
    if(!is_jumping_)
    {
      is_jumping_ = true;
      velocity_x_ = JUMP_VELOCITY;
      SetGraph(IMAGE_JUMP);
    }
  }
}

// 下を押したら屈む機能を追加する
void Heroine::HandleInput(Input input)
{
  if(input == Input::PRESS_B)
  {
    if(!is_jumping_)
    {
      //...
    }
  }
  else if(input == Input::PRESS_DOWN)
  {
    if(!is_jumping_)
    {
      SetGraph(IMAGE_DUCK);
    }
  }
  else if(input == Input::RELEASE_DOWN)
  {
    SetGraph(IMAGE_STAND);
  }
}

// 今度は屈んだ姿勢でジャンプ→「下」を離す→ヒロインが直立姿勢に戻るというバグが生まれた。
// これを修正するために、is_ducking_フラグを追加する
void Heroine::HandleInput(Input input)
{
  if(input == Input::PRESS_B)
  {
    if(!is_jumping_ && !is_ducking_)
    {
      // jump
    }
  }
  else if(input == Input::PRESS_DOWN)
  {
    if(!is_jumping_)
    {
      is_ducking_ = true;
      SetGraph(IMAGE_DUCK);
    }
  }
  else if(input == Input::RELEASE_DOWN)
  {
    is_ducking_ = false;
    SetGraph(IMAGE_STAND);
  }
}

// 今度は、ジャンプ中に「下」ボタンを押すとヒロインが「ダイブ攻撃」するとかっこいいと考えた！
void Heroine::HandleInput(Input input)
{
  if(input == Input::PRESS_B)
  {
    if(!is_jumping_ && !is_ducking_)
    {
      // jump
    }
  }
  else if(input == Input::PRESS_DOWN)
  {
    if(!is_jumping_)
    {
      // duck
    }
    else
    {
      is_jumping_ = false;
      SetGraph(IMAGE_DIVE);
    }
  }
  else if(input == Input::RELEASE_DOWN)
  {
    if(is_ducking_)
    {
      is_ducking_ = false;
      SetGraph(IMAGE_STAND);
    }
  }
}

// 条件分岐も状態ベースで行うほうがFSMらしい
void Heroine::HandleInput(Input input)
{
  switch(state_)
  {
    case State::STATE_STANDING:
      if(input == Input::PRESS_B)
      {
        // ジャンプ状態に遷移
        state_ = State::STATE_JUMPING;
        velocity_x_ = JUMP_VELOCITY;
        SetGraph(IMAGE_JUMP);
      }
      else if(input == Input::PRESS_DOWN)
      {
        // 屈み状態に遷移
        state_ = State::STATE_DUCKING;
        SetGraph(IMAGE_DUCK);
      }
      break;
      
      //その他の状態
  }
}

// 今度は時間変化する要素の追加を考える
void Heroine::Update()
{
  if(state_ == State::STATE_DUCKING)
  {
    charge_time_++;
    if(charge_time_ > 100)
    {
      SuperBomb();
    }
  }
}

void Heroine::HandleInput(Input input)
{
  switch(state_)
  {
    case State::STATE_STANDING:
      if(input == Input::PRESS_B)
      {
        //.,,
      }
      else if(input == Input::PRESS_DOWN)
      {
        // 屈み状態に遷移
        state_ = State::STATE_DUCKING;
        charge_time_ = 0;
        SetGraph(IMAGE_DUCK);
      }
      //...
      break;
      
      //その他の状態
  }
}