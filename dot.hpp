#ifndef DOT_HPP
#define DOT_HPP
#include "idraw.hpp"
#include <stdexcept>

namespace topit
{
  struct Dot: IDraw
  {
    p_t begin() const override;
    p_t next(p_t prev) const override;
    p_t d;
    Dot(int x, int y);
    explicit Dot(p_t dd);
  };

}

#endif