#include <iostream>
#include <iomanip>
#include <functional>
#include <vector>
#include <optional>

using namespace std;

using pi = pair<int, int>;

double numerical_diff(double const, function<double(double)> const&);
optional<vector<double>> numerical_gradient(vector<double> const&, vector<function<double(double)>> const&);
optional<vector<double>> gradient_descent(vector<double> const&, vector<function<double(double)>> const&, const double lr, const int step_count);

constexpr double H = 10e-4;

double
numerical_diff(double const X, function<double(double)> const& f) {
  // 中心差分
  return (f(X + H) - f(X - H)) / (2 * H);
}

optional<vector<double>>
numerical_gradient(vector<double> const& X, vector<function<double(double)>> const& F) {
  const int size = X.size();
  if (size != F.size()) return nullopt;

  vector<double> grad(size);
  for (int i = 0; i < size; ++i) {
    double d = numerical_diff(X[i], F[i]);
    grad[i] = d;
  }
  
  return grad;
}

optional<vector<double>>
gradient_descent(vector<double> const& X, vector<function<double(double)>> const& F, const double lr = 0.1, const int step_count = 100) {
  if (X.size() != F.size()) return nullopt;

  vector<double> res = X;
  const int size = X.size();
  for (int cnt = 0; cnt < step_count; ++cnt) {
    auto grad = numerical_gradient(res, F);
    for (int j = 0; j < size; ++j) {
      res[j] -= grad.value()[j] * lr;
    }
  }

  return res;
}

int main() {
  cout << fixed;
  function<double(double)> f = [](const double x) {
    return x * x;
  };

  auto res = gradient_descent({2.0, 3.0}, {f, f});
  for (auto itr : res.value()) {
    cout << itr << " ";
  }
  cout << endl;
}