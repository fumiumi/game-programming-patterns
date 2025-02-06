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