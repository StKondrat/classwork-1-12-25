#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "idraw.hpp"

namespace topit
{
  struct Square : IDraw
  {
    p_t start;
    int side;
    p_t begin() const override;
    p_t next(p_t cur) const override;
    Square(int x, int y, int s);
  };
}

#endif