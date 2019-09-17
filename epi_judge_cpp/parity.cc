#include "test_framework/generic_test.h"

static short ps[256];

static short count(int n) {
  short c = 0;
  while (n) {
    c += n & 1;
    n >>= 1;
  }
  return c;
}
static void fill_ps() {
  for (int i = 0; i < 256; ++i) {
    ps[i] = count(i) & 1;
  }
}
short Parity(unsigned long long x) {
  fill_ps();
  short p = 0;
  while (x) {
    p ^= ps[x & 0xff];
    x >>= 8;
  }
  return p;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
