#include "State.h"

void Heroine::HandleInput(Input input)
{
  HeroineState2 state = state_->HandleInput(*this, input);

  if(state != nullptr)
  {
    delete state_;
    state_ = state;

    // 新しい状態の入口処理
    state_->Enter(*this);
  }
}