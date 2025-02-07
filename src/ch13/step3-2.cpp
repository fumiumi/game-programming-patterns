// // 第三段階：Breedが親のBreedを持てるようにする
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

// // 何を継承して、何をオーバーライドするか決める
// int Breed::getHealth()
// {
//   // オーバーライド
//   if(health_ != 0 || parent_ == nullptr)
//   {
//     return health_;
//   }

//   // 継承
//   return parent_->getHealth();
// }

// const char *Breed::getAttack()
// {
//   // オーバーライド
//   if(attack_ != nullptr || parent_ == nullptr)
//   {
//     return attack_;
//   }

//   // 継承
//   return parent_->getAttack();
// }

// 方法２：オブジェクト生成時に継承（コピーダウンデリゲーション）
// 親系統をメンバ変数に保持する必要がなくなる
Breed::Breed(Breed *parent, int health, const char *attack)
    : health_(health),
      attack_(attack)
{
  // オーバーライドしない属性を継承
  if(parent != nullptr)
  {
   if(health_ == 0)
   {
     health_ = parent->getHealth();
   }

    if(attack_ == nullptr)
    {
      attack_ = parent->getAttack();
    }
  }
}