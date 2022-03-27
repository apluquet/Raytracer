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
#include "utils/object_loader.h"
#include "utils/objects/sphere.h"
#include "utils/objects/triangle.h"
#include "utils/point.h"
#include "utils/ray.h"
#include "utils/scene.h"
#include "utils/vector.h"

int main(int argc, char* argv[]) {
  // Create materials
  Color red(255, 0, 0);
  PhongMaterial phong_material(red, 0.2, 1, 0.5, 100);

  std::vector<std::string> files(argv + 1, argv + argc);
  std::vector<Object*> objects = object_loader(files, &phong_material);

  // Get object from .obj

  // Create scene (camera + light)
  PointLight light(Point(5, 5, 5), Color(255, 255, 255), 1);
  // Image image(1920, 1080);
  Image image(192 * 2, 108 * 2);
  Camera camera(Point(3, 0, 0), Vector(-1, 0, 0), Vector(0, 0, 1), 1, 120, 90,
                image);
  Scene scene(camera, 1.5);
  scene.addLight(&light);

  for (Object* object : objects) scene.addObject(object);

  Ray ray;
  std::optional<Intersection> intersection;
  Color color(0, 0, 0);

  for (int i = 0; i < image.height; i++)
    for (int j = 0; j < image.width; j++) {
      ray = camera.cast_ray(j, i);
      intersection = scene.intersectObject(ray);

      if (!intersection.has_value()) continue;

      color =
          intersection.value().object->get_texture(intersection.value(), scene);
      image.my_image[i][j] = color;
    }

  image.to_ppm();
}
