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
#include "utils/objects/triangle.h"
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
  Color blue(0, 0, 255);
  Color green(0, 255, 0);
  PhongMaterial phong_material(pink, 0.2, 1, 0.5, 150);
  Uniform_Texture uniform(pink);
  Uniform_Texture uniform_blue(blue);
  Uniform_Texture uniform_green(green);

  /*
  // Create a sphere
  Point sphere_center = Point(0, 0, 0);
  double sphere_radius = 1;
  Sphere sphere = Sphere(sphere_center, sphere_radius, &phong_material);

  Point sphere_center2 = Point(1, 0.5, 0.5);
  double sphere_radius2 = 0.1;
  Sphere sphere2 = Sphere(sphere_center2, sphere_radius2, &phong_material);
  */

  // Triangle
  Point A(0, -1, 0);
  Point B(0, 0, 1);
  Point C(0, 1, 0);

  Point D(1, 1, 0);
  Point E(1, -1, 0);
  Point F(-1, -1, 0);

  Point G(-1, -1, 0);
  Point H(-1, 1, 0);
  Point I(1, 1, 0);
  Triangle triangle(A, B, C, &phong_material);
  Triangle triangleplan(D, E, F, &phong_material);
  Triangle triangleplan2(G, H, I, &uniform_blue);
  // Triangle triangle(A, B, C, &uniform);

  // Triangle 2
  Point B2(0, 0, -1);
  Triangle triangle2(A, B2, C, &uniform);

  // Create light
  Vector light_position(5, 5, 5);
  Color light_color(255, 255, 255);
  double light_intensity = 1;
  PointLight light(light_position, light_color, light_intensity);

  // Camera definition
  Point position(2, 0, 1.5);
  Vector direction = Vector(-1, 0, 0);
  Vector up = Vector(0, 0, 1);
  Camera camera(position, direction, up, 1, 120, 90, image);

  // Create scene
  Scene scene(camera, 0.5);
  // scene.addObject(&sphere);
  // scene.addObject(&sphere2);
  scene.addObject(&triangle);
  // scene.addObject(&triangleplan);
  // scene.addObject(&triangleplan2);
  // scene.addObject(&triangle2);
  scene.addLight(&light);

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
