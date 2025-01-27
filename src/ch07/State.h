#pragma once
#include <string>
#include <memory>

// Stateパターンでは、以下のような「状態」は仮想関数として定義する
// enum State
// {
//   STATE_STANDING,
//   STATE_JUMPING,
//   STATE_DUCKING,
//   STATE_DIVING
// };

static const int MAX_CHARGE = 100;

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

  virtual void HandleInput(Input input)
  {
    state_->HandleInput(*this, input);
  }

  virtual void Update()
  {
    state_->Update(*this);
  }

  void SetGraph(std::string graph_path);

  void SetState(std::unique_ptr<HeroineState> state);

  void Jump();

  void SuperBomb();

  int ChargeTime() { return charge_time_; }

  bool IsJumping() const { return is_jumping_; }
  bool IsDucking() const { return is_ducking_; }

private:
  int pos_x_;
  int pos_y_;
  int velocity_x_;
  int velocity_y_;
  bool is_jumping_;
  bool is_ducking_;
  int charge_time_;
  std::unique_ptr<HeroineState2> state_;
  std::unique_ptr<HeroineState2> equipment_;
};

class HeroineState
{
public:
  virtual ~HeroineState() = default;
  virtual void HandleInput(Heroine &heroine, Heroine::Input input) {}
  virtual void Update(Heroine &heroine) {}
};

// 各々のFSMに固有の状態インスタンスを持たせる
class HeroineState2
{
  public:
  virtual ~HeroineState2() = default;
  virtual HeroineState2* HandleInput(Heroine &heroine, Heroine::Input input);
  virtual void Update(Heroine &heroine);
}

// 状態オブジェクトにメンバ変数がない場合、staticなインスタンスを一つ作ればいい

// 前方宣言
class StandingState;
class DuckingState;
class JumpingState;
class DivingState;

class ActorState
{
public:
  static StandingState standing;
  static DuckingState ducking;
  static JumpingState jumping;
  static DivingState diving;
  //...
};

