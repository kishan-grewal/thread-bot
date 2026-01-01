// src/world.cpp

// types.hpp flows through world.hpp
#include "world.hpp"
#include <cmath>
#include <optional>

World::World(const Vec2 &min, const Vec2 &max)
    : world_min_(min), world_max_(max) {
} // : shows fast init list, these two vars are predefined in hpp

void World::add_obstacle(const Obstacle &obst) { obstacles_.push_back(obst); }

const std::vector<Obstacle> &World::obstacles() const { return obstacles_; }

bool World::is_inside(const Vec2 &p) const {
  return p.x >= world_min_.x && p.x <= world_max_.x && p.y >= world_min_.y &&
         p.y <= world_max_.y;
}

bool World::collides(const Vec2 &center, float radius) const {
  // check world bound
  if (center.x - radius < world_min_.x || center.x + radius > world_max_.x ||
      center.y - radius < world_min_.y || center.y + radius > world_max_.y) {
    return true;
  }

  // check all obstacles
  for (const Obstacle &obst : obstacles_) {
    // redundan, handled by clamp
    //   if (obst.Contains(center)) {
    //       return true;
    //   }

    // find closest corner OR just return center if inside box, this returns
    // closest point in the circle no matter what to the center of the circle,
    // e.g. x distance or 0 distance
    float closest_x = clamp(center.x, obst.min.x, obst.max.x);
    float closest_y = clamp(center.y, obst.min.y, obst.max.y);

    // find vector [dx, dy] from this point to center
    // dx is 0
    float dx = center.x - closest_x;
    float dy = center.y - closest_y;

    if (dx * dx + dy * dy < radius * radius) {
      return true;
    }
  }
  return false;
}

std::optional<float> World::raycast(const Pose2D &origin, float max_range) const {
  float cos_th = std::cos(origin.theta);
  float sin_th = std::sin(origin.theta);

  // default closest_hit to lidar range
  std::optional<float> closest_hit;

  // check each obstacle
  for (const Obstacle &obst : obstacles_) {
    // x = cos(theta) * t
    // y = sin(theta) * t
    // t = x / cos(theta) or y / sin(theta)
    // but origin is not 0, 0 so x/y is delta

    float tx_min, tx_max;
    if (cos_th != 0.0f) { // if not vertical
      float t1 = (obst.min.x - origin.x) / cos_th;
      float t2 = (obst.max.x - origin.x) / cos_th;
      tx_min = std::min(t1, t2);
      tx_max = std::max(t1, t2);
    } else {
      if (origin.x >= obst.min.x && origin.x <= obst.max.x) {
        // if above or below, t_enter/exit ignores x for the t_enter and t_exit
        tx_min = -INFINITY;
        tx_max = INFINITY;
      } else {
        continue;
      }
    }

    float ty_min, ty_max;
    if (sin_th != 0.0f) { // if not horizontal
      float t1 = (obst.min.y - origin.y) / sin_th;
      float t2 = (obst.max.y - origin.y) / sin_th;
      ty_min = std::min(t1, t2);
      ty_max = std::max(t1, t2);
    } else {
      if (origin.y >= obst.min.y && origin.y <= obst.max.y) {
        // if left or right exactly, t_enter/exit ignores y for the t_enter and
        // t_exit
        ty_min = -INFINITY;
        ty_max = INFINITY;
      } else {
        continue;
      }
    }

    // slab method, just works
    float t_enter = std::max(tx_min, ty_min); // max of mins
    float t_exit = std::min(tx_max, ty_max);  // min of maxes

    if (t_enter <= t_exit && t_enter > 0 && t_enter <= max_range) {
      if (!closest_hit || t_enter < *closest_hit) {
        closest_hit = t_enter;  // sets bool to true and value to t_enter
        // std::optional = bool (no *) + value (*)
      }
    }
  }

  return closest_hit;
}