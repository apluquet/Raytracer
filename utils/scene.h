/**
 * @file scene.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Scene class.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <list>

#include "utils/camera.h"
#include "utils/light.h"
#include "utils/object.h"

class Object;
class Texture_Material;

class Scene {
 public:
  explicit Scene(const Camera &camera, const double &ambientIntensity)
      : camera(camera), ambientIntensity(ambientIntensity) {}

  void addObject(Object *object);
  void addLight(Light *light);

  // void deleteObject(Object object);
  // void deleteLight(Light light);

  std::list<Object *> objects;
  std::list<Light *> lights;
  double ambientIntensity;  // [0,1]
  Camera camera;
};
