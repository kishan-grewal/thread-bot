// src/worker.cpp

#include "worker.hpp"

// default constructor
WorkerBase::WorkerBase() = default;

// set atomic bool false and "join" on destructor
WorkerBase::~WorkerBase() {
  // stop is just the first flag wave to the thread to stop
  stop();
  // join means we ask c++ to pause "this" thread until our thread has exited
  // without this, if c++ kills a thread that has not exited, the program will
  // literally just crash
  join();
}

void WorkerBase::start() {
  // if already running do nothing
  if (running_.load()) {
    return;
  }

  // else set running to true and create the thread, it does function
  // thread_entry
  running_.store(true);
  thread_ = std::thread(&WorkerBase::thread_entry, this);
}

// threads cannot be safely killed, full stop
// so we assign the thread a function with a while loop thread_entry
// the while loop has the atomic bool as a condition and will end in its own
// time, safely
void WorkerBase::stop() {
  // set atomic bool false thats it
  running_.store(false);
}

void WorkerBase::join() {
  if (thread_.joinable()) {
    thread_.join(); // join is a please wait to the "this" thread, asking it to
                    // wait for our thread to exit
  }
}

bool WorkerBase::is_running() const {
  // public can read the atomic bool (its private)
  return running_.load();
}

// thread entry is literally a wrapper for whatever function the subclass wants
// to call in the thread we need this wrapper so that worker has absolute
// authority over when the thread is stopped
void WorkerBase::thread_entry() {
  while (running_.load()) {
    run_loop();
  }
}
