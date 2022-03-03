/**
 * @file intersection.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Intersection struct.
 * @version 0.1
 * @date 2022-03-01
 *
 * @copyright Copyright (c) 2022
 *
 * Contains :
 * the ray that was used to compute the intersection,
 * the point where an intersection was found,
 * and the normal vector of the object at this point.
 */

#pragma once

#include "utils/point.h"
#include "utils/ray.h"
#include "utils/vector.h"

struct Intersection {
  Intersection(const Ray &ray, const Point &point, const Vector &normal)
      : ray(ray), point(point), normal(normal.normalize()) {}

  Ray ray;
  Point point;
  Vector normal;
};
