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
#include <memory>

#include "utils/blob.h"
#include "utils/image.h"
#include "utils/materials/cartoon.h"
#include "utils/materials/phong.h"
#include "utils/materials/uniform_material.h"
#include "utils/object_loader.h"
#include "utils/objects/aabb.h"
#include "utils/objects/sphere.h"
#include "utils/objects/triangle.h"
#include "utils/point.h"
#include "utils/ray.h"
#include "utils/scene.h"
#include "utils/textures/aabb_texture.h"
#include "utils/textures/checkeredSphere.h"
#include "utils/textures/uvSphere.h"
#include "utils/vector.h"

extern "C" {
#define STB_IMAGE_IMPLEMENTATION
#include "utils/libs/stb_image.h"
}

static std::string filename_with_index(std::string filepath, int index,
                                       int nb_of_digits = 3) {
  std::stringstream ss;
  ss << filepath << std::setfill('0') << std::setw(nb_of_digits) << index;
  return ss.str();
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout
        << "Please provide a .png texture.\nYou can get one using the "
           "following command : `wget "
           "https://www.solarsystemscope.com/textures/download/"
           "8k_earth_daymap.jpg && convert 8k_earth_daymap.jpg map.png "
           "&& rm 8k_earth_daymap.jpg`\nUSAGE example: ./raytracer map.png"
        << std::endl;
    return 1;
  }

  // "frames" folder is generated if it does not exist
  const char* directory = "frames";
  if (!fs::is_directory(directory) ||
      !fs::exists(directory)) {       // Check if src folder exists
    fs::create_directory(directory);  // create src folder
  }

  int width = 1920;
  int height = 1080;

  Image image(width, height);

  Point position = Point(3, 0, 0);  // Camera position
  Point look_at = Point(0, 0, 0);   // Point camera is looking at
  Vector forward = (look_at - position).normalize();
  Vector right = forward ^ Vector(0, 0, 1);
  Vector up = right ^ forward;
  Camera camera(position, image, forward, up, 0.5, 60, 45);

  Scene scene(camera, 1.5, Color(122. / 255., 143. / 255., 255. / 255.));

  PointLight light(Point(10, -10, 10), Color(1., 1., 1.), 1.5);
  scene.addLight(&light);

  // Create UV Sphere
  std::shared_ptr<Image> sky_sphere = std::make_shared<Image>(argv[1]);

  std::shared_ptr<Texture> sky_texture = std::make_shared<UVSphere>(sky_sphere);
  std::shared_ptr<Texture> checkered =
      std::make_shared<CheckeredSphere>(10, Color(0, 0, 0), Color(1, 1, 1));
  UniformMaterial sky_material(sky_texture);

  scene.addObject(new Sphere(Point(0, 0, 0), 1, &sky_material));

  // Render frames (to convert with : `ffmpeg -r 30 -i my_image_%05d.ppm -y -an
  // output.mp4`)
  int frames = 256;
  double angle_step = 360. / frames * PI / 180;
  double radius = (position - look_at).length();

  for (int f = 0; f < frames; f++) {
    double theta = angle_step * f;

    image = Image(width, height);
    position = Point(cos(theta) * radius, sin(theta) * radius, 0) + look_at;
    forward = (look_at - position).normalize();
    right = forward ^ Vector(0, 0, 1);
    up = right ^ forward;

    Camera camera(position, image, forward, up, 0.5, 60, 40);

    scene.camera = camera;

    scene.render();
    scene.camera.image.to_ppm(filename_with_index("./frames/my_image_", f));
  }
}
