#pragma once
#include <string>

enum State
{
  STATE_STANDING,
  STATE_JUMPING,
  STATE_DUCKING,
  STATE_DIVING
};

class Heroine
{
public:
  enum class Input
  {
    PRESS_B, 
    PRESS_DOWN, 
    PRESS_RIGHT, 
    PRESS_B_AND_RIGHT,
    RELEASE_B,
    RELEASE_DOWN,
    RELEASE_RIGHT,
    RELEASE_B_AND_RIGHT
  };

  Heroine();
  ~Heroine() = default;

  void HandleInput(Input input);

  void Update();

  void SetGraph(std::string graph_path);

  void Jump();

  void SuperBomb();
  
private:
  int pos_x_;
  int pos_y_;
  int velocity_x_;
  int velocity_y_;
  bool is_jumping_;
  bool is_ducking_;
  State state_;
  int charge_time_;
};