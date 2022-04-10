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
#include "utils/objects/aabb.h"
#include "utils/objects/sphere.h"
#include "utils/objects/triangle.h"
#include "utils/point.h"
#include "utils/ray.h"
#include "utils/scene.h"
#include "utils/textures/aabb_texture.h"
#include "utils/vector.h"

extern "C" {
#define STB_IMAGE_IMPLEMENTATION
#include "utils/libs/stb_image.h"
}

int main(int argc, char* argv[]) {
  // Create materials
  Color red(1., 0., 0.);
  PhongMaterial phong_material(red, 0.2, 0.5, 0.3, 100);

  std::shared_ptr<Image> top = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/tnt_top.png");
  std::shared_ptr<Image> side = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/tnt_side.png");
  std::shared_ptr<Image> bottom = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/tnt_bottom.png");

  AABBTexture tnt_texture(top, side, bottom);

  // Get object from .obj
  std::vector<std::string> files(argv + 1, argv + argc);
  // std::vector<Object*> objects = object_loader(files, &phong_material);

  // Create AABB object
  AABB aabb(Point(0, 0, 0), Point(1, 1, 1), &tnt_texture);

  // Create scene (camera + light)
  // PointLight light(Point(4.1, -4.32, 3.36), Color(1., 1., 1.), 1);
  PointLight light(Point(2, 3, 5), Color(1., 1., 1.), 1);
  Image image(1920 / 2, 1080 / 2);
  // Camera camera(Point(3.56, 1.67, 3.87), image, Vector(0, -1, 0),
  // Vector(0, 0, 1), 1, 60, 45);
  Camera camera(Point(-3, -3, 3), image, Vector(1, 1, -1).normalize(),
                Vector(1, 1, 1).normalize(), 1, 60, 45);
  Scene scene(camera, 1.5, Color(0., 0., 0.));
  scene.addLight(&light);
  // scene.addObject(&aabb);

  // for (Object* object : objects) scene.addObject(object);
  scene.addObject(&aabb);

  scene.render(false);
  scene.camera.image.to_ppm();
}
