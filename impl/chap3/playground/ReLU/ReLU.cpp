/**
 * ReLU関数
 * h(x) = (x > 0) ? x : 0
 */

#include <iostream>
#include "libgnuplot.hpp"

int main() {
  GnuplotPipe gp;
  gp.setXrange(-5.0, 6.0);
  gp.setYrange(-1.0, 6.0);
  gp.sendCmdFromString("f(x) = x <= 0 ? 0 : x");
  gp.sendCmdFromString("plot f(x)");
}