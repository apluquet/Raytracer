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

#ifndef UTILS_SCENE_H_
#define UTILS_SCENE_H_

#include <list>

#include "utils/camera.h"
#include "utils/light.h"
#include "utils/object.h"

class Scene {
  explicit Scene(Camera camera) : camera(camera) {}

  void addObject(Object object);
  void addLight(Light light);
  void addCamera(Camera camera);

  void deleteObject(Object object);
  void deleteLight(Light light);
  void deleteCamera(Camera camera);

  std::list<Object> objects;
  std::list<Light> lights;
  Camera camera;
};

#endif  // UTILS_SCENE_H_
