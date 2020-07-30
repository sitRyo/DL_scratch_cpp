#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

template <class Mtx, class Func>
void setMatrix(Mtx&& m, Func&& f) {
  for (int r = 0; r < m.rows(); ++r) {
    for (int c = 0; c < m.cols(); ++c) {
      m(r, c) = f(r, c);
    }
  }
}

auto plus = [](double const a1, double const a2) {
  return a1 + a2;
};

auto mul = [](double const a1, double const a2) {
  return a1 * a2;
};

int main() {
  Matrix4d m1, m2;
  setMatrix(m1, plus);
  setMatrix(m2, mul);
  
  std::cout << "Fixed size 4-by-4 mul 4-by-4 \n";
  std::cout << m1 * m2 << std::endl;

  MatrixXd mx1(1, 20), mx2(20, 20);
  setMatrix(mx1, plus);
  setMatrix(mx2, mul);

  MatrixXd mx = mx1 * mx2;
  
  std::cout << "Dynamic size 1-by-20 mul 20-by-20 \n";
  std::cout << mx << std::endl;

  std::cout << "check utility api\n";
  std::cout << "maxCoeff (return Sclar) ";
  
  MatrixXd::Index row, col;
  std::cout << mx.maxCoeff(&row, &col) << std::endl;
  // std::cout << mx.maxCoeff() << std::endl;

  std::cout << "minCoeff (return Scalr) ";
  std::cout << mx.minCoeff(&row, &col) << std::endl;
  // std::cout << mx.minCoeff() << std::endl;

  std::cout << "mean (return Scalr) ";
  std::cout << mx.mean() << std::endl;
}