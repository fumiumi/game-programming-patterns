#include "ch10.h"

class Skeleton : public Entity
{
public:
  Skeleton()
    : partollingLeft_(true)
  {
  }

  void update(double elapsed) override;

private:
  bool partollingLeft_;
};

class Statue : public Entity
{
public:
  Statue()
  {
  }

  void update(double elapsed) override;

private:
  void shootLightning()
  {
    // 雷を撃つ処理
  }

  int frames_ = 0;
  int delay_ = 60;
};