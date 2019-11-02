#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  std::reverse(A.begin(), A.end());
  int c = 1;
  for (int i = 0; i < A.size(); i++) {
    A[i] += c;
    if (A[i] > 9) {
      A[i] %= 10;
      c = 1;
    } else {
      c = 0;
      break;
    }
  }
  if (c) {
    A.push_back(c);
  }
  std::reverse(A.begin(), A.end());
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
