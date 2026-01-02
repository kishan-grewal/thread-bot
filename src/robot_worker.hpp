// src/robot_worker.hpp

#pragma once

#include "robot.hpp"
#include "shared_context.hpp"
#include "worker.hpp"

class RobotWorker : public WorkerBase {
public:
  RobotWorker(SharedContext *context, Robot *robot, float dt);
  ~RobotWorker() = default;

protected:
  void run_loop() override;

private:
  SharedContext *context_;
  Robot *robot_;
  float dt_;

  // only the cpp uses the function
  ControlCommand decide_control(float distance) const;
};