//第3章：フライトウェイト

#include <iostream>
#include "ch03.h"

int main()
{
  World world;

  // 移動コストを取得
  int cost = world.getMovementCost(0, 0);

  std::cout << "Movement cost: " << cost << std::endl;
}