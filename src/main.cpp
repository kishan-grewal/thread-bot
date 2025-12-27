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

  Vec2 operator+(const Vec2 &other) const {
    return Vec2(x + other.x, y + other.y);
  }

  Vec2 operator-(const Vec2 &other) const {
    return Vec2(x - other.x, y - other.y);
  }

  Vec2 operator*(float s) const { return Vec2(x * s, y * s); }

  Vec2 operator/(float s) const { return Vec2(x / s, y / s); }

  Vec2 unit() const {
    float len = length();
    if (len == 0.0f)
      return Vec2();
    return Vec2(x / len, y / len);
  }
};

int main() {
  Vec2 a(3.0f, 4.0f);
  Vec2 b(1.0f, 2.0f);

  Vec2 c = a + b;
  Vec2 d = a - b;
  Vec2 e = a * 2.0f;
  Vec2 f = a / 2.0f;
  Vec2 g = a.unit();

  std::cout << "a + b = (" << c.x << ", " << c.y << ")" << std::endl; // (4, 6)
  std::cout << "a - b = (" << d.x << ", " << d.y << ")" << std::endl; // (2, 2)
  std::cout << "a * 2 = (" << e.x << ", " << e.y << ")" << std::endl; // (6, 8)
  std::cout << "a / 2 = (" << f.x << ", " << f.y << ")" << std::endl; //(1.5, 2)

  std::cout << "a.unit() = (" << g.x << ", " << g.y << ")"
            << std::endl; //(0.6, 0.8)

  return 0;
}