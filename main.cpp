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

#include "utils/blob.h"
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
  Color red(1., 0., 0.);
  Color green(0., 1., 0.);
  PhongMaterial phong_material(green, 0.2, 0.5, 0.3, 100);
  PhongMaterial phong_reflect(red, 0.2, 0.8, 0.2, 0.5, 100);

  // Get object from .obj
  std::vector<std::string> files(argv + 1, argv + argc);
  std::vector<Object*> objects = object_loader(files, &phong_reflect);

  // Create a sphere
  Point sphere_center = Point(0, -0.5, 2);
  double sphere_radius = 0.5;
  Sphere sphere = Sphere(sphere_center, sphere_radius, &phong_material);

  // Create scene (camera + light)
  PointLight light(Point(5, 5, 5), Color(1., 1., 1.), 1);
  Image image(1920 / 4, 1080 / 4);
  // Image image(2, 2);
  Camera camera(Point(3, 0, 0), Vector(-1, 0, 0), Vector(0, 0, 1), 1, 120, 90,
                image);
  Scene scene(camera, 1.5, Color(0., 0., 0.));
  scene.addLight(&light);
  scene.addObject(&sphere);

  for (Object* object : objects) scene.addObject(object);

  Ray ray;
  std::optional<Intersection> intersection;
  Color color(0., 0., 0.);

  for (int i = 0; i < image.height; i++)
    for (int j = 0; j < image.width; j++) {
      ray = camera.cast_ray(j, i);
      intersection = scene.intersectObject(ray);

      if (intersection.has_value()) {
        color = intersection.value().object->get_material()->get(
            intersection.value(), scene);
      } else {
        color = scene.backgroundColor;
      }
      image.my_image[i][j] = color;
    }

  image.to_ppm();
}
