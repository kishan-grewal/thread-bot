// src/main.cpp

#include <cmath>
#include <iostream>

// WHAT IS OBSTACLE:
// filled rectangle
// max (5, 2)
//     ┌────────┐
//     │████████│
//     │████████│
//     └────────┘
// min (0, 0)

// WHEN TO PASS THE VARIABLE vs ITS REF
// Primitives by value, everything else by const.&
// "constref" is the best way to use the value, efficient and safe const . &

// const
// const int fn() const { }
//   ^                ^
//   │                └── "I won't modify my own members"
//   └── "I return something you can't modify"
// the first const is linked with the return type int, the second is linked with
// "this"

// const must be done at creation, you can't make something const later
// the key insight being that when you pass a var into a function, you create an
// rvalue, the var inside the function is its own entity

struct Vec2 {
  // x, y, default:, Vec2: x. y, length, unit
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

struct Pose2D {
  // x, y, theta, default:, Pose2D: x. y. theta,
  float x = 0.0f;
  float y = 0.0f;
  float theta = 0.0f;

  Pose2D() = default;

  Pose2D(float x, float y, float theta) : x(x), y(y), theta(theta) {}
};

struct Obstacle {
  // min vec2, max vec2, default:, Obstacle: min. max, contains
  Vec2 min;
  Vec2 max;

  Obstacle() = default;

  Obstacle(const Vec2 &min, const Vec2 &max) : min(min), max(max) {}

  bool Contains(const Vec2 &p) const {
    return p.x >= min.x && p.x <= max.x && p.y >= min.y && p.y <= max.y;
  }
};

struct ControlCommand {
  // linear, angular, default:, ControlCommand: linear. angular
  float linear = 0.0f;
  float angular = 0.0f;

  ControlCommand() = default;

  ControlCommand(float linear, float angular)
      : linear(linear), angular(angular) {}
};

struct Robot {
  // pose, linear vel, angular vel
  Pose2D pose;
  float linear_velocity = 0.0f;
  float angular_velocity = 0.0f;

  // no constructor needed, Pose2D has one already as does float
};

enum class ControlState { Forward, TurnLeft, TurnRight, Stop };

// main returns error code
int main() {
  Obstacle wall(Vec2(0.0f, 0.0f), Vec2(5.0f, 2.0f));

  std::cout << "inside: " << wall.Contains(Vec2(2.5f, 1.0f)) << std::endl;
  std::cout << "outside: " << wall.Contains(Vec2(5.5f, 1.0f)) << std::endl;
    
  return 0;
}