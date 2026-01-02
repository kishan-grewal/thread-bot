// src/reporter_worker.cpp

#include "reporter_worker.hpp"
#include "types.hpp"
// these two are for the sleep
#include <thread>
#include <chrono>

ReporterWorker::ReporterWorker(SharedContext *context) : context_(context) {}

void ReporterWorker::run_loop() {
  // lock (temporarily) and read robot state
  RobotState state;
  {
    std::lock_guard<std::mutex> lock(context_->state_mutex);
    // every line of code between lock guard and the end brace is guarded
    state = context_->robot_state;
  }

  SensorData sensor;
  {
    std::lock_guard<std::mutex> lock(context_->sensor_mutex);
    sensor = context_->sensor_data;
  }

  printf("%f %f %f\n", state.pose.x, state.pose.y, sensor.history.back());

  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}