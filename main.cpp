#include <iostream>
#include <cstddef>

namespace topit
{
  struct p_t
  {
    int x, y;
  };

  struct f_t
  {
    p_t aa;
    p_t bb;
  };

  size_t rows(f_t fr);
  size_t cols(f_t fr);
  
  struct IDraw
  {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t prev) const = 0;
    virtual ~IDraw() = default;
  };

  bool operator == (p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }

  bool operator != (p_t a, p_t b)
  {
    return !(a==b);
  }

  struct Dot: IDraw
  {
    p_t begin() const override;
    p_t next(p_t prev) const override;
    p_t d;
    Dot(int x, int y);
    explicit Dot(p_t dd);
  };

  struct VSeg : IDraw
  {
    p_t a, b;

    VSeg(int x, int y1, int y2) : a{x, y1}, b{x, y2} {}

    p_t begin() const override
    {
      return a;
    }

    p_t next(p_t cur) const override
    {
      if (cur == b) return begin();
      int step = (b.y >= a.y) ? 1 : -1;
      return {a.x, cur.y + step};
    }
  };

  struct HSeg : IDraw
  {
    p_t a, b;

    HSeg(int x1, int x2, int y) : a{x1, y}, b{x2, y} {}

    p_t begin() const override
    {
      return a;
    }

    p_t next(p_t cur) const override
    {
      if (cur == b) return begin();
      int step = (b.x >= a.x) ? 1 : -1;
      return {cur.x + step, a.y};
    }
  };

  void extend(p_t ** pts, size_t s, p_t p);
  size_t get_points(IDraw& b, p_t ** pts, size_t & s);
  f_t build_frame(const p_t * pts, size_t s);
  char * build_canvas(f_t fr, char fill);
  void paint(char * cnv, f_t fr, p_t p, char fill);
  void flush(std::ostream& os, const char * cnv, f_t fr);
}

int main()
{
  using namespace topit;
  IDraw * shp[3] = {};
  p_t * pts = nullptr;
  size_t s = 0;
  int err = 0;

  try
  {
    shp[0] = new Dot(0, 0);
    shp[1] = new Dot(2, 3);
    shp[2] = new Dot(-5, -2);

    for (size_t i = 0; i < 3; ++i)
    {
      get_points(*shp[i], &pts, s);
    }
    f_t fr = build_frame(pts, s);
    char * cnv = build_canvas(fr, '.');
    for (size_t i = 0; i < s; ++i)
    {
      paint(cnv, fr, pts[i], '#');
    }
    flush(std::cout, cnv, fr);
    delete [] cnv;
  }
  
  catch (...)
  {
    std::cerr << "Error!\n";
    err = 1;
  }
  delete shp[2];
  delete shp[1];
  delete shp[0];
  return err;
}

size_t topit::rows(f_t fr)
{
  return (fr.bb.y - fr.aa.y + 1);
}

size_t topit::cols(f_t fr)
{
  return (fr.bb.x - fr.aa.x + 1);
}

topit::p_t topit::Dot::begin() const
{
  return d;
}

topit::p_t topit::Dot::next(p_t prev) const
{
  return begin();
}

void topit::extend(p_t ** pts, size_t s, p_t p)
{
  p_t * res = new p_t[s + 1];
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
  size_t upd_s = s + 1;
  p_t * res = new p_t[upd_s];
  for (size_t i = 0; i < s; ++i)
  {
    res[i] = (*pts)[i];
  }
  p_t p = b.begin();
  res[s] = p;
  delete[] *pts;
  *pts = res;
  size_t delta = 1;
  while (b.next(p) != b.begin())
  {
    p = b.next(p);
    extend(pts, s + delta, p);
    ++delta;
  }
  s = upd_s;
  return delta;
}

topit::f_t topit::build_frame(const p_t * p, size_t s)
{
  if (!s) {
    throw std::logic_error("bad size");
  }
  
  int xmin = p[0].x; int ymin = p[0].y;
  int xmax = xmin; int ymax = ymin;
  for (size_t i = 1; i < s; ++i) {
    xmin = std::min(xmin, p[i].x);
    ymin = std::min(ymin, p[i].y);
    xmax = std::max(xmax, p[i].x);
    ymax = std::max(ymax, p[i].y);
  }
  p_t a{xmin, ymin};
  p_t b{xmax, ymax};
  return f_t{a, b};
}

char * topit::build_canvas(f_t fr, char fill)
{
  char * cnv = new char[rows(fr) * cols(fr)];
  for (size_t i = 0; i < rows(fr) * cols(fr); ++i)
  {
    cnv[i] = fill;
  }
  return cnv;
}

void topit::paint(char * cnv, f_t fr, p_t p, char fill)
{
  int dx = p.x - fr.aa.x;
  int dy = fr.bb.y - p.y;
  cnv[dy * cols(fr) + dx] = fill;
}

void topit::flush(std::ostream& os, const char * cnv, f_t fr)
{
  for (size_t i = 0; i < rows(fr); ++i)
  {
    for (size_t j = 0; j < cols(fr); ++j)
    {
      os << cnv[i * cols(fr) + j];
    }
    os << "\n";
  }
}

topit::Dot::Dot(int x, int y) : d{x, y} {}

topit::Dot::Dot(p_t dd) : d{dd} {}
