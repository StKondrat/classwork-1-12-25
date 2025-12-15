#include "square.hpp"

topit::p_t topit::Square::begin() const
{
  return start;
}

topit::p_t topit::Square::next(p_t cur) const
{
  if (cur.x == start.x + 1 && cur.y == start.y)
  {
    return begin();
  }
  if (cur.y < start.y + side && cur.x == start.x)
  {
    return {cur.x, cur.y + 1};
  }
  if (cur.y == start.y + side && cur.x < start.x + side)
  {
    return {cur.x + 1, cur.y};
  }
  if (cur.x == start.x + side && cur.y > start.y)
  {
    return {cur.x, cur.y - 1};
  }
  if (cur.x > start.x && cur.y == start.y)
  {
    return {cur.x - 1, cur.y};
  }
  return begin();
}

topit::Square::Square(int x, int y, int s) : start{x, y}, side{s} {}