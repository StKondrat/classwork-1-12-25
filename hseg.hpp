#ifndef HSEG_HPP
#define HSEG_HPP
#include "idraw.hpp"

namespace topit
{
  struct HSeg : IDraw
  {
    p_t a, b;
    p_t begin() const override;
    p_t next(p_t cur) const override;
    HSeg(int x1, int x2, int y);
  };
}

#endif