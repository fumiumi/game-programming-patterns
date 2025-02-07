// 13.6.1型オブジェクトのカプセル化
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

enum HealthState
{
  LOW_HEALTH,
  MEDIUM_HEALTH,
  HIGH_HEALTH
}

// Monsterが保持している系統を公開することもできる
class Monster
{
  public:
    Monster(Breed &breed)
    : health_(breed.getHealth()),
      breed_(breed)
    {}

    // 系統公開することで、外部コードが型オブジェクトにアクセスできるようになる
    Breed &getBreed() { return breed_; }

    const char *getAttack() const { return breed_.getAttack(); }
    Breed &getBreed() { return breed_; }

  private:
    int health_;
    Breed& breed_;
}

const char *Monster::getAttack() const 
{
  if(health_ < LOW_HEALTH)
  {
    return "怪物は弱々しくもがいた。";
  }

  return breed_.getAttack();
}