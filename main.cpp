#include <iostream>
#include <cstddef>
#include "ascii_draw.hpp"

int main()
{
  using namespace topit;
  IDraw * shp[5] = {};
  p_t * pts = nullptr;
  size_t s = 0;
  int err = 0;

  try
  {
    shp[0] = new Diag(0, 0, 7, 7);
    shp[1] = new VSeg(0, 0, 7);;
    shp[2] = new HSeg(0, 7, 0);
    shp[3] = new Square(10, 0, 7);
    shp[4] = new Rectangle(20, 0, 2, 7);

    for (size_t i = 0; i < 5; ++i)
    {
      get_points(*shp[i], &pts, s);
    }
    f_t fr = build_frame(pts, s);
    char * cnv = build_canvas(fr, '.');
    for (size_t i = 0; i < s; ++i)
    {
      paint(cnv, fr, pts[i], '@');
    }
    flush(std::cout, cnv, fr);
    delete [] cnv;
  }
  
  catch (...)
  {
    std::cerr << "Error!\n";
    err = 1;
  }
  delete shp[4];
  delete shp[3];
  delete shp[2];
  delete shp[1];
  delete shp[0];
  return err;
}
