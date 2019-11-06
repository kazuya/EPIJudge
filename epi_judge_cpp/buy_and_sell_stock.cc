#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  double m = 0;
  double dm = 0;
  for (int i = prices.size()-1; i >= 0; --i) {
    if (prices[i] > m) {
      m = prices[i];
    } else {
      double d = m - prices[i];
      if (d > dm) {
        dm = d;
      }
    }
  }
  return dm;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
