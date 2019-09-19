#include <tuple>
#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
struct Rect {
  int x, y, width, height;
};

struct Line {
  int x, length;
};

Line IntersectLine(const Line& L1, const Line& L2) {
  if (L1.x > L2.x) {
    return IntersectLine(L2, L1);
  }
  int p1 = L1.x+L1.length;
  int p2 = L2.x+L2.length;
  if (p1 >= L2.x) {
    if (p1 >= p2) {
      return Line{L2.x, L2.length};
    } else {
      return Line{L2.x, p1-L2.x};
    }
  } else {
    return Line{0,-1};
  }
}

Rect IntersectRectangle(const Rect& R1, const Rect& R2) {
  Line Lx = IntersectLine(Line{R1.x,R1.width}, Line{R2.x,R2.width});
  if (Lx.length < 0) {
    return {0, 0, -1, -1};
  }
  Line Ly = IntersectLine(Line{R1.y,R1.height}, Line{R2.y,R2.height});
  if (Ly.length < 0) {
    return {0, 0, -1, -1};
  }

  return {Lx.x, Ly.x, Lx.length, Ly.length};
}
bool operator==(const Rect& r1, const Rect& r2) {
  return std::tie(r1.x, r1.y, r1.width, r1.height) ==
         std::tie(r2.x, r2.y, r2.width, r2.height);
}

template <>
struct SerializationTraits<Rect> : UserSerTraits<Rect, int, int, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("area({})", arg_name), FmtStr("perimeter({})", arg_name),
            FmtStr("max(w, h)({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Rect& x) {
    return {x.height * x.width, 2 * (x.height + x.width),
            std::max(x.height, x.width)};
  }
};

std::ostream& operator<<(std::ostream& out, const Rect& r) {
  return PrintTo(out, std::make_tuple(r.x, r.y, r.width, r.height));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"R1", "R2"};
  return GenericTestMain(args, "rectangle_intersection.cc",
                         "rectangle_intersection.tsv", &IntersectRectangle,
                         DefaultComparator{}, param_names);
}
