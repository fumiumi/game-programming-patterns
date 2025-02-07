// 第14章：コンポーネント
// ドメインの切り出し

namespace Controller
{
  enum JoystickDirection
  {
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN,
  };

  JoystickDirection getJoystickDirection() {
  };
};

// インプットに関するドメインを切り出す
class InputComponent
{
public:
  void update(Bjorn &bjorn)
  {
    switch (Controller::getJoystickDirection())
    {
    case Controller::DIR_LEFT:
      bjorn.velocity -= WALK_ANIMATION;
      break;
    case Controller::DIR_RIGHT:
      bjorn.velocity += WALK_ANIMATION;
      break;
    }
  };

private:
  static const int WALK_ANIMATION = 1;
};

// 物理シミュレーションに関するドメインを切り出す
class PhysicsComponent
{
public:
  void update(Bjorn &bjorn, World &world)
  {
    bjorn.x += bjorn.velocity;
    world.resolveCollision(volume_, bjorn.x, bjorn.y, bjorn.velocity);
  };

private:
  Volume volume_;
};

// グラフィックスに関するドメインを切り出す
class GraphicsComponent
{
  public:
    void update(Bjorn &bjorn, Graphics &graphics)
    {
      Sprite *sprite = &spriteStand_;
      if (bjorn.velocity < 0)
      {
        sprite = &spriteWalkLeft_;
      }
      else if (bjorn.velocity > 0)
      {
        sprite = &spriteWalkRight_;
      }

      graphics.draw(*sprite, bjorn.x, bjorn.y);
    };

    private:
      Sprite spriteStand_;
      Sprite spriteWalkLeft_;
      Sprite spriteWalkRight_;
};

// 残ったBjornクラス
class Bjorn
{
public:
  int velocity;
  int x, y;

  Bjorn()
      : velocity_(0),
        x_(0),
        y_(0) 
    {};

  void update(World &world, Graphics &graphics)
  {
    inputComponent_.update(*this);
    physicsComponent_.update(*this, world);
    graphicsComponent_.update(*this, graphics);
  };=

private:
  InputComponent inputComponent_;
  PhysicsComponent physicsComponent_;
  GraphicsComponent graphicsComponent_;
};

class World
{
public:
  World() {
  };

  void resolveCollision(Volume &volume, int x, int y, int velocity) {
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
