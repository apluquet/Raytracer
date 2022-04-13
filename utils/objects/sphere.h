/**
 * @file sphere.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Sphere class.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <optional>
#include <vector>

#include "utils/object.h"
#include "utils/point.h"
#include "utils/ray.h"

class Sphere : public Object {
 public:
  Sphere(const Point &center, const double &radius, Material *material)
      : center(center), radius(radius), material(material) {}

  std::optional<Intersection> intersect(const Ray &ray) override;
  Vector normal(const Point &point) override;
  Material *get_material() override;
  double get_potential(const Point &point) override;

  std::vector<Point> get_position() override;

  Point center;
  double radius;
  Material *material;
};
