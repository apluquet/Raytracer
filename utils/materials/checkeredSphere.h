/**
 * @file checkeredSphere.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Texture mapping material class implementation.
 * @version 0.1
 * @date 2022-04-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "utils/material.h"

class CheckeredSphere : public Texture_Material {
 public:
  explicit CheckeredSphere(int precision, const Color &one, const Color &two)
      : precision(precision), one(one), two(two) {
    widthBox = 1. / precision;
    heightBox = 1. / (2 * precision);
  }

  Color get(const Intersection &intersection, const Scene &scene,
            int reflection_index = 5);

 private:
  bool getBox(double u, double v);
  int precision;
  double widthBox;
  double heightBox;
  Color one;
  Color two;
};
