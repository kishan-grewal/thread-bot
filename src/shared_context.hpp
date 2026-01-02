// src/shared_context.hpp

#include "types.hpp"
#include <atomic>
#include <mutex>

// 3 mutexes: control, state, sensor

struct SharedContext {
  // mutable (so they can be locked and unlocked in const functions)
  // mutexes and their data
  mutable std::mutex state_mutex;
  RobotState robot_state;

  mutable std::mutex sensor_mutex;
  SensorData sensor_data;

  // flag for ending all workers
  std::atomic<bool> shutdown_requested{false};

  // default constructor
  SharedContext() = default;
};