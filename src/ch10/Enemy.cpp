#include "Enemy.h"

void Skeleton::update(double elapsed)
{
  if(partollingLeft_)
  {
    setX(x() - elapsed);

    if(x() == 0)
    {
      partollingLeft_ = false;
      setX(-x());
    }
  }
  else
  {
    setX(x() + elapsed);
    if(x() == 100)
    {
      partollingLeft_ = true;
      setX(-x());
    }
  }
}

void Statue::update(double elapsed)
{
  if(++frames_ == delay_)
  {
    shootLightning();

    frames_ = 0;
  }
}