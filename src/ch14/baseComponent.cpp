class InputComponent
{
public:
  virtual ~InputComponent() {}
  virtual void update(Bjorn &bjorn) = 0;
};

class PlayerInputComponent : public InputComponent
{};