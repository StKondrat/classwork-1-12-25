#include "dot.hpp"

topit::p_t topit::Dot::begin() const
{
  return d;
}

topit::p_t topit::Dot::next(p_t prev) const
{
  return begin();
}

topit::Dot::Dot(int x, int y) : d{x, y} {}

topit::Dot::Dot(p_t dd) : d{dd} {}