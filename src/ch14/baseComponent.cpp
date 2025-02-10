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


class InputComponent
{
public:
  virtual ~InputComponent() {}
  virtual void update(Bjorn &bjorn) = 0;
};

class PlayerInputComponent : public InputComponent
{
public:
  virtual void update(Bjorn &bjorn) override
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
  }

private:
  static const int WALK_ANIMATION = 1;
};

class Bjorn
{
public:
  int velocity;
  int x, y;

  Bjorn(InputComponent *inputComponent)
      : velocity_(0),
        x_(0),
        y_(0),
        input_(inputComponent) 
    {};

  void update(World &world, Graphics &graphics)
  {
    input_->update(*this);
    physics_.update(*this, world);
    graphics_.update(*this, graphics);
  };

private:
  InputComponent* input_;
  PhysicsComponent physics_;
  GraphicsComponent graphics_;
};

class DemoInputComponent : public InputComponent
{
public:
  virtual void update(Bjorn &bjorn) override
  {
    // 自動的にbjornを動かすAI...
  }
};

void makeBjorn()
{
  Bjorn *bjorn = new Bjorn(new PlayerInputComponent());
  Bjorn *demoBjorn = new Bjorn(new DemoInputComponent());
}


// 他のドメインも抽象化
class PhysicsComponent
{
public:
  virtual ~PhysicsComponent() {}
  virtual void update(GameObject &object, World &world) = 0;
};

class GraphicsComponent
{
public:
  virtual ~GraphicsComponent() {}
  virtual void update(GameObject &object, Graphics &graphics) = 0;
};

class GameObject
{
public:
  // 課題: コンポーネント間で共有するデータをどうするか
  int velocity;
  int x, y;

  GameObject( InputComponent *input, 
              PhysicsComponent *physics, 
              GraphicsComponent *graphics
            )
      : velocity_(0),
        x_(0),
        y_(0),
        input_(input),
        physics_(physics),
        graphics_(graphics)
    {};

  void update(World &world, Graphics &graphics)
  {
    input_->update(*this);
    physics_->update(*this, world);
    graphics_->update(*this, graphics);
  };

private:
  InputComponent* input_;
  PhysicsComponent* physics_;
  GraphicsComponent* graphics_;
};

// 各ゲームオブジェクト用のコンポーネントを作成していく
class BjornInputComponent : public InputComponent
{
  //...
};

class BjornPhysicsComponent : public PhysicsComponent
{
  //...
};

class BjornGraphicsComponent : public GraphicsComponent
{
  //...
};

GameObject *CreateBjorn()
{
  return new GameObject(new BjornInputComponent(),
                        new BjornPhysicsComponent(),
                        new BjornGraphicsComponent());
}





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