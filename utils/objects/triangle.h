/**
 * @file sphere.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Sphere class.
 * @version 0.1
 * @date 2022-03-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <optional>

#include "utils/object.h"
#include "utils/point.h"
#include "utils/ray.h"

class Triangle : public Object {
 public:
  Triangle(const Point &A, const Point &B, const Point &C,
           Texture_Material *material)
      : A(A), B(B), C(C), material(material) {}

  std::optional<Intersection> intersect(const Ray &ray) override;
  Vector normal(const Point &point) override;
  Color get_texture(const Intersection &intersection,
                    const Scene &scene) override;

  Point A;
  Point B;
  Point C;
  Texture_Material *material;
};
