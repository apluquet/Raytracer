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

#include <vector>

#include "utils/camera.h"
#include "utils/light.h"
#include "utils/object.h"

class Intersection;
class Object;
class Material;

class Scene {
 public:
  explicit Scene(const Camera &camera, const double &ambientIntensity,
                 const Color &backgroundColor)
      : camera(camera),
        ambientIntensity(ambientIntensity),
        backgroundColor(backgroundColor) {}

  void addObject(Object *object);
  void addLight(Light *light);

  std::optional<Intersection> intersectObject(
      const Ray &ray, const double &min_distance = -1) const;

  double get_potential(const Point &point) const;

  void renderLines(int start, int end);
  void render(bool multithreading = true);

  // void deleteObject(Object object);
  // void deleteLight(Light light);

  std::vector<Object *> objects;
  std::vector<Light *> lights;
  double ambientIntensity;  // [0,1]
  Color backgroundColor;
  Camera camera;
};
