#include "geom.hpp"
#include <stdexcept>
#include <iostream>

bool topit::operator == (p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y;
}

bool topit::operator != (p_t a, p_t b)
{
  return !(a==b);
}

size_t topit::rows(f_t fr)
{
  return (fr.bb.y - fr.aa.y + 1);
}

size_t topit::cols(f_t fr)
{
  return (fr.bb.x - fr.aa.x + 1);
}

topit::f_t topit::build_frame(const p_t * p, size_t s)
{
  if (!s) {
    throw std::logic_error("bad size");
  }
  
  int xmin = p[0].x; int ymin = p[0].y;
  int xmax = xmin; int ymax = ymin;
  for (size_t i = 1; i < s; ++i) {
    xmin = std::min(xmin, p[i].x);
    ymin = std::min(ymin, p[i].y);
    xmax = std::max(xmax, p[i].x);
    ymax = std::max(ymax, p[i].y);
  }
  p_t a{xmin, ymin};
  p_t b{xmax, ymax};
  return f_t{a, b};
}
