// 第14章：コンポーネント
// モノリシックなクラス

namespace Controller
{
  enum JoystickDirection
  {
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN,
  };

  JoystickDirection getJoystickDirection()
  {
  };
};

class World
{
  public:
    World()
    {
    };

    void resolveCollision(Volume &volume, int x, int y, int velocity)
    {
    };
};
class Graphics
{
};
class Volume
{
};
class Sprite
{
};

class Bjorn
{
public:
  Bjorn()
  : velocity_(0),
    x_(0),
    y_(0)
  {
  };

  void update(World &world, Graphics &graphics);

private:
  static const int WALK_ANIMATION = 1;

  int velocity_;
  int x_, y_;

  Volume volume_;

  Sprite spriteStand_;
  Sprite spriteWalkLeft_;
  Sprite spriteWalkRight_;
}

// モノリシックなupdate関数
void Bjorn::update(World &world, Graphics &graphics)
{
  // ユーザー入力を処理
  switch (Controller::getJoystickDirection())
  {
  case Controller::DIR_LEFT:
    velocity_ -= WALK_ANIMATION;
    break;

  case Controller::DIR_RIGHT:
    velocity_ += WALK_ANIMATION;
    break;
  }

  // 位置を更新
  x_ += velocity_;
  world.resolveCollision(volume_, x_, y_, velocity_);

  // スプライトを描画
  Sprite *sprite = &spriteStand_;
  if (velocity_ < 0)
  {
    sprite = &spriteWalkLeft_;
  }
  else if (velocity_ > 0)
  {
    sprite = &spriteWalkRight_;
  }
  graphics.draw(*sprite, x_, y_);
}