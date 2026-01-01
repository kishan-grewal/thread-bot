// src/types.hpp

#pragma once // use in all hpp

#include <chrono>
#include <cmath>
#include <random>
#include <vector>
// use std::mt19937 its the modern better form of random

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

// pushback for primitives and even small objects, emplaceback for massive
// objects

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
  // linear_vel, angular_vel, default:, ControlCommand: linear_vel. angular_vel
  float linear_vel = 0.0f;
  float angular_vel = 0.0f;

  ControlCommand() = default;

  ControlCommand(float linear_vel, float angular_vel)
      : linear_vel(linear_vel), angular_vel(angular_vel) {}
};

struct RobotState {
  // pose, linear_vel vel, angular_vel vel
  Pose2D pose;
  float linear_vel = 0.0f;
  float angular_vel = 0.0f;

  // no constructor needed, Pose2D has one already as does float
};

enum class ControlState { Forward, TurnLeft, TurnRight, Stop };

struct SensorData {
  // timestamp, history, default:, add_sample
  // prev distance = history.back()
  std::chrono::steady_clock::time_point timestamp;

  std::vector<float> history; // last N readings

  SensorData() = default;

  void add_sample(float d) {
    timestamp = std::chrono::steady_clock::now();
    history.push_back(d);

    // keep only last 10 samples
    if (history.size() > 10) {
      history.erase(history.begin());
    }
  }
};

// free functions

constexpr float PI = 3.14159265358979f;

inline float deg2rad(float deg) {
  // pi / 180
  return deg * PI / 180.0f;
}

inline float rad2deg(float rad) { return rad * 180.0f / PI; }

inline float clamp(float value, float min, float max) {
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

inline std::mt19937 &rng() {
  static std::mt19937 gen(
      std::random_device{}()); // static = called once per program
  return gen;
}

inline float uniform(float min, float max) {
  std::uniform_real_distribution<float> dist(min, max); // U(min, max)
  return dist(rng());
}

inline float normal(float mean, float stddev) {       // dont shadow std in c++
  std::normal_distribution<float> dist(mean, stddev); // N(u, s)
  return dist(rng());
}