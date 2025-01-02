// 第4章　オブザーバ

#include "ch04_Observer.h"
#include <vector>

// Achievementsクラスのメンバ関数の実装
void Achievements::OnNotify(const Entity &entity, Event event)
{
  switch (event)
  {
  case Event::kEVENT_START_FALL:
    if (entity.IsHero() && heroIsOnBridge_)
    {
      Unlock(Achievement::kACHIEVEMENT_FELL_OFF_BRIDGE);
    }
    break;
    // 他のイベントに対する処理
  }
}

void Achievements::Unlock(Achievement achievement)
{
  // 実績をアンロックする
}

// Subjectクラスのメンバ関数の実装
void Subject::AddObserver(Observer *observer)
{
  observers_.emplace_back(observer);
}

void Subject::RemoveObserver(Observer *observer)
{
  observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
                                  [observer](const std::unique_ptr<Observer> &o)
                                  { return o.get() == observer; }),
                   observers_.end());
}

void Subject::Notify(const Entity &entity, Event event)
{
  for (auto &observer : observers_)
  {
    observer->OnNotify(entity, event);
  }
}

void Physics::UpdateEntity(Entity &entity)
{
  bool wasOnSurface = entity.IsOnSurface();
  entity.Accelerate(kGRAVITY);
  entity.Update();

  if (wasOnSurface && !entity.IsOnSurface())
  {
    Notify(entity, Event::kEVENT_START_FALL);
  }
}