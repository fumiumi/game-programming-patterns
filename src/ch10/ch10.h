#pragma once

namespace
{
  const int MAX_ENTITIES = 10;
}

class Entity
{
public:
  Entity()
      : x_(0.0), y_(0.0) {
        };

  virtual ~Entity();
  virtual void update(double elapsed) = 0;

  double x() const { return x_; }
  double y() const { return y_; }

  void setX(double x) { x_ = x; }
  void setY(double y) { y_ = y; }

private:
  double x_;
  double y_;
};

class World
{
public:
  World()
    : numEntities_(0)
  {
  }

  void gameLoop();

private:
  Entity *entities_[MAX_ENTITIES];
  int numEntities_;
};