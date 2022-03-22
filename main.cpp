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
#include "utils/objects/sphere.h"
#include "utils/objects/triangle.h"
#include "utils/point.h"
#include "utils/ray.h"
#include "utils/scene.h"
#include "utils/vector.h"

int main() {
  std::cout << "Hello World" << std::endl;

  // Our image parameter
  Image image(192, 108);

  // Create materials
  Color red(255, 0, 0);
  PhongMaterial phong_material(red, 1, 1, 0.5, 150);

  // Create a sphere
  Point sphere_center = Point(0, 0, 0);
  double sphere_radius = 1;
  Sphere sphere = Sphere(sphere_center, sphere_radius, &phong_material);

  /*
  Point sphere_center2 = Point(1, 0.5, 0.5);
  double sphere_radius2 = 0.1;
  Sphere sphere2 = Sphere(sphere_center2, sphere_radius2, &phong_material);
  */

  // Create light
  Vector light_position(5, 5, 5);
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

  // Create Blob
  Blob blob(Point(-2, -2, -2), 4., 10);
  std::vector<Object*> triangles = blob.evaluate(scene);

  std::cout << triangles.size() << " triangles in blob.\n";

  Scene blob_scene(camera, 0.5);
  for (Object* triangle : triangles) blob_scene.addObject(triangle);
  scene = blob_scene;

  Ray ray;
  std::optional<Intersection> intersection;
  Color color(0, 0, 0);

  ray = Ray(Point(2, 0, -0.5), Vector(-1, 0, 0));
  intersection = scene.intersectObject(ray);

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
