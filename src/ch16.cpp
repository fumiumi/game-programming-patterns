#include <string>

// 第16章：サービスロケータ

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

// サービスロケータ
class Locator
{
public:
  static Audio *GetAudio() { return *service_; }

  static void Provide(Audio *service)
  {
    service_ = service;
  }

private:
  static Audio *service_;
};

// サービスの呼び出し
void hoge()
{
  Audio *audio = Locator::GetAudio();
  audio->PlaySound(VERY_LOUD_BANG);
}

// サービスのありか
// ゲーム起動時にロケータにサービスを登録する
void GameInit()
{
  ConsoleAudio *audio = new ConsoleAudio;
  Locator::Provide(audio);
}

// NULLオブジェクト」パターン
class NullAudio : public Audio
{
public:
  virtual void PlaySound(int soundID) override
  {
    // 何もしない
  }

  virtual void StopSound(int soundID) override
  {
    // 何もしない
  }

  virtual void StopAllSounds() override
  {
    // 何もしない
  }
};

// ロケータを修正
class Locator
{
public:
  // nullオブジェクトで初期化する
  staric void Initialize() { service_ = &nullService_; }

  static Audio *GetAudio() { return *service_; }

  static void Provide(Audio *service)
  {
    if (service == nullptr)
    {
      service = &nullService_;
    }
    service_ = service;
  }

private:
  static Audio *service_;
  static NullAudio nullService_;
};

// ログ・デコレータ
class LoggedAudio : public Audio
{
public:
  LoggedAudio(Audio *wrapped) : wrapped_(wrapped) {}

  virtual void PlaySound(int soundID) override
  {
    log("Play sound");
    wrapped_.PlaySound(soundID);
  }

  virtual void StopSound(int soundID) override
  {
    log("Stop sound");
    wrapped_.StopSound(soundID);
  }

  virtual void StopAllSounds() override
  {
    log("Stop all sounds");
    wrapped_.StopAllSounds();
  }

private:
  void log(const char *message)
  {
    // ログを出力する
  }
  Audio &wrapped_;
};

// ログ出力に切り替え
void enableAudioLogging()
{
  // 既存のサービスをデコレートする
  Audio *service = new LoggedAudio(Locator::GetAudio());
  // 新しいサービスに切り替える
  Locator::Provide(service);
}

// サービスのスコープ
class Base
{
  // サービスのありかを突き止め、service_に格納する

protected:
  static Audio GetAudio() { return *service_; }

private:
  static Audio *service_;
}

