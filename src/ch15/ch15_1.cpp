
class Event
{
  // イベントのデータ
};

Event getNextEvent()
{
  // イベントを取得する
  return Event();
}

void polling()
{
  while (running)
  {
    Event event = getNextEvent();
    // イベントを処理する
  }
}

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

class Audio
{
public:
  static void PlaySound(SoundId id, int volume);

private:
  static void startSound(ResourceId resource, int channel, int volume);
}

void Audio::PlaySound(SoundId id, int volume)
{
  ResourceId resource = loadSound(id);
  int channel = findOpenChannel();
  startSound(resource, channel, volume);
}

static const SoundId SOUND_SELECT = 1;
static const int VOL_MAX = 100;

class Menu
{
public:
  void OnSelect(int index)
  {
    Audio::PlaySound(SOUND_SELECT, VOL_MAX);
    // メニューの選択を処理する
  } 
}