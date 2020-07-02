#include <iostream>
#include <iomanip>
#include <functional>
using namespace std;

constexpr double H = 10e-4;

double numeric_diff(double const X, function<double(double)> const& f) {
  // 中心差分
  return (f(X + H) - f(X - H)) / (2 * H);
}

int main() {
  function<double(double)> f = [](double x) {
    return x * x * x + 2 * x;
  };

  cout << setprecision(12) << fixed;
  cout << numeric_diff(0.0, f) << endl;
  cout << numeric_diff(1.0, f) << endl;
  cout << numeric_diff(2.0, f) << endl;
}