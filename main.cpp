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
#include "utils/materials/cartoon.h"
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
  CartoonMaterial cartoon_material(red, 0.2, 0.5, 0.3, 100);

  // Get object from .obj
  std::vector<std::string> files(argv + 1, argv + argc);
  std::vector<Object*> objects = object_loader(files, &cartoon_material);

  // Create scene (camera + light)
  // PointLight light(Point(4.1, -4.32, 3.36), Color(1., 1., 1.), 1);
  PointLight light(Point(5, 5, 5), Color(1., 1., 1.), 1);
  Image image(1920 / 2, 1080 / 2);
  // Image image(480, 270);
  // Camera camera(Point(3.56, 1.67, 3.87), image, Vector(0, -1, 0),
  // Vector(0, 0, 1), 1, 60, 45);
  Camera camera(Point(6, 0, 0), image, Vector(-1, 0, 0), Vector(0, 0, 1), 1, 60,
                45);
  Scene scene(camera, 1.5, Color(0., 0., 0.));
  scene.addLight(&light);

  for (Object* object : objects) scene.addObject(object);

  scene.render();
  scene.camera.image.to_ppm();
}
