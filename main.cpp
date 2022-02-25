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
#include "utils/objects/sphere.h"
#include "utils/point.h"
#include "utils/ray.h"
#include "utils/vector.h"

int main() {
  std::cout << "Hello World" << std::endl;

  /* Image tests

  Image my_image(5, 4);
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

  /* Ray tests

  Point point = Point(42, 42, 42);
  std::cout << "Point: " << point << "\n";

  Vector vector = Vector(1, 0, 0);
  std::cout << "Vector: " << vector << "\n";

  Ray ray = Ray(point, vector);
  std::cout << "Ray: " << ray << "\n";
  */
  Point center = Point(10, 0, 0);
  double radius = 4.2;
  Texture_Material material = Uniform_Texture(42, 42);
  Sphere sphere = Sphere(center, radius, material);

  int size = 1000;
  Image image(size, size);
  double step = 5. * 2 / size;

  for (int i = 0; i < image.height; i++)
    for (int j = 0; j < image.width; j++) {
      Point origin(0, (-size / 2 + j) * step, (-size / 2 + i) * step);
      Vector direction(1, 0, 0);
      Ray ray(origin, direction);

      std::optional<Point> intersection = sphere.intersect(ray);

      if (!intersection.has_value()) continue;

      Color color = sphere.get_texture(intersection.value());

      image.my_image[i][j] = color;
    }

  image.to_ppm();
}
