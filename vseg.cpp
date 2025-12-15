#include "vseg.hpp"

topit::p_t topit::VSeg::begin() const
{
  return a;
}

topit::p_t topit::VSeg::next(p_t cur) const
{
  if (cur == b) return begin();
  int step = (b.y >= a.y) ? 1 : -1;
  return {a.x, cur.y + step};
}

topit::VSeg::VSeg(int x, int y1, int y2) : a{x, y1}, b{x, y2} {}