#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
  vector<bool> s(n+1, true);
  vector<int> p;
  s[0] = s[1] = false;
  for (int i = 2; i <= n; ++i) {
    if (s[i]) {
      p.push_back(i);
      for (long long j = (long long)i*(long long)i; j <= n; j += i) {
        s[j] = false;
      }
    }
  }
  return p;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
