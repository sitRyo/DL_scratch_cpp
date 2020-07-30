/**
 * MNISTReader.hpp
 * MNISTデータセットのリーダ
 */

#ifndef _INC_MNISTREADER_
#define _INC_MNISTREADER_

#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

class MNISTReader {
  std::ios_base::openmode fileOpenMode;

  std::ifstream trainImageIfs;
  std::ifstream t10kImageIfs;
  std::ifstream trainLabelIfs;
  std::ifstream t10kLabelIfs;

  bool isNormalize;

  void skipHeaderData();

  /* Debug */
  void printHeader();
public:
  using BufType = std::unique_ptr<unsigned char[]>;
  using NormalizedBufType = std::unique_ptr<double[]>;
  using LabelType = unsigned int;
  
  /* 訓練画像枚数 */
  const static unsigned int TRAIN_IMAGE_NUM = 60000;

  /* 検証用画像枚数 */
  const static unsigned int T10K_IMAGE_NUM = 10000;

  /* 画像データサイズ. 1byte(グレースケール) * 28 * 28 */
  const static unsigned int IMAGE_SIZE = 28 * 28;

  /* Labelのサイズ. 1byte (0 ~ 9) */
  const static unsigned int LABEL_SIZE = 1;

  /* 画像のヘッダサイズ */
  const static unsigned int IMAGE_HEADER_SIZE = 16;

  /* ラベルのヘッダサイズ */
  const static unsigned int LABEL_HEADER_SIZE = 8;

  /* 1ピクセルの最大値 */
  static const double IMG_PIXEL_MAX;  

  MNISTReader(std::string const&);
  ~MNISTReader() = default;
  MNISTReader(const MNISTReader&) = delete;
  MNISTReader& operator=(const MNISTReader&) = delete;

  BufType readNextTrainImage();
  BufType readNextT10kImage();
  LabelType readNextTrainLabel();
  LabelType readNextT10kLabel();

  NormalizedBufType normalize(BufType&) const;
};

#endif // _INC_MNISTREADER_