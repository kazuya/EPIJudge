#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

vector<int> AddReversedPositives(vector<int> x, vector<int> y) {
  if (x.size() < y.size()) {
    std::swap(x, y);
  }
  int c = 0;
  int i = 0;
  vector<int> z;
  for (i = 0; i < y.size(); i++) {
    int s = x[i] + y[i] + c;
    z.push_back(s % 10);
    c = s / 10;
  }
  for (;i < x.size(); i++) {
    int s = x[i] + c;
    z.push_back(s % 10);
    c = s / 10;
  }
  if (c) {
    z.push_back(c);
  }
  return z;
}
vector<int> Multiply(vector<int> x, vector<int> y) {
  if (x.size() < y.size()) {
    std::swap(x, y);
  }
  int xs = x[0] > 0 ? 1 : -1;
  int ys = y[0] > 0 ? 1 : -1;
  x[0] *= xs;
  y[0] *= ys;
  std::reverse(x.begin(), x.end());
  std::reverse(y.begin(), y.end());
  vector<int> z(1, 0);

  int i;
  for (i = 0; i < y.size(); i++) {
    vector<int> r(i, 0);
    int c = 0;
    for (int j = 0; j < x.size(); ++j) {
      int m = x[j] * y[i] + c;
      c = m / 10;
      r.push_back(m % 10);
    }
    if (c) {
      r.push_back(c);
    }
    z = AddReversedPositives(z, r);
  }

  while (!z.empty() && *(z.end() - 1) == 0) {
    z.erase(z.end()-1);
  }
  if (z.empty()) {
    z.push_back(0);
  } else {
    std::reverse(z.begin(), z.end());
    z[0] *= xs*ys;
  }
  return z;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
