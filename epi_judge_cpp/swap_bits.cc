#include "test_framework/generic_test.h"
long long SwapBits(long long x, int i, int j) {
  long long b_i = (x >> i) & 1;
  long long b_j = (x >> j) & 1;
  if (b_i ^ b_j) {
    long long mask = ~((1ll << i) | (1ll << j));
    return (x & mask) | (b_j << i) | (b_i << j);
  }
  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "i", "j"};
  return GenericTestMain(args, "swap_bits.cc", "swap_bits.tsv", &SwapBits,
                         DefaultComparator{}, param_names);
}
