// src/world.hpp

#pragma once // use in all hpps

#include "types.hpp"
#include <optional>
// Vec2, Pose2D, Obstacle, ControlCommand, Robot, SensorData
// deg2rad, rad2deg, clamp, uniform, normal

// struct and class are identical datatypes
// its just that struct members are public by default and class are private by
// default

class World {
public:
  void collide(float x);
  // World: min vec2. max vec2, add_obstacle, obstacles, is_inside, collides,
  // raycast
  World(const Vec2 &min, const Vec2 &max);

  void add_obstacle(const Obstacle &obst);

  // read-only obstacles vector, this is how you access it
  const std::vector<Obstacle> &obstacles() const;

  // const right is read-only function, const left is read-only variable/return
  // value const left on a function parameter TRANSFORMS the rvalue copy into a
  // constant even if the variable itself was not

  bool is_inside(const Vec2 &p) const;
  bool collides(const Vec2 &center, float radius) const;
  std::optional<float> raycast(const Pose2D &origin, float max_range) const;

private:
  Vec2 world_min_; // world_min_ in menu so that in the kitchen we can use it
                   // for a fast init list
  Vec2 world_max_;
  std::vector<Obstacle> obstacles_;
};