/**
 * @file main.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Main file of this raytracer project.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>

#include "utils/image.h"
#include "utils/point.h"
#include "utils/ray.h"
#include "utils/vector.h"

int main() {
  std::cout << "Hello World" << std::endl;

  /* Image tests

  Image my_image(500, 400);
  my_image.to_ppm();
  */

  /* Vector tests

  Vector v1 = Vector(1, 2, 3);
  std::cout << v1;

  Vector v2 = v1 * 2;
  std::cout << v2;

  Vector v3 = v1 ^ v2;
  std::cout << v3;

  Vector v4 = v2 + Vector(0, 1, 0);
  std::cout << v4;

  Vector v5 = v1 ^ v4;
  std::cout << v5;
  */

  Point point = Point(42, 42, 42);
  std::cout << "Point: " << point << "\n";

  Vector vector = Vector(1, 0, 0);
  std::cout << "Vector: " << vector << "\n";

  Ray ray = Ray(point, vector);
  std::cout << "Ray: " << ray << "\n";
}
