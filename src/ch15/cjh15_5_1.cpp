// 第15章：イベントキュー

using SoundId = int;

class ResourceId
{
};

ResourceId loadSound(SoundId id)
{
  // 受け取ったハンドルを使ってリソースをロードする
  return ResourceId();
}

int findOpenChannel()
{
  // サウンドチャンネルを探す
  return 0;
}

// サウンドを出力するリクエストを「モノ化」する必要がある
// 跡になるまで取っておけるように、保留中のサウンドリクエストの詳細情報を保存する小さい構造体が必要
struct PlayMessage
{
  SoundId id;
  int volume;
};

// 保留中のメッセージを管理するための保存領域を作る
class Audio
{
public:
  static void Init()
  {
    numPending_ = 0;
  }

  static void PlaySound(SoundId id, int volume);

  // 実際にサウンドを再生する
  static void Update()
  {
    for (int i = 0; i < numPending_; i++)
    {
      ResourceId resource = loadSound(pending_[i].id);
      int channel = findOpenChannel();

      if (channel == -1)
      {
        return;
      }

      startSound(resource, channel, pending_[i].volume);
    }

    numPending_ = 0;
  }

  //...

private:
  static const int MAX_PENDING = 16;
  static PlayMessage pending_[MAX_PENDING];
  static int numPending_;
};

// PlaySound()の遅延防止のために、イベントキューを使ってサウンドリクエストを保留する
void Audio::PlaySound(SoundId id, int volume)
{
  assert(numPending_ < MAX_PENDING);

  pending_[numPending_].id = id;
  pending_[numPending_].volume = volume;
  numPending_++;
}

void assert(bool condition)
{
  if (!condition)
  {
    std::terminate();
  }
}
