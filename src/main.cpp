// src/main.cpp

#include "robot.hpp"
#include "world.hpp"
#include "shared_context.hpp"
#include "reporter_worker.hpp"
#include "world_worker.hpp"
#include "robot_worker.hpp"
#include <iomanip>
#include <iostream>

int main() {
  // c++ has some automatic conversions suprisingly for function params
  // e.g. int -> float, var -> const ref

  // world, add_obstacle, robot, for(get_state, raycast, decide_control,
  // integrate)

  // create shared context for mutexes
  SharedContext context;

  // world and robot still live in main
  World world(Vec2(0.0f, 0.0f), Vec2(100.0f, 100.0f));
  world.add_obstacle(Obstacle(Vec2(50.0f, 0.0f), Vec2(60.0f, 20.0f)));
  Robot robot(Pose2D(10.0f, 10.0f, 0.0f), 1.0f);
  
  // initialize shared context, needs starting values
  context.robot_state = robot.get_state();
  context.sensor_data.add_sample(-1.0f); // needs something to read

  // sim params
  float dt = 0.001f;
  float max_range = 20.0f;

  // create workers
  ReporterWorker reporter_worker(&context);
  WorldWorker world_worker(&context, &world, max_range);
  RobotWorker robot_worker(&context, &robot, dt);

  // start all workers
  reporter_worker.start();
  world_worker.start();
  robot_worker.start();

  // run for some amount of clock time
  std::this_thread::sleep_for(std::chrono::milliseconds(2500));

  // stop all workers
  reporter_worker.stop();
  world_worker.stop();
  robot_worker.stop();

  // wait for all workers to finish
  reporter_worker.join();
  world_worker.join();
  robot_worker.join();

  return 0;
}