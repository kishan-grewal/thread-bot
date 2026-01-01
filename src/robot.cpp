// src/robot.cpp

#include "robot.hpp"
#include <cmath>

Robot::Robot(
    const Pose2D &initial_pose,
    float radius) // need curly brace for any multi-items in fast init list
    : state_({initial_pose, 0.0f, 0.0f}), radius_(radius) {}

const RobotState &Robot::get_state() const { return state_; }

float Robot::radius() const { return radius_; }

void Robot::integrate(float dt, const ControlCommand &cmd) {
  state_.linear_vel = clamp(cmd.linear_vel, -max_linear_vel_, max_linear_vel_);
  state_.angular_vel =
      clamp(cmd.angular_vel, -max_angular_vel_, max_angular_vel_);

  state_.pose.theta += state_.angular_vel * dt;
  float cos_th = std::cos(state_.pose.theta);
  float sin_th = std::sin(state_.pose.theta);

  state_.pose.x += state_.linear_vel * cos_th * dt;
  state_.pose.y += state_.linear_vel * sin_th * dt;
}
