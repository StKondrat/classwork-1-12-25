#include "rectangle.hpp"

topit::p_t topit::Rectangle::begin() const
{
  return start;
}

topit::p_t topit::Rectangle::next(p_t cur) const
{
  if (cur.x == start.x + 1 && cur.y == start.y)
  {
    return begin();
  }
  if (cur.y < start.y + b && cur.x == start.x)
  {
    return {cur.x, cur.y + 1};
  }
  if (cur.y == start.y + b && cur.x < start.x + a)
  {
    return {cur.x + 1, cur.y};
  }
  if (cur.x == start.x + a && cur.y > start.y)
  {
    return {cur.x, cur.y - 1};
  }
  if (cur.x > start.x && cur.y == start.y)
  {
    return {cur.x - 1, cur.y};
  }
  return begin();
}

topit::Rectangle::Rectangle(int x, int y, int length, int height) : start{x, y}, a{length}, b{height} {};