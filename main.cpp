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
#include "utils/scene.h"
#include "utils/vector.h"

int main() {
  std::cout << "Hello World" << std::endl;

  Color pink(255, 51, 153);
  Uniform_Texture material_pink = Uniform_Texture(pink);

  // Create a sphere
  Point sphere_center = Point(0, 0, 10);
  double sphere_radius = 4.2;
  Sphere sphere = Sphere(sphere_center, sphere_radius, &material_pink);

  // Our image parameter
  int size = 1000;
  Image image(size, size);

  // Camera definition
  Point position(0, 0, 0);
  Vector direction(0, 0, 1);
  Vector up(1, 0, 0);
  Camera camera(position, direction, up, 1, 90, 90, image);
  Scene scene(camera);
  scene.addObject(&sphere);

  Ray ray;
  std::optional<Point> intersection;

  for (int i = 0; i < image.width; i++)
    for (int j = 0; j < image.height; j++) {
      ray = camera.cast_ray(i, j);

      for (Object* object : scene.objects)
        intersection = object->intersect(ray);

      if (!intersection.has_value()) continue;

      Color color = sphere.get_texture(intersection.value());

      image.my_image[i][j] = color;
    }

  image.to_ppm();
}
