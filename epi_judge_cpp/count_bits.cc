#include "test_framework/generic_test.h"

static short rs[256];

static short count(int n) {
  short c = 0;
  while (n) {
    if (n & 1) {
      ++c;
    }
    n >>= 1;
  }
  return c;
}
static void fill_rs() {
  for (int i = 0; i < 256; ++i) {
    rs[i] = count(i);
  }
}

short CountBits(unsigned int x) {
  fill_rs();
  short c = 0;
  for (int i = 0; x && i < sizeof(x); ++i) {
    c += count(x & 0xFF);
    x >>= 8;
  }
  return c;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "count_bits.cc", "count_bits.tsv", &CountBits,
                         DefaultComparator{}, param_names);
}
