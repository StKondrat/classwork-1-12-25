#ifndef IDRAW_HPP
#define IDRAW_HPP
#include <cstddef>
#include "geom.hpp"

namespace topit
{
  struct IDraw
  {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t prev) const = 0;
    virtual ~IDraw() = default;
  };

  size_t get_points(IDraw& b, p_t ** pts, size_t & s);
}

#endif