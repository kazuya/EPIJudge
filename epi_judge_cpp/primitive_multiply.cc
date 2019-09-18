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

unsigned long long Multiply(unsigned long long x, unsigned long long y) {
  unsigned long long a = 0;
  for (int i = 0; i < sizeof(unsigned long long)*8; ++i) {
    if (x & (1ULL << i)) {
      a = Add(a, y << i);
    }
  }

  return a;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_multiply.cc",
                         "primitive_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
