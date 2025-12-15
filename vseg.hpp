#ifndef VSEG_HPP
#define VSEG_HPP
#include "idraw.hpp"

namespace topit
{
  struct VSeg : IDraw
  {
    p_t a, b;
    p_t begin() const override;
    p_t next(p_t cur) const override;
    VSeg(int x, int y1, int y2);
  };
}

#endif