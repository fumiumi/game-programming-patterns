#include "ch10.h"

void World::gameLoop()
{
  while(true)
  {
    // input処理

    // update処理
    for(int i = 0; i < numEntities_; ++i)
    {
      entities_[i]->update();
    }

    // 物理処理
    // 描画処理
  }
}