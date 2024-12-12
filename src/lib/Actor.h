//このプロジェクトで使うActorクラスのヘッダファイル

#pragma once

#include <iostream>

//抽象クラスActor
class Actor
{ 
public:
  Actor() {}
  virtual ~Actor() = 0;
};