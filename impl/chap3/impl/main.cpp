#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
#include <array>
#include <type_traits>
#include <cmath>

#include <eigen3/Eigen/Dense>

#include <boost/lexical_cast.hpp>

#include "MNISTReader.hpp"

/* 行列を指定した出力に表示 */
#define PRINT_MATRIX(MTX, STREAM) STREAM << MTX << std::endl;

/* 行列を標準出力に表示 */
#define PRINT_MATRIX_STDOUT(MTX) PRINT_MATRIX(MTX, std::cout)

/* 使う検証データの数 */
constexpr unsigned int READ_IMG_NUM = 10000;

/* 関数ポインタが使えないのでfanctorでsigmoidを宣言してみた。 */
struct sigmoid {
  double operator()(double const x) const {
    return 1 / (1 + std::exp(-x));
  }
};

template <class Derived>
void
softmax(Eigen::MatrixBase<Derived>& mtx) {
  double t = mtx.maxCoeff();
  mtx = mtx.unaryExpr([&t](double p){ return std::exp(p - t); });
  
  auto s = mtx.sum();
  auto m = mtx.array() / s;
  mtx = m.matrix();
}

template <class Derived>
bool 
isMatch(Eigen::MatrixBase<Derived>& vec, unsigned int label) {
  int row, col;
  vec.maxCoeff(&row, &col);
  return col == label;
}

template <unsigned int Cols>
auto 
readRow(std::ifstream& ifs) {
  std::array<double, Cols> col;
  std::string s;

  for (auto i = 0; i < Cols; ++i) {
    ifs >> s;
    col[i] = boost::lexical_cast<double>(s);
  }

  return col;
}

template <unsigned int Rows, unsigned int Cols>
Eigen::MatrixXd 
readWeightFiles(std::string const& fileName) {
  std::ifstream ifs(fileName); // for read
  Eigen::MatrixXd matrix(Rows, Cols); // Row行, Col列の行列を生成

  for (int r = 0; r < Rows; ++r) {
    auto row = readRow<Cols>(ifs);
    for (int c = 0; c < Cols; ++c) {
      matrix(r, c) = row[c];
    }
  }
  
  // PRINT_MATRIX_STDOUT(matrix);
  return matrix;
}

// 想定はRows = 1
template <unsigned int Cols, class T>
Eigen::Matrix<std::remove_all_extents_t<T>, Eigen::Dynamic, Eigen::Dynamic>
createVectorFromInput(std::unique_ptr<T>&& input) {
  Eigen::MatrixXd matrix(1, Cols);
  for (int i = 0; i < Cols; ++i) {
    matrix(0, i) = input[i];
  }

  return matrix;
}

int main(int argc, char *argv[]) {
  // 浮動小数点の表示方法を変更
  std::cout << std::fixed << std::setprecision(11);

  if (argc < 2) {
    std::cout << "Please Enter MNIST dataset path" << std::endl;
    exit(0);
  }

  std::string datasetDirPath {argv[1]};
  MNISTReader mnistReader {datasetDirPath};

  printf("read config files \nw1...\n");
  Eigen::MatrixXd w1 = readWeightFiles<784, 50>("./wfile/w1.txt"); /* 隠れ層1 重みファイル */
  printf("w2...\n");
  Eigen::MatrixXd w2 = readWeightFiles<50, 100>("./wfile/w2.txt"); /* 隠れ層2 重みファイル */
  printf("w3...\n");
  Eigen::MatrixXd w3 = readWeightFiles<100, 10>("./wfile/w3.txt"); /* 隠れ層3 重みファイル */
  printf("b1...\n");
  Eigen::MatrixXd b1 = readWeightFiles<1, 50>("./wfile/b1.txt"); /* バイアス 1 */
  printf("b2...\n");
  Eigen::MatrixXd b2 = readWeightFiles<1, 100>("./wfile/b2.txt"); /* バイアス 2 */
  printf("b3...\n");
  Eigen::MatrixXd b3 = readWeightFiles<1, 10>("./wfile/b3.txt"); /* バイアス 3 */

  // 10枚取り出してみる
  std::array<Eigen::MatrixXd, READ_IMG_NUM> trainImgs;
  std::array<unsigned int, READ_IMG_NUM> trainLabels;
  for (int i = 0; i < READ_IMG_NUM; ++i) {
    // 画像データ取得
    auto img = mnistReader.readNextT10kImage();
    auto imgNormalize = mnistReader.normalize(img);
    trainImgs[i] = createVectorFromInput<784>(std::move(imgNormalize));

    // label取得
    trainLabels[i] = mnistReader.readNextT10kLabel();
  }

  auto count = 0;
  // ニューラルネットワーク
  for (int i = 0; i < READ_IMG_NUM; ++i) {
    Eigen::MatrixXd img = trainImgs[i];
    Eigen::MatrixXd a1 = img * w1 + b1;
    Eigen::MatrixXd z1 = a1.unaryExpr(sigmoid());
    Eigen::MatrixXd a2 = z1 * w2 + b2;
    Eigen::MatrixXd z2 = a2.unaryExpr(sigmoid());
    Eigen::MatrixXd a3 = z2 * w3 + b3;
    softmax(a3);
    count += isMatch(a3, trainLabels[i]);
  }

  std::cout << "Accuracy: " << (double) count / READ_IMG_NUM << std::endl;
}
