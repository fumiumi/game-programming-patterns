#include "State.h"

class StandingState : public HeroineState2
{
public:
  StandingState() = default;
  ~StandingState() = default;

  virtual HeroineState2* HandleInput(Heroine& heroine, Heroine::Input input) override;

  virtual void Update(Heroine& heroine) override;

  // 入口処理
  virturl void Enter(Heroine& heroine) override;

private:
};