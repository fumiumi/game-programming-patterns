// 第13章：型オブジェクト

class Breed
{
  pubulic:
    Breed(int health, const char *attack)
    : health_(health),
      attack_(atttack)
    {}

    int getHealth() const { return health_; }
    const char *getAttack() const { return attack_; }

  private:
    int health_;
    const char *attacK_;
};

class Monster
{
  public:
    Monster(Breed &breed)
    : health_(breed.getHealth()),
      breed_(breed)
    {}

    const char *getAttack() const { return breed_.getAttack(); }

  private:
    int health_;
    Breed& breed_;
};