/**
 * libgnuplot.cpp
 * C++からgnuplotを制御するためのヘルパ関数群
 */

#include "libgnuplot.hpp"
#include <boost/lexical_cast.hpp>

/**
 * @brief Gnuplotへのパイプをオープン
 */
GnuplotPipe::GnuplotPipe() 
{
  gpipe_ = popen("gnuplot -persist", "w");
}

/**
 * @brief Gnuplotへのパイプをクローズ
 */
GnuplotPipe::~GnuplotPipe() 
{
  pclose(gpipe_);
}

/**
 * @brief Gnuplotに文字列をgnuplotへのcommandとして送信 (エラーメッセージを返せると良い)
 * @param command command
 */
void
GnuplotPipe::sendCmdFromString(std::string const& cmd) 
{
  fprintf(gpipe_, "%s\n", cmd.c_str());
}

/**
 * @brief Xrangeを指定
 * @param lx 左端
 * @param rx 右端
 */
void
GnuplotPipe::setXrange(double const lx, double const rx) 
{
  std::string l = boost::lexical_cast<std::string>(lx);
  std::string r = boost::lexical_cast<std::string>(rx);
  sendCmdFromString("set xrange[" + l + ":" + r + "]");
}

/**
 * @brief Yrangeを指定
 * @param ly 上端
 * @param ry 下端
 */
void 
GnuplotPipe::setYrange(double const ly, double const ry) {
  std::string l = boost::lexical_cast<std::string>(ly);
  std::string r = boost::lexical_cast<std::string>(ry);
  sendCmdFromString("set yrange[" + l + ":" + r + "]");
}