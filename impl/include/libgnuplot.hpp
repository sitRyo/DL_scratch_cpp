/**
 * libgnuplot.hpp
 * C++からgnuplotを制御するためのヘルパ関数群
 */

#ifndef __INC_LIBGNUPLOT__
#define __INC_LIBGNUPLOT__

#include <cstdio>
#include <string>

/**
 * @brief 2次元のグラフをプロットするためのGnuplotヘルパ関数群
 */
class GnuplotPipe {
  FILE *gpipe_;
public:
  GnuplotPipe(); 
  virtual ~GnuplotPipe();
  void sendCmdFromString(std::string const&);
  void setXrange(double const, double const);
  void setYrange(double const, double const);
};

#endif // __INC_LIBGNUPLOT__