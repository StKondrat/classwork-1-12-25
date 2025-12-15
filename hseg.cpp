#include "hseg.hpp"

topit::p_t topit::HSeg::begin() const
{
  return a;
}

topit::p_t topit::HSeg::next(p_t cur) const
{
  if (cur == b) return begin();
  int step = (b.x >= a.x) ? 1 : -1;
  return {cur.x + step, a.y};
}

topit::HSeg::HSeg(int x1, int x2, int y) : a{x1, y}, b{x2, y} {}