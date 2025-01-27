#include "State.h"
#include "StandingState.h"
#include <memory>

class DuckingState : public HeroineState2
{
public:
  DuckingState()
      : charge_time_(0)
  {
  }

  virtual HeroineState2 HandleInput(Heroine &heroine, Heroine::Input input) override;

  virtual void Update(Heroine &heroine) override;

  // 入口処理
  virtual void Enter(Heroine &heroine) override;

private:  
  // これはかがみ状態にしか意味をなさないので、Heroineクラスから分離
  int charge_time_;
};