// 第13章：型オブジェクト

// 第一段階：型オブジェクトの基本形
//  class Breed
//  {
//    pubulic:
//      Breed(int health, const char *attack)
//      : health_(health),
//        attack_(atttack)
//      {}

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

// 第二段階：型オブジェクトのファクトリ
class Breed
{
  pubulic :
      // Breedの中にMonsterのファクトリを作ることで、
      // カスタムアロケータなどを利用してメモリ配置を最適化する余地が生まれる
      Monster *
      newMonster()
  {
    return new Monster(*this);
  }

  Breed(int health, const char *attack)
      : health_(health),
        attack_(atttack)
  {
  }

  int getHealth() const { return health_; }
  const char *getAttack() const { return attack_; }

private:
  int health_;
  const char *attacK_;
};

class Monster
{
  friend class Breed;

public:
  cont char *getAttack() const { return breed_.getAttack(); }

private:
  Monster(Breed &breed)
      : health_(breed.getHealth()),
        breed_(breed)
  {
  }

  int health_;
  Breed &breed_;
};