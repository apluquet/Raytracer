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

#include <thread>  // NOLINT [build/c++11]

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

double Scene::get_potential(const Point &point) const {
  double potential = 0;

  for (Object *object : objects) {
    potential += object->get_potential(point);
  }

  return potential;
}

void Scene::renderLines(int start, int end) {
  Ray ray;
  std::optional<Intersection> intersection;
  Color color(0., 0., 0.);

  for (int i = start; i < end; i++)
    for (int j = 0; j < camera.image.width; j++) {
      ray = camera.cast_ray(j, i);
      intersection = intersectObject(ray);

      if (intersection.has_value()) {
        color = intersection.value().object->get_material()->get(
            intersection.value(), *this);
      } else {
        color = backgroundColor;
      }
      camera.image.my_image[i][j] = color;
    }
}

void Scene::render(bool multithreading) {
  if (multithreading) {
    unsigned int nb_thread = std::jthread::hardware_concurrency();
    int lines_per_thread = camera.image.height / nb_thread;

    // Check that the number of threads is not too big compared too the number
    // of lines.
    if (lines_per_thread > 0) {
      std::jthread threads[nb_thread];

      for (int i = 0; i < nb_thread - 1; i++) {
        threads[i] =
            std::jthread(&Scene::renderLines, this, i * lines_per_thread,
                         (i + 1) * lines_per_thread);
      }

      // Last thread takes the undividable lines.
      threads[nb_thread - 1] =
          std::jthread(&Scene::renderLines, this,
                       (nb_thread - 1) * lines_per_thread, camera.image.height);

      for (int i = 0; i < nb_thread; i++) threads[i].join();
      return;
    }
  }

  // If multithreading was not performed, render the entire image.
  renderLines(0, camera.image.height);
}
