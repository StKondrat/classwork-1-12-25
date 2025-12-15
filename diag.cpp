#include "diag.hpp"

topit::p_t topit::Diag::begin() const
{
  return a;
}

topit::p_t topit::Diag::next(p_t cur) const
{
  if (cur == b) return begin();
  int stepx = (b.x >= a.x) ? 1 : -1;
  int stepy = (b.y >= a.y) ? 1 : -1;
  return {cur.x + stepx, cur.y + stepy};
}

topit::Diag::Diag(int x1, int y1, int x2, int y2) : a{x1, y1}, b{x2, y2} {}