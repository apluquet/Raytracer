/**
 * @file ray.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Ray class.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef UTILS_RAY_H_
#define UTILS_RAY_H_

#include "utils/point.h"
#include "utils/vector.h"

class Ray {
 public:
  Ray(const Point &origin, const Vector &direction)
      : origin(origin), direction(direction) {}

  friend std::ostream &operator<<(std::ostream &os, const Ray &ray);

  Point origin;
  Vector direction;
};

#endif  // UTILS_RAY_H_
