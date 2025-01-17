#pragma once

#include <string>

// ステートパターン
// 有限状態機械（FSM）を表現する方法を考える

// enumはFSMの状態の集合を表現できる
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
  void SetGraph(std::string graph_path);

  //...
  
private:
  int pos_x_;
  int pos_y_;
  int velocity_x_;
  int velocity_y_;
  State state_;
};