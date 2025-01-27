#include "DuckingState.h"
#include "StandingState.h"

HeroineState2 *DuckingState::HandleInput(Heroine &heroine, Heroine::Input input)
{
  if (input == Heroine::Input::RELEASE_DOWN)
  {
    // 直立状態に遷移　
    // 入口処理を実装したので、他状態のSetGraph()は不要になった
    return new StandingState();
  }
  // その他の入力

  // この状態に留まる
  return nullptr;
}

void DuckingState::Update(Heroine &heroine)
{
  charge_time_++;
  if (heroine.ChargeTime() > MAX_CHARGE)
  {
    heroine.SuperBomb();
  }
}

void DuckingState::Enter(Heroine &heroine)
{
  // かがみ状態に遷移したときに必ず必要な処理
  heroine.SetGraph("duck.png");
}