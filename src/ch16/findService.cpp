// 16.6.2 サービスのありかがわからなかったときの対処法

namespace
{
  const int VERY_LOUD_BANG = 1;
}

// 公開するインターフェースを抽象ンターフェースとして定義する
class Audio
{
public:
  virtual ~Audio() {}
  virtual void PlaySound(int soundID) = 0;
  virtual void StopSound(int soundID) = 0;
  virtual void StopAllSounds() = 0;
};

// プロバイダ
class ConsoleAudio : public Audio
{
public:
  virtual void PlaySound(int soundID) override
  {
    // サウンドを再生する
  }

  virtual void StopSound(int soundID) override
  {
    // サウンドを停止する
  }

  virtual void StopAllSounds() override
  {
    // すべてのサウンドを停止する
  }
};

// ゲームを停止する
class Locator
{
public:
  static Audio &GetAudio()
  {
    Audio *service = nullptr;

    // サービスのありかを探す

    assert(service != nullptr);

    return *service;
  }

  static void Provide(Audio *service)
  {
    service_ = service;
  }

private:
  static Audio *service_;
};

void assert(bool b)
{
  if (!b)
  {
    std::terminate();
  }
}

