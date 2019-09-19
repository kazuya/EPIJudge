#include "test_framework/generic_test.h"
long long Reverse(int xx) {
  if (xx < 0) {
    return -Reverse(-xx);
  }
  long long x = xx;
  long long y = 0;
  while (x) {
    y *= 10;
    y += x % 10;
    x /= 10;
  }
  return y;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
