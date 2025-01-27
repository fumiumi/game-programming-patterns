#include "StandingState.h"

// 入口処理
void StandingState::Enter(Heroine &heroine)
{
  // StandingStateに遷移したときに必ず必要な処理
  heroine.SetGraph("stand.png");
}