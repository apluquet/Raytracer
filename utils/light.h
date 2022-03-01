/**
 * @file light.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Light class.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "utils/color.h"
#include "utils/point.h"

class Light {};

class PointLight : public Light {
 public:
  PointLight(const Point &position, const Color &color, const double &intensity)
      : position(position), color(color), intensity(intensity) {}

  Point position;
  Color color;
  double intensity;
};
