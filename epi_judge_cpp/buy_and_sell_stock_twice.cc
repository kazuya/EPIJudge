#include <vector>
#include <limits>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockTwice(const vector<double>& prices) {
  vector<double> fms(prices.size());
  double m = std::numeric_limits<double>::max(), dm = 0.0;
  for (int i = 0; i < prices.size(); ++i) {
    auto a = prices[i];
    if (a < m) {
      m = a;
    }
    auto d = a - m;
    if (d > dm) {
      dm = d;
    }
    fms[i] = dm;
  }
  vector<double> bms(prices.size());
  m = std::numeric_limits<double>::min(), dm = 0.0;
  for (int i = prices.size() - 1; i >= 0; --i) {
    auto a = prices[i];
    if (a > m) {
      m = a;
    }
    auto d = m - a;
    if (d > dm) {
      dm = d;
    }
    bms[i] = dm;
  }
  fms.insert(fms.begin(), 0);
  dm = 0.0;
  for (int i = 0; i < prices.size(); ++i) {
    auto d = fms[i] + bms[i];
    if (d > dm) {
      dm = d;
    }
  }

  return dm;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
