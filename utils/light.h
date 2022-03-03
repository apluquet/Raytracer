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

class Light {
 public:
  Light() {}
  Light(const Point &position, const Color &color, const double &intensity)
      : position(position), color(color), intensity(intensity) {}

  virtual Point get_position() = 0;
  virtual Color get_color() = 0;
  virtual double get_intensity() = 0;

  Point position;
  Color color;
  double intensity;
};

class PointLight : public Light {
 public:
  PointLight(const Point &position, const Color &color, const double &intensity)
      : Light(position, color, intensity) {}

  Point get_position() override { return position; }
  Color get_color() override { return color; }
  double get_intensity() override { return intensity; }
};
