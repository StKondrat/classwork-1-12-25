#ifndef GEOM_HPP
#define GEOM_HPP
#include <cstddef>

namespace topit
{
  struct p_t
  {
    int x, y;
  };


  bool operator == (p_t a, p_t b);

  bool operator != (p_t a, p_t b);

  struct f_t
  {
    p_t aa;
    p_t bb;
  };

  f_t build_frame(const p_t * pts, size_t s);

  size_t rows(f_t fr);
  size_t cols(f_t fr);
}

#endif