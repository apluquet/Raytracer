/**
 * @file material.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Implementation of class material
 * @version 0.1
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/material.h"

Color Uniform_Texture::get(const Point &point) {
  size_t Ir = kd;
  size_t Ig = kd;
  size_t Ib = kd;

  Color color(Ir, Ig, Ib);
  return color;
}
