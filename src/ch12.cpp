// 第12章：サブクラスサンドボックス

enum SoundId
{
  SOUND_BEEP,
  SOUND_SQUEEK,
  SOUND_TAP,
  SOUND_SPROING,
  SOUND_SWOOP.
  SOUND_DIVE
};

enum ParticleType
{
  PARTICLE_DUST,
  PARTICLE_SPARKLE,
  PARTICLE_STARS
};

// 外部システム
class ParticleSystem
{
};

// ユーティリティ関数を提供する基底クラス
class Superpower
{
public:
  virtual ~Superpower() {}

protected:
  virtual void Activate() = 0;

  void Move(double x, double y, double z)
  {
    // 何か処理
  }

  void PlaySound(SoundId sound_id)
  {
    // 何か処理
  }

  void swawnParticles(ParticleType type, int count)
  {
    // 何か処理
  }
};

// 派生クラスでは、protectedメンバ関数を組み合わせてActivate()を実装する
class SkyLaunch : public Superpower
{
protected:
  // 空中高く飛び上がるSuperpower、適切な効果音とパーティクルもセット
  virtual void Activate() override
  {
    Move(0, 0, 20);
    PlaySound(SOUND_SPROING);
    swawnParticles(PARTICLE_DUST, 10);
  }
};

// よりバリエーション豊かなSuperpowerを提供するために手を加える
class Superpower
{
public:
  virtual ~Superpower() {}

protected:
  virtual void Activate() = 0;

  void Move(double x, double y, double z)
  {
    // 何か処理
  }

  void PlaySound(SoundId sound_id)
  {
    // 何か処理
  }

  void swawnParticles(ParticleType type, int count)
  {
    // 何か処理
  }

  double getHeroX() const { return hero_x_; }
  double getHeroY() const { return hero_y_; }
  double getHeroZ() const { return hero_z_; }

private:
  double hero_x_;
  double hero_y_;
  double hero_z_;
}

class SkyLaunch : public Superpower
{
protected:
  virtual void Activate() override
  {
    if (getHeroZ() == 0)
    {
      playSound(SOUND_SPROING);
      swawnParticles(PARTICLE_DUST, 10);
      move(0, 0, 20);
    }
    else if(getHeroZ() < 10.0f)
    {
      // ダブルジャンプ
      playSound(SOUND_SQUEEK);
      move(0, 0, 100 - getHeroZ() - 20);
    }
    else
    {
      // ダイブアタック
      playSound(SOUND_DIVE);
      swawnParticles(PARTICLE_SPARKLE, 1);
      move(0, 0, -getHeroZ());
    }
  }
};

// Superpowerは肥大化したときは、コンポジションを使って分割する
class SoundPlayer
{
  void playSound(SoundId sound_id)
  {
    // 何か処理
  }

  void stopSound(SoundId sound_id)
  {
    // 何か処理
  }

  void setVolume(SoundId sound_id, float volume)
  {
    // 何か処理
  }
};

class ParticleSystem
{
  void spawnParticles(ParticleType type, int count)
  {
    // 何か処理
  }

  void update()
  {
    // 何か処理
  }
};

class Superpower
{
  protected:
    SoundPlayer& getSoundPlayer() { return sound_player_; }
    ParticleSystem& getParticleSystem() { return particle_system_; }

  private:
    SoundPlayer sound_player_;
    ParticleSystem particle_system_;
};

// 基底クラスのコンストラクタに渡す
class Superpower
{
  public:
    Superpower(ParticleSystem* particles)
      : particle_system_(particles)
    {
    }

  private:
    ParticleSystem& particle_system_;
};

// 2段階で初期化する
class Superpower
{
  public:
    void init(ParticleSystem* particles)
    {
      particle_system_ = particles;
    }

  private:
    ParticleSystem* particle_system_;
};

Superpower* createSkyLaunch(ParticleSystem* particles)
{
  Superpower* power = new SkyLaunch();
  power->init(particles);
  return power;
}
