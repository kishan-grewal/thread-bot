// src/reporter_worker.hpp

#pragma once

#include "shared_context.hpp"
#include "worker.hpp"

// : here is inheritance
class ReporterWorker : public WorkerBase {
public:
  ReporterWorker(SharedContext *context);
  ~ReporterWorker() = default;

protected:
  void run_loop() override;
  // change this function in the parent

private:
  SharedContext *context_;
};