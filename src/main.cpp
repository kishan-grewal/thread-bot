// src/main.cpp

#include <cmath>
#include <iostream>

struct Vec2 {
  float x = 0.0f;
  float y = 0.0f;

  // faster
  Vec2(float x, float y) : x(x), y(y) {}

  // slower
  // Vec2(float x, float y) {
  //     this->x = x;
  //     this->y = y;
  // }

  // we also want the no args constructor
  Vec2() = default;

  float length() const { return std::sqrt(x * x + y * y); }
};

int main() {
  Vec2 a(3.0f, 4.0f);
  Vec2 b;

  std::cout << "a: (" << a.x << ", " << a.y << ")" << std::endl;
  std::cout << "a.length(): (" << a.length() << ")" << std::endl;
  std::cout << "b: (" << b.x << ", " << b.y << ")" << std::endl;

  return 0;
}