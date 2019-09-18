#include <stdexcept>

#include "test_framework/generic_test.h"
unsigned long long ClosestIntSameBitCount(unsigned long long x) {
  // Find the lowest pair of differing bits.
  // Note the description in the book 4.4 seems a bit wrong about the LSB, which is not relevant
  const int nBits = sizeof(x)*8;
  for (int i = 0; i < nBits - 1; ++i) {
    if (((x >> i) ^ (x >> (i+1))) & 1) {
      return (x ^ (3 << i));
    }
  }
  throw std::invalid_argument("all bits are 0 or 1");
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "closest_int_same_weight.cc",
                         "closest_int_same_weight.tsv", &ClosestIntSameBitCount,
                         DefaultComparator{}, param_names);
}
