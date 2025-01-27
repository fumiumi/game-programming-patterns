// 第4章　オブザーバ
#include <iostream>
#include <list>

namespace
{
  const double kGRAVITY = 9.8;
  const int kMAXOBSERVERS = 10;
}

enum class Event
{
  kEVENT_START_FALL,
};

enum class Achievement
{
  kACHIEVEMENT_FELL_OFF_BRIDGE,
};

// ゲーム内のエンティティを表すクラス
class Entity
{
public:
  virtual ~Entity() {}
  virtual void UpdateEntity(Entity &entity) = 0;
  virtual void Accelerate(double gravity) = 0;
  virtual bool IsOnSurface() = 0;
  void Update();
  bool IsHero() const;
};

// オブザーバーパターンは、オブジェクト間の依存関係を解消するためのデザインパターンです。
class Observer
{
public:
  virtual ~Observer() {
    subject_->RemoveObserver(this);
  }
  virtual void OnNotify(const Entity &entity, Event event) = 0;
  void ReceiveSubjectDestroyed()
  {
    isSubjectExist_ = false;
  }

private:
  Subject * subject_;
  bool isSubjectExist_;
};

class Subject
{
public:
  ~Subject()
  {
    // まずは全 Observer に「もう削除するよ」と伝える
    NotifyDestroy();

    // 全ての unique_ptr<Observer> を解放する
    // Observer のデストラクタが呼ばれるが、observer 側で subject_ = nullptr 済みになっていれば安全
    observers_.clear();
  }
  void AddObserver(Observer *observer);
  void RemoveObserver(Observer *observer);

protected:
  void Notify(const Entity &entity, Event event);

private:
  void NotifyDestroy();
  std::list<std::unique_ptr<Observer>> observers_;
};

// オブザーバーパターンの例：実績機能
class Achievements : public Observer
{
public:
  virtual void OnNotify(const Entity &entity, Event event) override;

private:
  void Unlock(Achievement achievement);
  bool heroIsOnBridge_;
  // 他の実績に必要な情報
};


// 物理エンジン
class Physics : public Subject
{
public:
  Physics() : wasOnSurface_(false) {};
  void UpdateEntity(Entity &entity);

private:
  bool wasOnSurface_;
};

// 他の方法：サブジェクトを継承ではなく包含で使う
class Subject2
{
public:
  void AddObserver(Observer *observer);
  void RemoveObserver(Observer *observer);

protected:
  void Notify(const Entity &entity, Event event);

private:
  std::list<std::unique_ptr<Subject>> observers_;

  // Physics2がサブジェクトメンバのNotifyにアクセスするために必要
  friend class Physics2;
};

class Physics2
{
public:
  Physics2() : subject(std::make_unique<Subject2>()), wasOnSurface_(false) {};
  void UpdateEntity(Entity &entity)
  {
    bool wasOnSurface = entity.IsOnSurface();
    entity.Accelerate(kGRAVITY);
    entity.Update();

    if (wasOnSurface && !entity.IsOnSurface())
    {
      subject->Notify(entity, Event::kEVENT_START_FALL);
    }
  }

private:
  std::unique_ptr<Subject2> subject;
  bool wasOnSurface_;
};

