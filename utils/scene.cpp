/**
 * @file scene.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Scene class methods.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/scene.h"

void Scene::addObject(Object *object) { objects.push_back(object); }

void Scene::addLight(Light *light) { lights.push_back(light); }

std::optional<Intersection> Scene::intersectObject(
    const Ray &ray, const double &min_distance) const {
  std::optional<Intersection> new_intersection;
  std::optional<Intersection> intersection;
  double distance = INFINITY;

  for (Object *object : objects) {
    new_intersection = object->intersect(ray);
    if (!new_intersection.has_value()) continue;

    double new_distance =
        (new_intersection.value().point - ray.origin).length();

    if (new_distance < distance) {
      distance = new_distance;
      intersection = new_intersection;
      if (new_distance < min_distance) return intersection;
    }
  }
  return intersection;
}
