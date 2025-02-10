// コンポーネントパターンでは、コンポーネント間の情報のやりとりが課題
// この問題を解決策の一つとして、コンポーネント間の情報のやりとりを行うためのインターフェースを定義する
class Component
{
public:
  virtual ~Component();
  virtual void Recieve(int message) = 0;
}

class GameObject
{
public:
  void Send(int message)
  {
    for (int i = 0; i < MAX_COMPONENTS; i++)
    {
      if (components_[i])
      {
        components_[i]->Recieve(message);
      }
    }
  }

private:
  static const int MAX_COMPONENTS = 16;
  Component *components_[MAX_COMPONENTS];
};