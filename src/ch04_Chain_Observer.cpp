// 連結パターン

#include <iostream>

class Entity;
class Event;

class Subject
{
public:
  Subject() : head_(nullptr) {}

  void AddObserver(Observer *observer);
  void RemoveObserver(Observer *observer);

  //...

private:
  Observer *head_;
};

class Observer
{
  friend class Subject;

public:
  Observer() : next_(nullptr) {}

  //...

private:
  Observer *next_;
};

void Subject::AddObserver(Observer *observer)
{
  observer->next_ = head_;
  head_ = observer;
}

void Subject::RemoveObserver(Observer *observer)
{
  if (head_ == observer)
  {
    head_ = observer->next_;
    return;
  }

  Observer *current = head_;
  // 先頭から一つずつ次のオブザーバーを移動
  while (current)
  {
    if (current->next_ == observer)
    {
      current->next_ = observer->next_;
      return;
    }
    current = current->next_;
  }
}

// リストノードのプール
class Subject2
{
  public:
    Subject2(){}

private:
  Node *head_;
};

class Node
{
  friend class Subject2;

private:
  Node *next_;
  Observer2 *observer_;
};

class Observer2
{
public:
  virtual ~Observer2() {}
  virtual void OnNotify(const Entity &entity, Event event) = 0;
};
