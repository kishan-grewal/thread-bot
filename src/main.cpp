// src/main.cpp

#include "robot.hpp"
#include "world.hpp"
#include <iostream>

int main() {
  // c++ has some automatic conversions suprisingly for function params
  // e.g. int -> float, var -> const ref
  Robot robot(Pose2D(0.0f, 0.0f, 0.0f), 1.0f); // x y th r

  for (size_t i = 0; i<1000; ++i) {
    robot.integrate(0.001f, ControlCommand(1.0f, 1.0f));
  }

  RobotState state = robot.get_state();
  float radius = robot.radius();
  
  std::cout << " x: " << state.pose.x << " y: " << state.pose.y
            << " th: " << state.pose.theta << " l: " << state.linear_vel
            << " a: " << state.angular_vel << " r: " << radius << std::endl;

  return 0;
}