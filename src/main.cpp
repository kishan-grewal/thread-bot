// src/main.cpp

#include "robot.hpp"
#include "world.hpp"
#include <iostream>
#include <iomanip>

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
  world.add_obstacle(Obstacle(Vec2(50.0f, 0.0f), Vec2(55.0f, 10.0f)));

  Robot robot(Pose2D(5.0f, 5.0f, 0.0f), 1.0f);
  float max_range = 20.0f;

  float time = 50.0f;
  float dt = 0.001f;
  size_t steps = time / dt;

  for (size_t i = 0; i < steps; ++i) {
    const RobotState &state = robot.get_state();
    std::optional<float> hit = world.raycast(state.pose, max_range);
    ControlCommand cmd = decide_control(distance);
    robot.integrate(dt, cmd);

    if (i % 1000 == 0) {
      std::cout << "Step " << std::setw(6) << i << ": pos=("
                << std::setw(6) << std::fixed << std::setprecision(2)
                << state.pose.x << ", " << state.pose.y << ") "
                << "dist=" << std::setw(6) << std::setprecision(2)
                << distance << std::endl;
    }
  }

  return 0;
}