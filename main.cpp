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

  // Tnt texture
  std::shared_ptr<Image> tnt_top = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/tnt_top.png");
  std::shared_ptr<Image> tnt_side = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/tnt_side.png");
  std::shared_ptr<Image> tnt_bottom = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/tnt_bottom.png");

  AABBTexture tnt_texture(tnt_top, tnt_side, tnt_bottom);

  // Grass texture
  std::shared_ptr<Image> grass_top = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/grass_top_colored.png");
  std::shared_ptr<Image> grass_side = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/grass_side.png");
  std::shared_ptr<Image> grass_bottom = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/dirt.png");

  AABBTexture grass_texture(grass_top, grass_side, grass_bottom);

  // craft texture
  std::shared_ptr<Image> craft_top = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/crafting_table_top.png");
  std::shared_ptr<Image> craft_side = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/crafting_table_front.png");
  std::shared_ptr<Image> craft_bottom = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/dirt.png");

  AABBTexture craft_texture(craft_top, craft_side, craft_bottom);

  // leaves texture
  std::shared_ptr<Image> leaves = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/flowering_azalea_leaves.png");

  AABBTexture leaves_texture(leaves, leaves, leaves);

  // oak texture
  std::shared_ptr<Image> oak_top = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/log_oak_top.png");
  std::shared_ptr<Image> oak_side = std::make_shared<Image>(
      "/home/dreamexe/Documents/Epita/S8/ISIM/raytracing-tp/scenes/"
      "minecraft_textures/default_pack_1.8/"
      "assets/minecraft/textures/blocks/log_oak.png");

  AABBTexture oak_texture(oak_top, oak_side, oak_top);

  // Get object from .obj
  std::vector<std::string> files(argv + 1, argv + argc);
  // std::vector<Object*> objects = object_loader(files, &phong_material);

  // Create scene (camera + light)
  // PointLight light(Point(4.1, -4.32, 3.36), Color(1., 1., 1.), 1);
  PointLight light(Point(2, 3, 5), Color(1., 1., 1.), 1);
  Image image(1920, 1080);
  // Camera camera(Point(3.56, 1.67, 3.87), image, Vector(0, -1, 0),
  // Vector(0, 0, 1), 1, 60, 45);
  Vector forward = Vector(10, 24, -12).normalize();
  Vector right = forward ^ Vector(0, 0, 1);
  Vector up = right ^ forward;
  Camera camera(Point(-7, -22, 15.5), image, forward, up, 1, 30, 22.5);
  Scene scene(camera, 1.5, Color(122. / 255., 143. / 255., 255. / 255.));
  scene.addLight(&light);
  // scene.addObject(&aabb);

  // for (Object* object : objects) scene.addObject(object);

  // Create AABB object

  // Grass
  scene.addObject(new AABB(Point(3, 0, 0), Point(4, 1, 1), &grass_texture));
  scene.addObject(new AABB(Point(4, 0, 0), Point(5, 1, 1), &grass_texture));
  scene.addObject(new AABB(Point(1, 1, 0), Point(2, 2, 1), &grass_texture));
  scene.addObject(new AABB(Point(2, 1, 0), Point(3, 2, 1), &grass_texture));
  scene.addObject(new AABB(Point(3, 1, 0), Point(4, 2, 1), &grass_texture));
  scene.addObject(new AABB(Point(4, 1, 0), Point(5, 2, 1), &grass_texture));
  scene.addObject(new AABB(Point(5, 1, 0), Point(6, 2, 1), &grass_texture));
  scene.addObject(new AABB(Point(0, 2, 0), Point(1, 3, 1), &grass_texture));
  scene.addObject(new AABB(Point(1, 2, 0), Point(2, 3, 1), &grass_texture));
  scene.addObject(new AABB(Point(2, 2, 0), Point(3, 3, 1), &grass_texture));
  scene.addObject(new AABB(Point(3, 2, 0), Point(4, 3, 1), &grass_texture));
  scene.addObject(new AABB(Point(4, 2, 0), Point(5, 3, 1), &grass_texture));
  scene.addObject(new AABB(Point(5, 2, 0), Point(6, 3, 1), &grass_texture));
  scene.addObject(new AABB(Point(6, 2, 0), Point(7, 3, 1), &grass_texture));
  scene.addObject(new AABB(Point(0, 3, 0), Point(1, 4, 1), &grass_texture));
  scene.addObject(new AABB(Point(1, 3, 0), Point(2, 4, 1), &grass_texture));
  scene.addObject(new AABB(Point(2, 3, 0), Point(3, 4, 1), &grass_texture));
  scene.addObject(new AABB(Point(3, 3, 0), Point(4, 4, 1), &grass_texture));
  scene.addObject(new AABB(Point(4, 3, 0), Point(5, 4, 1), &grass_texture));
  scene.addObject(new AABB(Point(5, 3, 0), Point(6, 4, 1), &grass_texture));
  scene.addObject(new AABB(Point(6, 3, 0), Point(7, 4, 1), &grass_texture));
  scene.addObject(new AABB(Point(2, 4, 0), Point(3, 5, 1), &grass_texture));
  scene.addObject(new AABB(Point(3, 4, 0), Point(4, 5, 1), &grass_texture));
  scene.addObject(new AABB(Point(4, 4, 0), Point(5, 5, 1), &grass_texture));

  // Oak
  scene.addObject(new AABB(Point(1, 3, 1), Point(2, 4, 2), &oak_texture));
  scene.addObject(new AABB(Point(1, 3, 2), Point(2, 4, 3), &oak_texture));
  scene.addObject(new AABB(Point(1, 3, 3), Point(2, 4, 4), &oak_texture));

  // Leaves
  scene.addObject(new AABB(Point(0, 3, 4), Point(1, 4, 5), &leaves_texture));
  scene.addObject(new AABB(Point(1, 3, 4), Point(2, 4, 5), &leaves_texture));
  scene.addObject(new AABB(Point(2, 3, 4), Point(3, 4, 5), &leaves_texture));
  scene.addObject(new AABB(Point(0, 4, 4), Point(1, 5, 5), &leaves_texture));
  scene.addObject(new AABB(Point(1, 4, 4), Point(2, 5, 5), &leaves_texture));
  scene.addObject(new AABB(Point(2, 4, 4), Point(3, 5, 5), &leaves_texture));
  scene.addObject(new AABB(Point(0, 5, 4), Point(1, 6, 5), &leaves_texture));
  scene.addObject(new AABB(Point(1, 5, 4), Point(2, 6, 5), &leaves_texture));
  scene.addObject(new AABB(Point(2, 5, 4), Point(3, 6, 5), &leaves_texture));

  scene.addObject(new AABB(Point(0, 4, 5), Point(1, 5, 6), &leaves_texture));
  scene.addObject(new AABB(Point(1, 4, 5), Point(2, 5, 6), &leaves_texture));
  scene.addObject(new AABB(Point(2, 4, 5), Point(3, 5, 6), &leaves_texture));
  scene.addObject(new AABB(Point(1, 3, 5), Point(2, 4, 6), &leaves_texture));
  scene.addObject(new AABB(Point(1, 5, 5), Point(2, 6, 6), &leaves_texture));

  scene.addObject(new AABB(Point(1, 4, 6), Point(2, 5, 7), &leaves_texture));

  // Craft
  scene.addObject(new AABB(Point(3, 2, 1), Point(4, 3, 2), &craft_texture));

  // TNT
  scene.addObject(new AABB(Point(4, 0, 1), Point(5, 1, 2), &tnt_texture));

  scene.render();
  scene.camera.image.to_ppm();
}
