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

  Color sth(150, 10, 20);
  Uniform_Texture material_sth = Uniform_Texture(sth);

  // Create a sphere
  Point sphere_center = Point(0, 0, 0);
  double sphere_radius = 4.2;
  Sphere sphere = Sphere(sphere_center, sphere_radius, &material_pink);

  Point sphere2_center = Point(9, 7, 0);
  double sphere2_radius = 2.1;
  Sphere sphere2 = Sphere(sphere2_center, sphere2_radius, &material_sth);

  // Our image parameter
  int size = 1000;
  Image image(size, size);

  // Camera definition
  Point position(0, -10, 10);
  Vector direction = Vector(0, 0, 0) - position;
  Vector up = Vector(0, position.y, 0) ^ direction;
  Camera camera(position, direction, up, 1, 90, 90, image);
  Scene scene(camera);
  scene.addObject(&sphere2);
  scene.addObject(&sphere);

  Ray ray;
  std::optional<Point> intersection;
  for (int i = 0; i < image.width; i++)
    for (int j = 0; j < image.height; j++) {
      ray = camera.cast_ray(i, j);

      double distance = INFINITY;
      Color color(0, 0, 0);

      for (Object* object : scene.objects) {
        intersection = object->intersect(ray);
        if (!intersection.has_value()) continue;

        double new_distance = (intersection.value() - ray.origin).length();

        if (new_distance < distance) {
          distance = new_distance;
          color = object->get_texture(intersection.value());
        }
      }

      if (distance != INFINITY) image.my_image[i][j] = color;
    }

  image.to_ppm();
}
