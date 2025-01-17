#include "StateMachine.h"
#include <string>

namespace
{
  const int JUMP_VELOCITY = 5;
  std::string IMAGE_JUMP = "jump.png";
  std::string IMAGE_DUCK = "dock.png";
  std::string IMAGE_STAND = "stand.png";
  std::string IMAGE_DIVE = "dive.png";
}

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

    case State::STATE_JUMPING:
      if(input == Input::PRESS_DOWN)
      {
        // ダイブ状態に遷移
        state_ = State::STATE_DIVING;
        SetGraph(IMAGE_DIVE);
      }
      break;

    case State::STATE_DUCKING:
      if(input == Input::RELEASE_DOWN)
      {
        // 直立状態に遷移
        state_ = State::STATE_STANDING;
        SetGraph(IMAGE_STAND);
      }
      break;

    case State::STATE_DIVING:
      break;
  }
}