#pragma once
#include <string>

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
  
private:
  int pos_x_;
  int pos_y_;
  int velocity_x_;
  int velocity_y_;
  bool is_jumping_;
  bool is_ducking_;
};