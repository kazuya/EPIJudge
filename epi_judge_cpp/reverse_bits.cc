#include "test_framework/generic_test.h"

static unsigned long long ReverseBits(unsigned long long n) {
  n = ((n & 0x00000000FFFFFFFFULL) << 32) | ((n & 0xFFFFFFFF00000000ULL) >> 32);
  n = ((n & 0x0000FFFF0000FFFFULL) << 16) | ((n & 0xFFFF0000FFFF0000ULL) >> 16);
  n = ((n & 0x00FF00FF00FF00FFULL) << 8) | ((n & 0xFF00FF00FF00FF00ULL) >> 8);
  n = ((n & 0x0F0F0F0F0F0F0F0FULL) << 4) | ((n & 0xF0F0F0F0F0F0F0F0ULL) >> 4);
  n = ((n & 0x3333333333333333ULL) << 2) | ((n & 0xCCCCCCCCCCCCCCCCULL) >> 2);
  n = ((n & 0x5555555555555555ULL) << 1) | ((n & 0xAAAAAAAAAAAAAAAAULL) >> 1);
  return n;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
