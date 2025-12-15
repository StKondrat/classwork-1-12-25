#include "idraw.hpp"

static void extend(topit::p_t ** pts, size_t s, topit::p_t p)
{
  topit::p_t * res = new topit::p_t[s + 1];
  for (size_t i = 0; i < s; ++i)
  {
    res[i] = (*pts)[i];
  }
  res[s] = p;
  delete[] *pts;
  *pts = res;
}

size_t topit::get_points(IDraw& b, p_t ** pts, size_t & s)
{
  size_t added = 0;
  p_t p = b.begin();

  extend(pts, s, p);
  ++s;
  ++added;

  while (true)
  {
    p = b.next(p);
    if (p == b.begin()) break;

    extend(pts, s, p);
    ++s;
    ++added;
  }
  return added;
}