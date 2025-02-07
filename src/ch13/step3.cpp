// 第13章：型オブジェクト

// 型オブジェクトの基本形
// class Breed
// {
//   pubulic:
//     Breed(int health, const char *attack)
//     : health_(health),
//       attack_(atttack)
//     {}

//     int getHealth() const { return health_; }
//     const char *getAttack() const { return attack_; }

//   private:
//     int health_;
//     const char *attacK_;
// };

// class Monster
// {
//   public:
//     Monster(Breed &breed)
//     : health_(breed.getHealth()),
//       breed_(breed)
//     {}

//     cont char *getAttack() const { return breed_.getAttack(); }

//   private:
//     int health_;
//     Breed& breed_;
// };

// 第三段階：Breedが親のBreedを持てるようにする
class Breed
{
  pubulic : Breed(Breed *parent, int health, const char *attack)
      : Breed_(parent),
        health_(health),
        attack_(atttack)
  {
  }

  int getHealth();
  const char *getAttack();

private:
  Breed *parent_;
  int health_;
  const char *attacK_;
};

// 何を継承して、何をオーバーライドするか決める
// 方法１：実行時に動的に決める
int Breed::getHealth()
{
  // オーバーライド
  if(health_ != 0 || parent_ == nullptr)
  {
    return health_;
  }

  // 継承
  return parent_->getHealth();
}

const char *Breed::getAttack()
{
  // オーバーライド
  if(attack_ != nullptr || parent_ == nullptr)
  {
    return attack_;
  }

  // 継承
  return parent_->getAttack();
}