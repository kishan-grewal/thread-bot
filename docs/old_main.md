// src/main.cpp

#include "robot.hpp"
#include "world.hpp"
#include <iomanip>
#include <iostream>

ControlCommand decide_control(float distance) {
  const float SAFE_DISTANCE = 5.0f;
  const float TURN_DISTANCE = 10.0f;

  if (distance < SAFE_DISTANCE) {
    return ControlCommand(0.0f, 1.0f);
  } else if (distance < TURN_DISTANCE) {
    return ControlCommand(0.5f, 0.5f);
  } else {
    return ControlCommand(1.0f, 0.0f);
  }
}

int main() {
  // c++ has some automatic conversions suprisingly for function params
  // e.g. int -> float, var -> const ref

  // world, add_obstacle, robot, for(get_state, raycast, decide_control,
  // integrate)

  World world(Vec2(0.0f, 0.0f), Vec2(100.0f, 100.0f));
  world.add_obstacle(Obstacle(Vec2(50.0f, 0.0f), Vec2(60.0f, 20.0f)));

  Robot robot(Pose2D(10.0f, 10.0f, 0.0f), 1.0f);
  float max_range = 20.0f;

  float time = 50.0f;
  float dt = 0.001f;
  size_t steps = time / dt;

  for (size_t i = 0; i < steps; ++i) {
    const RobotState &state = robot.get_state();

    std::optional<float> hit = world.raycast(state.pose, max_range);
    ControlCommand cmd;
    float display_distance;

    if (hit) {
      cmd = decide_control(*hit);
      display_distance = *hit;
    } else {
      cmd = decide_control(max_range);
      display_distance = -1;
    }

    robot.integrate(dt, cmd);

    // if (i % 1000 == 0) {
    //   std::cout << "Step " << std::setw(6) << i << ": pose=("
    //             << std::setw(6) << std::fixed << std::setprecision(2)
    //             << state.pose.x << ", " << state.pose.y << ", " <<
    //             state.pose.theta << ") "
    //             << "dist=" << std::setw(6) << std::setprecision(2)
    //             << display_distance << std::endl;
    // }
    if (i % 1000 == 0) {
      printf("%f %f %f\n", state.pose.x, state.pose.y, display_distance);
    }
  }

  return 0;
}