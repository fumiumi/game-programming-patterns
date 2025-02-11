// 同じ効果音を複数回鳴らしても音が大きくならないようにする

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

class Audio
{
public:
  static void Init()
  {
    head_ = 0;
    tail_ = 0;
  }

  static void PlaySound(SoundId id, int volume);
  static void Update();

private:
  static int head_;
  static int tail_;

  static const int MAX_PENDING = 16;
  static PlayMessage pending_[MAX_PENDING];
};


// 同じ効果音を複数回鳴らしても音が大きくならないようにする
void Audio::PlaySound(SoundId id, int volume)
{
  assert((tail_ + 1) % MAX_PENDING != head_); 

  // 保留中のリクエストを調べる
  for (int i = head_; i != tail_; i = (i + 1) % MAX_PENDING)
  {
    if (pending_[i].id == id)
    {
      // 2つの音量のうち大きい方を採用する
      pending_[i].volume = std::max(pending_[i].volume, volume);
      return;
    }
  }

  // リストの最後に追加する
  pending_[tail_].id = id;
  pending_[tail_].volume = volume;
  // 環状バッファ
  tail_ = (tail_ + 1) % MAX_PENDING;
}

// キューの中のリクエストを一つだけ処理する
// 先頭のマーカーをインクリメントするだけで、配列要素の移動は行わない
void Audio::Update()
{
  // 保留中のサウンドリクエストが無ければ何もしない
  if(head_ == tail_)
  {
    return;
  }

  ResourceId resource = loadSound(pending_[head_].id);
  int channel = findOpenChannel();

  if (channel == -1)
  {
    return;
  }

  startSound(resource, channel, pending_[head_].volume);

  // 環状バッファ
  head_ = (head_ + 1) % MAX_PENDING;
}


void assert(bool condition)
{
  if (!condition)
  {
    std::terminate();
  }
}
