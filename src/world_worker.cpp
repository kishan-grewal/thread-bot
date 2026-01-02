// src/world_worker.cpp

#include "world_worker.hpp"
#include "world.hpp"
// these two are for the sleep
#include <thread>
#include <chrono>

WorldWorker::WorldWorker(SharedContext *context, World *world, float max_range)
    : context_(context), world_(world), max_range_(max_range) {}

void WorldWorker::run_loop() {
  RobotState state;
  {
    std::lock_guard<std::mutex> lock(context_->state_mutex);
    state = context_->robot_state;
  }

  Pose2D pose = state.pose;
  // raycast is read-only, no mutex needed
  std::optional<float> hit = world_->raycast(pose, max_range_);
  float distance = hit ? *hit : -1.0f;
  // if hit ?(then) *hit(value) :(else) -1.0f

  // no read variable, write operation in mutex
  {
    std::lock_guard<std::mutex> lock(context_->sensor_mutex);
    context_->sensor_data.add_sample(distance);
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}