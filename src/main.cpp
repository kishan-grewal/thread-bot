// src/main.cpp

#include "types.hpp"
#include <iostream>

// main returns error code
int main() {
  std::cout << "45 deg = " << deg2rad(45.0f) << "rad" << std::endl;
  std::cout << "clamp 15 to [0, 10] = " << clamp(15.0f, 0.0f, 10.0f)
            << std::endl;
  float unif = uniform(0.0f, 10.0f);
  float norm = normal(5.0f, 2.0f);
  std::cout << "unif = " << unif << ", "
            << "norm = " << norm << std::endl;

  return 0;
}