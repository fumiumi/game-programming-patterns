#pragma once
#include "State.h"
// StateパターンクラスをHeroineに移譲

class Heroine
{
  public:
  enum class Input
  {
    PRESS_B, 
    PRESS_DOWN, 
    PRESS_RIGHT, 
    PRESS_B_AND_RIGHT,
    RELEASE_B,
    RELEASE_DOWN,
    RELEASE_RIGHT,
    RELEASE_B_AND_RIGHT
  };

    Heroine();
    ~Heroine() = default;

    virtual void HandleInput(Input input)
    {
      state_->HandleInput(*this, input);
    }

    virtual void Update()
    {
      state_->Update(*this);
    }

    // その他

  private:
    HeroineState *state_;
};