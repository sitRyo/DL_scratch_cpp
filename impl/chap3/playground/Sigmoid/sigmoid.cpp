/**
 * sigmoid関数
 * h(x) = 1 / 1 + exp(-x)
 */

#include <iostream>
#include "libgnuplot.hpp"

int main() {
  GnuplotPipe gp;
  gp.setXrange(-6.0, 6.0);
  gp.setYrange(-0.1, 1.1);
  gp.sendCmdFromString("plot 1 / (1 + exp(-x))");
}