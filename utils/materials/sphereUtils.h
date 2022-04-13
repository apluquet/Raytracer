/**
 * @file sphereUtils.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief
 * @version 0.1
 * @date 2022-04-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <math.h>

#include <cmath>
#include <vector>

#include "utils/material.h"

#define PI 3.14159265

inline Point flatten3Dpoint(const Point &point3D, const Point &center) {
  // Vector from sphere center to intersection point
  Vector vec = point3D - center;
  double radius = vec.length();

  // Azimuthal angle increasing clockwise
  double theta = atan2(vec.x, vec.z);

  // Polar angle
  double phi = acos(vec.y / radius);

  double raw_u = theta / (2 * PI);
  double u = 1 - (raw_u + 0.5);
  double v = 1 - phi / PI;

  return Point(u, v, 0);
}
