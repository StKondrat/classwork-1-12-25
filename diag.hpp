#ifndef DIAG_HPP
#define DIAG_HPP
#include "idraw.hpp"

namespace topit
{
  struct Diag : IDraw
  {
    p_t a, b;
    p_t begin() const override;
    p_t next(p_t cur) const override;
    Diag(int x1, int y1, int x2, int y2);
  };
}

#endif