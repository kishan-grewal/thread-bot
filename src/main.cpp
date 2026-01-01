// src/main.cpp

#include "world.hpp"
#include <iomanip>
#include <iostream>

int main() {
  std::cout << "=== World Constructor ===" << std::endl;
  World world(Vec2(0.0f, 0.0f), Vec2(100.0f, 100.0f));
  std::cout << "Created world: [0, 0] to [100, 100]" << std::endl;

  std::cout << "\n=== Adding Obstacles ===" << std::endl;
  world.add_obstacle(Obstacle(Vec2(20.0f, 20.0f), Vec2(40.0f, 40.0f)));
  world.add_obstacle(Obstacle(Vec2(60.0f, 10.0f), Vec2(80.0f, 30.0f)));
  std::cout << "Added 2 obstacles" << std::endl;
  std::cout << "Total obstacles: " << world.obstacles().size() << std::endl;

  std::cout << "\n=== Testing is_inside() ===" << std::endl;
  Vec2 inside(50.0f, 50.0f);
  Vec2 outside(150.0f, 150.0f);
  Vec2 boundary(100.0f, 100.0f);

  std::cout << "Point (50, 50) inside world: "
            << (world.is_inside(inside) ? "YES" : "NO") << std::endl;
  std::cout << "Point (150, 150) inside world: "
            << (world.is_inside(outside) ? "YES" : "NO") << std::endl;
  std::cout << "Point (100, 100) inside world: "
            << (world.is_inside(boundary) ? "YES" : "NO") << std::endl;

  std::cout << "\n=== Testing collides() ===" << std::endl;
  // Circle in open space
  Vec2 safe_center(10.0f, 10.0f);
  std::cout << "Circle at (10, 10) radius 3 collides: "
            << (world.collides(safe_center, 3.0f) ? "YES" : "NO") << std::endl;

  // Circle hitting first obstacle
  Vec2 obstacle1_center(30.0f, 30.0f);
  std::cout << "Circle at (30, 30) radius 5 collides: "
            << (world.collides(obstacle1_center, 5.0f) ? "YES" : "NO")
            << std::endl;

  // Circle hitting second obstacle
  Vec2 obstacle2_center(70.0f, 20.0f);
  std::cout << "Circle at (70, 20) radius 4 collides: "
            << (world.collides(obstacle2_center, 4.0f) ? "YES" : "NO")
            << std::endl;

  // Circle hitting world boundary
  Vec2 boundary_center(98.0f, 50.0f);
  std::cout << "Circle at (98, 50) radius 5 collides with boundary: "
            << (world.collides(boundary_center, 5.0f) ? "YES" : "NO")
            << std::endl;

  std::cout << "\n=== Testing raycast() ===" << std::endl;
  float max_range = 50.0f;

  // Ray pointing right, should hit obstacle at (60, 10)-(80, 30)
  Pose2D ray1(10.0f, 20.0f, 0.0f); // pointing east (theta=0)
  float dist1 = world.raycast(ray1, max_range);
  std::cout << "Ray from (10, 20) pointing east (0°): hit at distance " << dist1
            << std::endl;

  // Ray pointing up, should miss obstacles
  Pose2D ray2(10.0f, 10.0f, deg2rad(90.0f)); // pointing north (theta=90°)
  float dist2 = world.raycast(ray2, max_range);
  std::cout << "Ray from (10, 10) pointing north (90°): hit at distance "
            << dist2 << std::endl;

  // Ray pointing northeast, should hit obstacle
  Pose2D ray3(0.0f, 0.0f, deg2rad(45.0f)); // pointing northeast (45°)
  float dist3 = world.raycast(ray3, max_range);
  std::cout << "Ray from (0, 0) pointing northeast (45°): hit at distance "
            << dist3 << std::endl;

  // Ray pointing right from middle, should hit boundary
  Pose2D ray4(50.0f, 50.0f, 0.0f); // pointing east
  float dist4 = world.raycast(ray4, max_range);
  std::cout << "Ray from (50, 50) pointing east (0°): hit at distance " << dist4
            << " (world boundary)" << std::endl;

  // Ray with no collision
  Pose2D ray5(5.0f, 5.0f,
              deg2rad(225.0f)); // pointing southwest (away from world)
  float dist5 = world.raycast(ray5, max_range);
  std::cout << "Ray from (5, 5) pointing southwest (225°): hit at distance "
            << dist5 << " (max range)" << std::endl;

  return 0;
}