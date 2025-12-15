#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "idraw.hpp"

namespace topit
{
  struct Rectangle : IDraw
  {
    p_t start;
    int a, b;
    p_t begin() const override;
    p_t next(p_t cur) const override;
    Rectangle(int x, int y, int length, int height);
  };
}

#endif