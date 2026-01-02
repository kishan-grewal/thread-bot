// src/robot.hpp

#pragma once
#include "types.hpp"

class Robot {
public:
  // Robot: constref initial_pose. radius, get_state. radius expose functions,
  // integrate
  Robot(const Pose2D &initial_pose, float radius);
  // reveal robot state as const ref (ref because large, const left for safety)
  // similar to passing it in, if you wanted a copy use RobotState not a const
  // ref
  const RobotState &get_state() const;
  float radius() const; // const right for read-only methods

  void integrate(float dt, const ControlCommand &cmd);

private:
  RobotState state_;
  float radius_;
  float max_linear_vel_ = 2.0f;
  float max_angular_vel_ = 2.0f;
};