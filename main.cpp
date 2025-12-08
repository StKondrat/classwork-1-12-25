// struct VSeg; struct HSeg
#include <iostream>
#include <cstddef>

namespace top
{
  struct p_t
  {
    int x, y;
  };

  struct IDraw
  {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
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
    p_t next(p_t) const override;
    p_t o;
    Dot(int x, int y);
  };

  struct frame_t
  {
    p_t left_bot;
    p_t right_top;
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

  void make_f(IDraw ** b, size_t k);
  void extend(p_t ** pts, size_t s, p_t p)
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

  size_t points(const IDraw& d, p_t ** pts, size_t s)
  {

  }

  size_t get_points(IDraw& b, p_t ** pts, size_t & s)
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
    return delta;
  }

  frame_t build_frame(const p_t * pts, size_t s);
  char * build_canvas(frame_t f);
  void paint_canvas(char * cnv, frame_t fr, const p_t * pts, size_t k, char f);
  void print_canvas(const char * cnv, frame_t fr);
}

int main()
{
  using namespace top;
  IDraw * f[3] = {};
  p_t * p = nullptr;
  size_t s = 0;
  char * cnv = nullptr;
  p_t ** kp = nullptr;
  int err = 0;

  try
  {
    make_f(f, 3);
    for (size_t i = 0; i < 3; ++i)
    {
      get_points(f[i], kp, s);
    }
    frame_t fr = build_frame(p, s);
    cnv = build_canvas(fr);
    paint_canvas(cnv, fr, p, s, '#');
    print_canvas(cnv, fr);
  }

  catch (...)
  {
    err = 1;
    delete f[0];
    delete f[1];
    delete f[2];
    delete[] p;
    delete[] cnv;
    return err;
  }
}

top::Dot::Dot(int x, int y): IDraw(), o{x, y}
{}

top::p_t top::Dot::begin() const
{
  return o;
}

top::p_t top::Dot::next(p_t) const
{
  return begin();
}

top::frame_t top::build_frame(const p_t * p, size_t s)
{
  if (!s) {
    throw std::logic_error("bad size");
  }
  
  int xmin = p[0].x; int ymin = p[0].y;
  int xmax = xmax; int ymax = ymin;
  for (size_t i = 1; i < s; ++i) {
    xmin = std::min(xmin, p[i].x);
    ymin = std::min(ymin, p[i].y);
    xmax = std::max(xmax, p[i].x);
    ymax = std::max(ymax, p[i].y);
  }
  p_t a{xmin, ymin};
  p_t b{xmax, ymax};
  return frame_t{a, b};
}