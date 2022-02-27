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

#include "gif-h/gif.h"
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
  Point sphere_center = Point(5, 0, 0);
  double sphere_radius = 4.2;
  Sphere sphere = Sphere(sphere_center, sphere_radius, &material_pink);

  Point sphere2_center = Point(-5, 0, 0);
  double sphere2_radius = 2.1;
  Sphere sphere2 = Sphere(sphere2_center, sphere2_radius, &material_sth);

  // Our image parameter
  size_t width = 192 * 10;
  size_t height = 108 * 10;
  Image image(width, height);

  // Camera definition
  Point position(0, -10, 0);
  Vector direction = Vector(0, 1, 0);
  Vector up = Vector(0, 0, 1);
  Camera camera(position, direction, up, 1, 120, 90, image);
  Scene scene(camera);
  scene.addObject(&sphere2);
  scene.addObject(&sphere);

  Ray ray;
  std::optional<Point> intersection;

  // Gif
  auto fileName = "raytracer.gif";
  int delay = 1;
  int frames = 50;
  double angle_step = 360 / frames * PI / 180;

  GifWriter g;
  GifBegin(&g, fileName, width, height, delay);
  for (int f = 0; f < frames; f++) {
    double theta = angle_step * f;
    Point position(cos(theta) * 10, sin(theta) * 10, 0);
    Vector direction = Vector(0, 0, 0) - position;
    Camera camera(position, direction, up, 1, 120, 90, image);
    scene.camera = camera;

    Image image(width, height);

    for (int i = 0; i < image.height; i++)
      for (int j = 0; j < image.width; j++) {
        ray = scene.camera.cast_ray(j, i);

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

    if (f == 12) image.to_ppm();
    GifWriteFrame(&g, image.to_rgba_vector().data(), width, height, delay, 8,
                  true);
  }
  GifEnd(&g);

  // image.to_ppm();
}
