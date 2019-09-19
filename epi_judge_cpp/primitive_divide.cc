#include "test_framework/generic_test.h"

unsigned long long Add(unsigned long long x, unsigned long long y) {
  unsigned long long z = x ^ y;
  unsigned long long c = (x & y) << 1;
  while (c) {
    unsigned long long zz = z ^ c;
    c = (z & c) << 1;
    z = zz;
  }
  return z;
}

unsigned Subtract(unsigned long long x, unsigned long long y, unsigned &b) {
  unsigned long long yy = Add(~y, 1);
  unsigned long long z = Add(x, yy);
  b = (z & (1ULL << 63)) ? 1 : 0;
  return z;
}

unsigned Divide(unsigned x, unsigned y) {
  unsigned q = 0;
  for (int i = 31; i >= 0; --i) {
    unsigned long long yy = (unsigned long long)y << i;
    unsigned b;
    unsigned z = Subtract(x, yy, b);
    if (!b) {
      x = z;
      q = Add(q, 1U << i);
    }
  }
  return q;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_divide.cc", "primitive_divide.tsv",
                         &Divide, DefaultComparator{}, param_names);
}
