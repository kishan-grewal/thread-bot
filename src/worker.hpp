// src/worker.hpp

#pragma once

#include <atomic>
#include <thread>

class WorkerBase {
public: // used by anyone e.g. main
  // constructor is not polymorphic
  WorkerBase();
  // destructor is polymorphic
  virtual ~WorkerBase();

  // needs a destructor as we are keeping the thread alive manually without a
  // container .e.g. a function

  // start the worker's thread
  void start();

  // signal the worker to stop its thread
  void stop();

  // wait for the worker to finish its thread
  void join();

  // check whether the worker is currently running
  bool is_running() const;

protected: // can be used by workerbase or its children
  virtual void run_loop() = 0;

private: // only used by workerbase, not objects of its child classes
  void thread_entry();

  std::thread thread_;
  std::atomic<bool> running_{false};
};