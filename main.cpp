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
#include "utils/materials/phong.h"
#include "utils/objects/sphere.h"
#include "utils/point.h"
#include "utils/ray.h"
#include "utils/scene.h"
#include "utils/vector.h"

int main() {
  std::cout << "Hello World" << std::endl;

  // Our image parameter
  Image image(1920, 1080);

  // Create materials
  Color pink(255, 0, 0);
  PhongMaterial phong_material(pink, 0.2, 1, 0.5, 200);

  // Create a sphere
  Point sphere_center = Point(0, 0, 0);
  double sphere_radius = 1;
  Sphere sphere = Sphere(sphere_center, sphere_radius, &phong_material);

  // Create light
  Vector light_position(2, 0, 0);
  Color light_color(255, 255, 255);
  double light_intensity = 1;
  PointLight light(light_position, light_color, light_intensity);

  // Camera definition
  Point position(2, 0, 0);
  Vector direction = Vector(-1, 0, 0);
  Vector up = Vector(0, 0, 1);
  Camera camera(position, direction, up, 1, 120, 90, image);

  // Create scene
  Scene scene(camera, 0.5);
  scene.addObject(&sphere);
  scene.addLight(&light);

  Ray ray;
  std::optional<Intersection> intersection;

  for (int i = 0; i < image.height; i++)
    for (int j = 0; j < image.width; j++) {
      ray = camera.cast_ray(j, i);

      double distance = INFINITY;
      Color color(0, 0, 0);

      for (Object* object : scene.objects) {
        intersection = object->intersect(ray);
        if (!intersection.has_value()) continue;

        double new_distance =
            (intersection.value().point - ray.origin).length();

        if (new_distance < distance) {
          distance = new_distance;
          color = object->get_texture(intersection.value(), scene);
        }
      }

      if (distance != INFINITY) image.my_image[i][j] = color;
    }

  image.to_ppm();
}
