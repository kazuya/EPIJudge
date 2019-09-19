#include "test_framework/generic_test.h"
double Power(double x, int y) {
  if (y < 0) {
    return Power(1/x, -y);
  }
  int z = y >> 1;
  double p = (y & 1) ? x : 1.0L;
  if (z) {
    double pp = Power(x, z);
    p *= pp*pp;
  }
  return p;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
