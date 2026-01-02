// src/world_worker.hpp

#pragma once

#include "shared_context.hpp"
#include "worker.hpp"
#include "world.hpp"

class WorldWorker : public WorkerBase {
public:
  // max_range is a param that would usually just be in main
  WorldWorker(SharedContext *context, World *world, float max_range);
  ~WorldWorker() = default;

protected:
  void run_loop() override;

private:
  SharedContext *context_;
  World *world_;
  float max_range_;
};