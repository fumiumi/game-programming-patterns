// 第5章：プロトタイプ

class Monster
{
public:
  virtual ~Monster() {}
  // プロトタイプパターンを実現するクローンメソッド
  virtual Monster *clone() const = 0;

  //...
};

class Ghost : public Monster
{
public:
  Ghost() {}
  Ghost(int health, int speed)
      : health_(health),
        speed_(speed)
  {
  }

  virtual Monster *clone() const
  {
    // クローンを作成
    return new Ghost(health_, speed_);
  }

private:
  int health_;
  int speed_;
};

// スポナークラス：Monsterの発生装置
class Spawner
{
public:
  Spawner(Monster *prototype)
      : prototype_(prototype)
  {
  }

  Monster *spawnMonster()
  {
    return prototype_->clone();
  }

private:
  Monster *prototype_;
};

//怪物生成関数
Monster *spawnGhost()
{
  return new Ghost();
}

typedef Monster *(*SpawnCallback)();

class Spawner2
{
public:
  Spawner2(SpawnCallback spawn)
      : spawn_(spawn)
  {}

  Monster *spawnMonster()
  {
    return spawn_();
  }

private:
  SpawnCallback spawn_;
};

//テンプレート
class Spawner3
{
public:
  virtual ~Spawner3() {}
  virtual Monster *spawnMonster() = 0;
};  

template <class T>
class SpawnFor : public Spawner3
{
public:
  virtual Monster *spawnMonster()
  {
    return new T();
  }
};