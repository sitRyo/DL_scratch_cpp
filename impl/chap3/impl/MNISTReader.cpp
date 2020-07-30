/**
 * MNISTReader.cpp
 * MNISTReader impl
 */

// MNISTデータセットは60000枚の訓練画像と10000枚のテスト画像で構成される数字画像のデータセット
// MNISTの画像データは28×28のグレー画像で書くピクセルは0から255までの値を取る
// ※ 28×28 = 784

#include "MNISTReader.hpp"

const double MNISTReader::IMG_PIXEL_MAX = 255.0;

MNISTReader::MNISTReader(std::string const& dirPath) {
  std::string t10kImageFileName = dirPath + "t10k-images.idx3-ubyte";
  std::string t10kLabelFileName = dirPath + "t10k-labels-idx1-ubyte";
  std::string trainImageFileName = dirPath + "train-images-idx3-ubyte";
  std::string trainLabelFileName = dirPath + "train-labels-idx1-ubyte";

  fileOpenMode = std::ios_base::binary | std::ios_base::in;

  this->trainImageIfs.open(trainImageFileName, fileOpenMode);
  this->trainLabelIfs.open(trainLabelFileName, fileOpenMode);
  this->t10kImageIfs.open(t10kImageFileName, fileOpenMode);
  this->t10kLabelIfs.open(t10kLabelFileName, fileOpenMode);

  skipHeaderData();
}

void MNISTReader::skipHeaderData() {
  this->trainImageIfs.seekg(IMAGE_HEADER_SIZE, std::ios_base::beg);
  this->t10kImageIfs.seekg(IMAGE_HEADER_SIZE, std::ios_base::beg);
  this->trainLabelIfs.seekg(LABEL_HEADER_SIZE, std::ios_base::beg);
  this->t10kLabelIfs.seekg(LABEL_HEADER_SIZE, std::ios_base::beg);
}

/**
 * @brief ヘッダー情報を読み飛ばせているかテスト。検証用画像で試してみた所、きちんとできている模様。
 */
void MNISTReader::printHeader() {
  char buf[16];
  this->t10kImageIfs.read(buf, IMAGE_HEADER_SIZE);
  for (int i = 0; i < IMAGE_HEADER_SIZE; ++i) {
    printf("%02x ", buf[i]);
  }
  puts("");
}

/**
 * @brief 訓練画像から1枚データを読み出す。
 */
MNISTReader::BufType MNISTReader::readNextTrainImage() {
  // 28 * 28
  BufType trainImage = std::make_unique<unsigned char[]>(IMAGE_SIZE);
  trainImageIfs.read(reinterpret_cast<char*>(trainImage.get()), IMAGE_SIZE);
  return trainImage;
}

/**
 * @brief 検証用画像から1枚データを読み出す。
 */
MNISTReader::BufType MNISTReader::readNextT10kImage() {
  BufType t10kImage = std::make_unique<unsigned char[]>(IMAGE_SIZE);
  t10kImageIfs.read(reinterpret_cast<char*>(t10kImage.get()), IMAGE_SIZE);
  return t10kImage;
}

/**
 * @brief 訓練画像のラベルを1つ読み出す。
 */
MNISTReader::LabelType MNISTReader::readNextTrainLabel() {
  LabelType label;
  trainLabelIfs.read(reinterpret_cast<char *>(&label), LABEL_SIZE);
  return label;
}

/**
 * @brief 検証用画像のラベルを1つ読み出す。
 */
MNISTReader::LabelType MNISTReader::readNextT10kLabel() {
  LabelType label;
  t10kLabelIfs.read(reinterpret_cast<char *>(&label), LABEL_SIZE);
  return label;
}

MNISTReader::NormalizedBufType MNISTReader::normalize(BufType& img) const {
  NormalizedBufType res = std::make_unique<double[]>(IMAGE_SIZE);
  for (int i = 0; i < IMAGE_SIZE; ++i) {
    res[i] = (double) img[i] / IMG_PIXEL_MAX;
  }

  return res;
}