// src/robot_worker.cpp

#include "robot_worker.hpp"
#include "robot.hpp"

RobotWorker::RobotWorker(SharedContext *context, Robot *robot, float dt)
    : context_(context), robot_(robot), dt_(dt) {}

ControlCommand RobotWorker::decide_control(float distance) const {
  const float SAFE_DISTANCE = 5.0f;
  const float TURN_DISTANCE = 10.0f;

  if (distance < SAFE_DISTANCE && distance > 0) {
    return ControlCommand(0.0f, 2.0f);
  } else if (distance < TURN_DISTANCE && distance > 0) {
    return ControlCommand(0.1f, 1.0f);
  } else {
    return ControlCommand(0.5f, 0.0f);
  }
}

void RobotWorker::run_loop() {
  // sensor mutex (read)
  float distance;
  {
    std::lock_guard<std::mutex> lock(context_->sensor_mutex);
    distance = context_->sensor_data.history.back();
  }

  // no lock needed for control command
  ControlCommand cmd = decide_control(distance);

  // no lock needed for integrate
  robot_->integrate(dt_, cmd);

  // sensor mutex (write)
  {
    std::lock_guard<std::mutex> lock(context_->state_mutex);
    // update shared context (robot state)
    context_->robot_state = robot_->get_state();
  }
}