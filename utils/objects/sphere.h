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

#ifndef UTILS_OBJECTS_SPHERE_H_
#define UTILS_OBJECTS_SPHERE_H_

#include <optional>

#include "utils/object.h"
#include "utils/point.h"
#include "utils/ray.h"

class Sphere : public Object {
 public:
  Sphere(const Point &center, const double &radius,
         const Texture_Material &material)
      : center(center), radius(radius), material(material) {}

  std::optional<Point> intersect(const Ray &ray) override;
  Vector normal(const Point &point) override;
  Color get_texture(const Point &point) override;

  Point center;
  double radius;
  Texture_Material material;
};

#endif  // UTILS_OBJECTS_SPHERE_H_
